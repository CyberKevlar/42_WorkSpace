//import { useEffect, useState } from "react";
//
//const Game = () => {
//  const [playerY, setPlayerY] = useState(150); // Paleta izquierda (AI)
//  const [aiY, setAiY] = useState(150); // Paleta derecha (AI)
//  const [ball, setBall] = useState({ x: 390, y: 190, vx: 4, vy: 4 });
//  const [playerScore, setPlayerScore] = useState(0); // Puntuación del jugador izquierdo
//  const [aiScore, setAiScore] = useState(0); // Puntuación del jugador derecho
//
//  useEffect(() => {
//    const gameLoop = setInterval(() => {
//      setBall((prevBall) => {
//        let { x, y, vx, vy } = prevBall;
//
//        // Movimiento de la pelota
//        x += vx;
//        y += vy;
//
//        // Colisión con las paredes superior e inferior
//        if (y <= 0 || y >= 380) {
//          vy *= -1;
//        }
//
//        // Colisión con la paleta izquierda (AI)
//        if (x <= 20 && y >= playerY && y <= playerY + 100) {
//          vx *= -1;
//        }
//
//        // Colisión con la paleta derecha (AI)
//        if (x >= 760 && y >= aiY && y <= aiY + 100) {
//          vx *= -1;
//        }
//
//        // La pelota sale por la izquierda
//        if (x <= 0) {
//          setAiScore((score) => score + 1);
//          return { x: 390, y: 190, vx: 4, vy: 4 }; // Reinicia la pelota
//        }
//
//        // La pelota sale por la derecha
//        if (x >= 780) {
//          setPlayerScore((score) => score + 1);
//          return { x: 390, y: 190, vx: -4, vy: 4 }; // Reinicia la pelota
//        }
//
//        return { x, y, vx, vy };
//      });
//
//      // Movimiento automático de la paleta izquierda (AI)
//      setPlayerY((prevPlayerY) => {
//        if (ball.y > prevPlayerY + 50) return Math.min(prevPlayerY + 4, 300);
//        if (ball.y < prevPlayerY + 50) return Math.max(prevPlayerY - 4, 0);
//        return prevPlayerY;
//      });
//
//      // Movimiento automático de la paleta derecha (AI)
//      setAiY((prevAiY) => {
//        if (ball.y > prevAiY + 50) return Math.min(prevAiY + 4, 300);
//        if (ball.y < prevAiY + 50) return Math.max(prevAiY - 4, 0);
//        return prevAiY;
//      });
//    }, 16);
//
//    return () => clearInterval(gameLoop);
//  }, [ball]);
//
//  return (
//    <div className="relative mx-auto mt-10 h-[400px] w-[800px] bg-black border-2 border-white overflow-hidden">
//      {/* Marcador del jugador (izquierda) */}
//      <div
//        className="absolute top-2 left-[20%] transform -translate-x-1/2 text-white text-6xl font-bold"
//        style={{ fontFamily: "monospace", letterSpacing: "0.2em", lineHeight: "1.5em" }}
//      >
//        {playerScore}
//      </div>
//
//      {/* Marcador de la IA (derecha) */}
//      <div
//        className="absolute top-2 right-[20%] transform translate-x-1/2 text-white text-6xl font-bold"
//        style={{ fontFamily: "monospace", letterSpacing: "0.2em", lineHeight: "1.5em" }}
//      >
//        {aiScore}
//      </div>
//
//      {/* Línea discontinua en el centro */}
//      <div className="absolute left-1/2 transform -translate-x-1/2 h-full w-[4px] bg-transparent">
//        <div className="h-full w-full bg-[repeating-linear-gradient(white_0_10px,transparent_10px_20px)]"></div>
//      </div>
//
//      {/* Paleta izquierda (AI) */}
//      <div
//        className="absolute left-2 w-[10px] h-[100px] bg-white"
//        style={{ top: `${playerY}px` }}
//      ></div>
//
//      {/* Paleta derecha (AI) */}
//      <div
//        className="absolute right-2 w-[10px] h-[100px] bg-white"
//        style={{ top: `${aiY}px` }}
//      ></div>
//
//      {/* Pelota */}
//      <div
//        className="absolute w-[20px] h-[20px] bg-white"
//        style={{ left: `${ball.x}px`, top: `${ball.y}px` }}
//      ></div>
//    </div>
//  );
//};
//
//export default Game;
//*/

import { useEffect, useState, useRef } from "react";
import { useSearchParams } from "react-router-dom";

const Game = () => {
  const [searchParams] = useSearchParams();
  const [ball, setBall] = useState({ x: 400, y: 200 });
  const [ball1, setBall1] = useState({ x: 400, y: 200 });
  const [ball2, setBall2] = useState({ x: 400, y: 200 });
  const [player1, setPlayer1] = useState(250);
  const [player2, setPlayer2] = useState(250);
  const [player3, setPlayer3] = useState(250);
  const [player4, setPlayer4] = useState(250);
  const [player1Score, setPlayer1Score] = useState(0);
  const [player2Score, setPlayer2Score] = useState(0);
  const [player3Score, setPlayer3Score] = useState(0);
  const [player4Score, setPlayer4Score] = useState(0);
  const [winner, setWinner] = useState<string | null>(null); // Evento de estado para el ganador.
  const [keysPressed, setKeysPressed] = useState<Set<string>>(new Set()); // Evento de estado para controlar las teclas presionadas.

  const players = searchParams.get("players"); // Variable para guardar el numero de jugadores para el boton del menu.
  const socketRef = useRef<WebSocket | null>(null); // Variable para guardar el websocket.
  const SCORE_LIMIT = 10; // Limite de puntuación para ganar.

  // Conexion del websocket y recepcion de datos del backend.
  useEffect(() => {
    const socket = new WebSocket("ws://localhost:4002");
    socketRef.current = socket; // Aqui guardamos el websocket en la referencia.

    socket.onopen = () => {
      if (players === "1") {
        socket.send("new AI-game");
      } else if (players === "2") {
        socket.send("new solo-game");
      } else if (players === "3") {
        socket.send("new multiplayer-game (local)");
      }
      console.log("🔗 Conexión WebSocket establecida");
    };

    socket.onmessage = (event) => {
      const data = JSON.parse(event.data);
      console.log("📩 Mensaje recibido:", event.data);

      // Actualizamos el estado del juego con los datos recibidos del backend.
      setBall(data.ball);
      setBall1(data.ball1);
      setBall2(data.ball2);
      setPlayer1(data.paddles.left);
      setPlayer2(data.paddles.right);
      setPlayer3(data.paddles.up);
      setPlayer4(data.paddles.down);
      setPlayer1Score(data.score.left);
      setPlayer2Score(data.score.right);
      setPlayer3Score(data.score.up);
      setPlayer4Score(data.score.down);

      console.log(event.data);

      // Verificamos si alguien ha ganado, y de gratis imprimimos un console.log para debug del que este mirando logs en el backend.
      if (data.score.left >= SCORE_LIMIT) {
        console.log("Jugador 1 ha ganado");
        setWinner("Jugador 1");
      } else if (data.score.right >= SCORE_LIMIT) {
        console.log("Jugador 2 ha ganado");
        setWinner("Jugador 2");
      } else if (data.score.up >= SCORE_LIMIT) {
        console.log("Jugador 3 ha ganado");
        setWinner("Jugador 3");
      } else if (data.score.down >= SCORE_LIMIT) {
        console.log("Jugador 4 ha ganado");
        setWinner("Jugador 4");
      }
    };

    socket.onerror = (error) => {
      console.error("❌ Error en el WebSocket:", error);
    };

    // Limpiamos conexión al desmontar el componente para evitar fugas de memoria (pura seguridad porsi porsi).
    return () => {
      socket.close();
    };
  }, []);

  // Manejamos las teclas presionadas y "despresionadas".
  useEffect(() => {
    const handleKeyDown = (event: KeyboardEvent) => {
      setKeysPressed((prev) => new Set(prev).add(event.key)); // Aqui agregamos la tecla al estado.
    };

    const handleKeyUp = (event: KeyboardEvent) => {
      setKeysPressed((prev) => {
        const newKeys = new Set(prev);
        newKeys.delete(event.key); // Aqui eliminamos la tecla del estado.
        return newKeys;
      });
    };

    // Actualizamos el estado de las teclas presionadas.
    window.addEventListener("keydown", handleKeyDown);
    window.addEventListener("keyup", handleKeyUp);

    // Limpiamos los eventos al desmontar el componente, en este caso el de las teclas.
    return () => {
      window.removeEventListener("keydown", handleKeyDown);
      window.removeEventListener("keyup", handleKeyUp);
    };
  }, []);

  // Enviamos comandos al backend en función de las teclas presionadas.
  useEffect(() => {

    const updateMovement = () => {
      const socket = socketRef.current; // Usamos el websocket de referencia que teniamos guardado.
      if (!socket || socket.readyState !== WebSocket.OPEN) return; // Verificamos si el websocket esta abierto, y enviamos el mensaje de tecla.
      if (keysPressed.has("w")) {
        socket.send("l-up");
      }
      if (keysPressed.has("s")) {
        socket.send("l-down");
      }
      if (keysPressed.has("ArrowUp")) {
        socket.send("r-up");
      }
      if (keysPressed.has("ArrowDown")) {
        socket.send("r-down");
      }
      if (keysPressed.has("c")) {
        socket.send("u-left");
      }
      if (keysPressed.has("v")) {
        socket.send("u-right");
      }
      if (keysPressed.has("n")) {
        socket.send("d-left");
      }
      if (keysPressed.has("m")) {
        socket.send("d-right");
      }
    };

    const interval = setInterval(updateMovement, 16); // Actualizamos el movimiento cada 16ms (= 60fps mas o menos).

    // Limpiamos intervalo.
    return () => clearInterval(interval);
  }, [keysPressed]); // Dejamos en escucha de cambios las teclas presionadas.

  // Renderizamos el juego.
  if (players === "3")
  {
    return (
      <div className="relative mx-auto mt-10 h-[610px] w-[800px] bg-black border-2 border-white overflow-hidden"
        style={{clipPath: "polygon(10% 0%, 90% 0%, 100% 10%, 100% 90%, 90% 100%, 10% 100%, 0% 90%, 0% 10%)",}}>
        <div
          className="absolute top-2 left-[25%] transform -translate-x-1/2 text-white text-6xl font-bold"
          style={{ fontFamily: "monospace", letterSpacing: "0.2em", lineHeight: "1.5em" }}>
          {player1Score}
        </div>
        <div
          className="absolute top-2 right-[25%] transform translate-x-1/2 text-white text-6xl font-bold"
          style={{ fontFamily: "monospace", letterSpacing: "0.2em", lineHeight: "1.5em" }}>
          {player2Score}
        </div>
        
        <div className="absolute left-1/2 transform -translate-x-1/2 h-full w-[4px] bg-transparent">
          <div className="h-full w-full bg-[repeating-linear-gradient(white_0_10px,transparent_10px_20px)]"></div>
        </div>
        <div
          className="absolute w-[10px] h-[100px] bg-white"
          style={{ top: `${player1 - 50}px`, left: `40px` }}>
        </div>
        <div
          className="absolute w-[10px] h-[100px] bg-white"
          style={{ top: `${player2 - 50}px`, right: `40px` }}>
        </div>
        <div
          className="absolute w-[100px] h-[10px] bg-white"
          style={{ top: `40px`, left: `${player3 - 50}px` }}>
        </div>
        <div
          className="absolute w-[100px] h-[10px] bg-white"
          style={{ bottom: `40px`, left: `${player4 - 50}px` }}>
        </div>
        <div
          className="absolute w-[20px] h-[20px] bg-white"
          style={{
            top: `${Math.max(0, Math.min(590, ball1.y - 10))}px`,
            left: `${Math.max(0, Math.min(780, ball1.x - 10))}px`,
          }}>
        </div>
        <div
          className="absolute w-[20px] h-[20px] bg-white"
          style={{
            top: `${Math.max(0, Math.min(590, ball2.y - 10))}px`,
            left: `${Math.max(0, Math.min(780, ball2.x - 10))}px`,
          }}>
        </div>
        {winner && (
          <div className="absolute inset-0 bg-black bg-opacity-75 flex items-center justify-center z-50">
            <div className="text-white text-4xl font-bold">
              ¡{winner} HA GANADO!
            </div>
          </div>
        )}
      </div>
    );
  }
  else if (players === "1" || players === "2")
  {
    console.log("Modo de juego: " + players);
    return (
      <div className="relative mx-auto mt-10 h-[610px] w-[800px] bg-black border-2 border-white overflow-hidden">
        <div
          className="absolute top-2 left-[25%] transform -translate-x-1/2 text-white text-6xl font-bold"
          style={{ fontFamily: "monospace", letterSpacing: "0.2em", lineHeight: "1.5em" }}>
          {player1Score}
        </div>
        <div
          className="absolute top-2 right-[25%] transform translate-x-1/2 text-white text-6xl font-bold"
          style={{ fontFamily: "monospace", letterSpacing: "0.2em", lineHeight: "1.5em" }}>
          {player2Score}
        </div>
        <div className="absolute left-1/2 transform -translate-x-1/2 h-full w-[4px] bg-transparent">
          <div className="h-full w-full bg-[repeating-linear-gradient(white_0_10px,transparent_10px_20px)]"></div>
        </div>
        <div
          className="absolute w-[10px] h-[100px] bg-white"
          style={{ top: `${player1 - 50}px`, left: `40px` }}></div>
        <div
          className="absolute w-[10px] h-[100px] bg-white"
          style={{ top: `${player2 - 50}px`, left: `750px` }}></div>
        <div
          className="absolute w-[20px] h-[20px] bg-white"
          style={{
            top: `${Math.max(0, Math.min(590, ball.y - 10))}px`,
            left: `${ball.x - 10}px`,
          }}>
        </div>
        {winner && (
          <div className="absolute inset-0 bg-black bg-opacity-75 flex items-center justify-center z-50">
            <div className="text-white text-4xl font-bold">
              ¡{winner} HA GANADO!
            </div>
          </div>
        )}
      </div>
    );
  }
  else {
    console.log("Modo de juego: " + players);
    return (
      <div className="flex items-center justify-center h-screen">
        <p className="text-white text-2xl">Error: Modo de juego no válido</p>
      </div>
    );
  }
}

export default Game;