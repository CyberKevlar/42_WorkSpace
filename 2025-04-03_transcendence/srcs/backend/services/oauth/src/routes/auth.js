const { access } = require("fs");
const jwt = require("./../plugins/jwt");

module.exports = async function (app) {
  const googleClientId = process.env.GOOGLE_CLIENT_ID;
  const googleClientSecret = process.env.GOOGLE_CLIENT_SECRET;
  const googleRedirectUri = process.env.GOOGLE_CLIENT_REDIRECT;

  let access_token;
  let loggedIn = new Map();

  app.get("/google", (req, reply) => {
    console.log("OAuth request received");
    reply.redirect(
      `https://accounts.google.com/o/oauth2/auth?client_id=${googleClientId}&redirect_uri=${googleRedirectUri}&response_type=code&scope=profile email`
    );
  });

  app.get("/callback", async (req, res) => {
    console.log(`\n-------------------------------`);
    console.log("\nHandling OAuth2 callback...");
    let code = req.query.code;
  
    try {
      const response = await fetch("https://oauth2.googleapis.com/token", {
        method: "POST",
        headers: {
          "Content-Type": "application/x-www-form-urlencoded",
        },
        body: new URLSearchParams({
          client_id: googleClientId,
          client_secret: googleClientSecret,
          redirect_uri: googleRedirectUri,
          code: code,
          grant_type: "authorization_code",
        }),
      });
  
      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`);
      }
  
      const responseBody = await response.json();
      access_token = responseBody.access_token;
  
      const userData = jwt.decodeToken(responseBody.id_token);
      console.log("🔓 Datos del usuario:", userData);
      console.log(`✅ Access token received\n`);
      console.log(`\n-------------------------------\n`);
  
      let user;
      user = await app.userDB.getUserByUsername(userData.name);
      if (!user) {
        console.log("🔐 Usuario no encontrado, creando nuevo usuario...");
        user = await app.userDB.createUser(userData.name, userData.sub, 1);
        console.log("✅ Nuevo usuario creado:", user);
      }
      

      loggedIn.set(code, true);
  
      const frontendHost =
        req.headers["x-forwarded-host"] ||
        req.headers.host ||
        "localhost";
  
      const redirectUrl = new URL(`https://${frontendHost}:8443`);
      res.redirect(redirectUrl.toString());
    } catch (error) {
      console.error("❌ Error during callback handling:", error.message);
      res.send("An error occurred");
    }
  });
};
