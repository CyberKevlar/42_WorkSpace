"use strict";

async function routes(fastify, options) {
  fastify.register(require("./health"));
  fastify.register(require("./auth"));
  fastify.register(require("./login"));
  fastify.register(require("./signup"));
  fastify.register(require("./db_example"));
}

module.exports = routes;