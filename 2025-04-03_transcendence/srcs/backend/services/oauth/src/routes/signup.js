module.exports = async function (app) {
  
    app.post("/signup", async (req, reply) => {

    console.log("🔐 Solicitud de registro recibida");
    const { username, password, oauth } = req.body;
    
    try {
        console.log("🔐 Verificando datos de registro");
        console.log("\t username: ", username);
        console.log("\t password: ", password);
        console.log("\t oauth: ", oauth);

      // Llamar a getUserByUsername desde el plugin de base de datos
      const existingUser = await app.userDB.getUserByUsername(username);

      if (existingUser) {
        console.log("❌ Usuario ya existe");
        return reply.status(409).send({ error: "Usuario ya existe" });
      }

      // Crear nuevo usuario
      const newUser = await app.userDB.createUser(username, password, oauth);
      console.log("✅ Usuario creado:", newUser);
      reply.status(201).send({ status: "ok", user: newUser });




    } catch (error) {
      console.error("❌ Error al crear usuario:", error.message);
      reply.status(500).send({ error: "Error interno del servidor" })};

    });
  };