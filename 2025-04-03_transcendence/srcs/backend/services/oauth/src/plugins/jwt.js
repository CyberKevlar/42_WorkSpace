const jwt = require("jsonwebtoken");
require("dotenv").config(); // Cargar variables de entorno

const JWT_SECRET = process.env.JWT_SECRET;

/**
 * Genera un JWT con los datos del usuario
 * @param {Object} payload - Datos del usuario (ej: { userId, email })
 * @param {String} expiresIn - Tiempo de expiración (ej: "7d", "1h")
 * @returns {String} Token JWT
 */
function generateToken(payload, expiresIn = "7d") {
  return jwt.sign(payload, JWT_SECRET, { expiresIn });
}

/**
 * Verifica la validez de un token JWT
 * @param {String} token - Token JWT recibido
 * @returns {Object|null} Datos del usuario si es válido, null si no
 */
function verifyToken(token) {
  try {
    return jwt.verify(token, JWT_SECRET);
  } catch (error) {
    console.error("❌ Error verificando JWT:", error.message);
    return null;
  }
}

/**
 * Decodifica un token JWT sin verificar su firma
 * @param {String} token - Token JWT recibido
 * @returns {Object|null} Datos del token si es válido, null si hay error
 */
function decodeToken(token) {
  try {
    return jwt.decode(token);
  } catch (error) {
    console.error("❌ Error decodificando JWT:", error.message);
    return null;
  }
}

module.exports = { generateToken, verifyToken, decodeToken };
