"use strict";

const fp = require("fastify-plugin");
const httpProxy = require("@fastify/http-proxy");

async function proxyPlugin(fastify, options) {
  const { services } = fastify.config; 
  const wsProxies = {};
  const activeConnections = new Map();

  // Register a proxy for each service
  for (const [serviceName, serviceConfig] of Object.entries(services)) {
    const {
      url: serviceUrl,
      prefix,
      proxyOptions = {},
      timeout,
      wsEnabled = false,
      wsPath = prefix
    } = serviceConfig;

    // HTTP Proxy
    fastify.register(httpProxy, {
      upstream: serviceUrl,
      prefix: prefix,
      http2: false,

      replyOptions: {
        rewriteRequestHeaders: (req, headers) => {
          // Add relevant headers
          headers["x-forwarded-proto"] = req.protocol;
          headers["x-forwarded-host"] = req.headers.host;

          // Custom headers
          headers["x-source"] = "gateway";
          headers["x-target"] = serviceName;
          headers["x-request-id"] = `${req.ip.replace(/[.:]/g, '-')}_${req.url.replace(/[\/?.]/g, '-')}_${Date.now()}`;
          headers["x-gateway-timestamp"] = Date.now().toString();

          // Apply custom header rewrites specific to the service
          if (proxyOptions.rewriteRequestHeaders)
            headers = proxyOptions.rewriteRequestHeaders(req, headers);

          return headers;
        },
      },
      timeout: timeout,
      ...proxyOptions,
    });

    // Set up WebSocket proxy for this service if enabled
    if (wsEnabled) {
      const parsedUrl = new URL(serviceUrl);
      wsProxies[wsPath] = {
        target: {
          host: parsedUrl.hostname,
          port: parsedUrl.port || (parsedUrl.protocol === 'https:' ? 443 : 80)
        },
        serviceName
      };
    }
  }

  // Handle WebSocket upgrade requests
  fastify.server.on('upgrade', (request, socket, head) => {
    const pathname = new URL(request.url, 'http://localhost').pathname;
    
    // Find the matching WebSocket proxy for this path
    const matchingProxy = Object.entries(wsProxies).find(([path, _]) => pathname.startsWith(path));
    if (!matchingProxy) {
      socket.destroy();
      return;
    }

    const [_, proxyInfo] = matchingProxy;
    const { target, serviceName } = proxyInfo;
    const requestId = `${request.socket.remoteAddress.replace(/[.:]/g, '-')}_${pathname.replace(/[\/?.]/g, '-')}_${Date.now()}`;
    
    // Create headers
    const headers = {
      ...request.headers,
      'x-source': 'gateway',
      'x-target': serviceName,
      'x-request-id': requestId,
      'x-gateway-timestamp': Date.now().toString()
    };

    // Create options
    const options = {
      host: target.host,
      port: target.port,
      path: pathname,
      headers: headers,
      method: 'GET'
    };

    // Create a proxy request
    const { request: httpRequest } = require('http');
    const proxyReq = httpRequest(options);
    
    proxyReq.on('upgrade', (proxyRes, proxySocket, proxyHead) => {
      // Connection established with the target
      socket.write(
        `HTTP/1.1 101 Switching Protocols\r\n` +
        `Upgrade: ${proxyRes.headers.upgrade}\r\n` +
        `Connection: Upgrade\r\n` +
        `Sec-WebSocket-Accept: ${proxyRes.headers['sec-websocket-accept']}\r\n` +
        `\r\n`
      );

      // Create connection object
      const connectionId = `${requestId}_${Date.now()}`;
      const connection = {
        id: connectionId,
        clientSocket: socket,
        serviceSocket: proxySocket,
        service: serviceName,
        path: pathname,
        clientIp: request.socket.remoteAddress,
        connectedAt: new Date(),
      };
      
      // Store in active connections map
      activeConnections.set(connectionId, connection);

      // Connect the client socket with the target socket
      proxySocket.pipe(socket);
      socket.pipe(proxySocket);

      // Handle errors and connection close
      proxySocket.on('error', (err) => {
        console.error(`WebSocket proxy target error for ${serviceName}:`, err, { connectionId });
        socket.destroy();
        cleanupConnection(connectionId);
      });

      socket.on('error', (err) => {
        console.error(`WebSocket client error for ${serviceName}:`, err, { connectionId });
        proxySocket.destroy();
        cleanupConnection(connectionId);
      });
      
      // Handle connection close from either side
      const closeHandler = () => {
        cleanupConnection(connectionId);
      };
      
      proxySocket.on('close', closeHandler);
      socket.on('close', closeHandler);
    });

    proxyReq.on('error', (err) => {
      console.error(`Failed to proxy WebSocket for ${serviceName}:`, err);
      socket.destroy();
    });

    proxyReq.end();
  });

  // Helper function to clean up a connection
  function cleanupConnection(connectionId) {
    if (activeConnections.has(connectionId)) {
      activeConnections.delete(connectionId);
    }
  }

  // Capture proxy errors
  fastify.setErrorHandler((error, request, reply) => {
    // Handle timeout errors
    if (error.code === "ETIMEDOUT") {
      console.error("Service timeout", {
        error: error.message,
        service: request.headers["x-target"],
      });

      reply.status(408).send({
        statusCode: 408,
        error: "Request Timeout",
        message: "Service took too long to respond",
      });
      return;
    }

    // Handle connection errors
    if (error.code === "ECONNREFUSED" || error.code === "ECONNRESET") {
      console.error("Service Unavailable", {
        error: error.message,
        service: request.headers["x-target"],
      });

      reply.status(503).send({
        statusCode: 503,
        error: "Service Unavailable",
        message: "Service temporarily unavailable",
      });
      return;
    }

    // For other errors, delegate to the global error handler
    reply.send(error);
  });
}

module.exports = fp(proxyPlugin, { name: "proxy" });
