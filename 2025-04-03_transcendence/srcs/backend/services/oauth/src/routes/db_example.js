// Ejemplo de registro de rutas que utilizan el plugin de base de datos
module.exports = async function(fastify, opts) {
  fastify.get('/users_create', async (request, reply) => {
    let username = 'test_user';
    let email = 'test_email';

    console.log(`Intento de crear usuario: ${username} (${email})`);
    try {
      const newUser = await fastify.userDB.createUser(username, email);
      console.log(`Usuario creado exitosamente: ID ${newUser.id}, Username: ${newUser.username}`);
      reply.code(201).send(newUser);
    } catch (error) {
      console.error(`Error al crear usuario: ${error.message}`);
      reply.code(400).send({ error: error.message });
    }
  });

  // Crear un nuevo usuario
  fastify.post('/users', async (request, reply) => {
    const { username, email } = request.body;
    console.log(`Intento de crear usuario: ${username} (${email})`);
    try {
      const newUser = await fastify.userDB.createUser(username, email);
      console.log(`Usuario creado exitosamente: ID ${newUser.id}, Username: ${newUser.username}`);
      reply.code(201).send(newUser);
    } catch (error) {
      console.error(`Error al crear usuario: ${error.message}`);
      reply.code(400).send({ error: error.message });
    }
  });

  // Obtener usuario por ID
  fastify.get('/users/:id', async (request, reply) => {
    const { id } = request.params;
    console.log(`Buscando usuario con ID: ${id}`);
    const user = await fastify.userDB.getUserById(id);
    if (user) {
      console.log(`Usuario encontrado: ${user.username}`);
      reply.send(user);
    } else {
      console.warn(`Usuario con ID ${id} no encontrado`);
      reply.code(404).send({ error: 'Usuario no encontrado' });
    }
  });

  // Listar usuarios
  fastify.get('/users', async (request, reply) => {
    const { limit = 10, offset = 0 } = request.query;
    console.log(`Listando usuarios - Límite: ${limit}, Offset: ${offset}`);
    const users = await fastify.userDB.listUsers(limit, offset);
    console.log(`Usuarios recuperados: ${users.length}`);
    reply.send(users);
  });

  // Actualizar usuario
  fastify.put('/users/:id', async (request, reply) => {
    const { id } = request.params;
    const updates = request.body;
    console.log(`Intento de actualizar usuario ID: ${id}`, updates);
    try {
      const updatedUser = await fastify.userDB.updateUser(id, updates);
      console.log(`Usuario actualizado: ID ${id}, Nuevos datos:`, updatedUser);
      reply.send(updatedUser);
    } catch (error) {
      console.error(`Error al actualizar usuario ${id}: ${error.message}`);
      reply.code(400).send({ error: error.message });
    }
  });

  // Eliminar usuario
  fastify.delete('/users/:id', async (request, reply) => {
    const { id } = request.params;
    console.log(`Intento de eliminar usuario con ID: ${id}`);
    const deleted = await fastify.userDB.deleteUser(id);
    if (deleted) {
      console.log(`Usuario con ID ${id} eliminado exitosamente`);
      reply.code(204).send();
    } else {
      console.warn(`No se pudo eliminar usuario con ID ${id}`);
      reply.code(404).send({ error: 'Usuario no encontrado' });
    }
  });
};