"use strict";

require("dotenv").config();

const config = {
  // Server
  serviceName: (process.env.SERVICE_URL && process.env.SERVICE_URL.split(":")[0]) || "gateway",
  port: (process.env.SERVICE_URL && process.env.SERVICE_URL.split(":")[1]) || 3000,
  host: "0.0.0.0", version: "1.0",

  // Services
  services: {
    oauth: {
      name: "oauth",
      url: process.env.AUTH_SERVICE_URL || "http://oauth:4000",
      prefix: "/oauth",
      timeout: 5000,
    },
    game: {
      name: "game",
      url: process.env.GAME_SERVICE_URL || "http://game:8080",
      prefix: "/game",
      wsEnabled: true,
      timeout: 5000,
    },
  },
  routeMap: {
    "/oauth": "oauth",
    "/game": "game",
  },

  // CORS
  cors: {
    origin: true,
    methods: ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS"],
    allowedHeaders: ["Content-Type", "Authorization"],
    credentials: true,
  },

  helmet: {
    // Disable CSP since we are not serving HTML/CSS/JS content directly
    contentSecurityPolicy: false,

    // Disable Frameguard since we are not serving content that can be embedded in iframes
    frameguard: false,

    // Protection against XSS
    xssFilter: true,

    // Prevent MIME sniffing
    noSniff: true,

    // Hide server information
    hidePoweredBy: true,

    // Control referrer policy
    referrerPolicy: {
      policy: "no-referrer",
    },

    // Cross-origin resource policies
    crossOriginResourcePolicy: {
      policy: "same-site",
    },

    // Disable unnecessary policies for API
    crossOriginEmbedderPolicy: false,
    crossOriginOpenerPolicy: false,

    // Add HSTS (even though behind nginx)
    strictTransportSecurity: {
      maxAge: 15552000, // 180 days
      includeSubDomains: true,
      preload: true,
    },

    // Prevent DNS prefetching
    dnsPrefetchControl: {
      allow: false,
    },
  },
};

module.exports = config;
