module.exports = async function (app) {
  let loggedIn = new Map();

  app.post("/login", async (req, reply) => {
    console.log("🔐 Solicitud de login recibida");

    const { username, password } = req.body;

    try {
      // Llamar a getUserByUsername desde el plugin de base de datos
      const user = await app.userDB.getUserByUsername(username);
      console.log("🔐 Verificando datos de login")
      console.log("\t username: ", username);

      if (!user) {
        console.log("❌ Usuario no encontrado");
        return reply.status(404).send({ error: "Usuario no encontrado" });
      }


      console.log("✅ Usuario encontrado:", user);

      // NO se debe autenticar un usuario de oauth con contraseña
      if (user.oauth != 0) {
        console.log("❌ Usuario de OAuth no puede usar contraseña");
        return reply.status(403).send({ error: "Usuario de OAuth no puede usar contraseña" });
      }

      // Comprobar contraseña
      const isValid = await app.userDB.checkPassword(username, password);
      if (!isValid) {
        console.log("❌ Contraseña incorrecta");
        return reply.status(401).send({ error: "Contraseña incorrecta" });
      }

      console.log("✅ Contraseña correcta");
      //loggedIn.set(username, true); // Guardar el estado de login en la sesión
      console.log("✅ Usuario autenticado:", user);
      reply.send({ status: "ok", user });
    } catch (error) {
      console.error("❌ Error al buscar usuario:", error.message);
      reply.status(500).send({ error: "Error interno del servidor" });
    }
  });
};