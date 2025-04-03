import { WebSocketServer } from 'ws';
import dotenv from 'dotenv';
import { Worker, isMainThread, parentPort } from 'worker_threads';
import { createServer } from 'http';
import events from 'events';

dotenv.config({ path: '../../.env' });
const PORT = process.env.PORT || 8080;


// Crear un servidor HTTP base
const server = createServer();

// Montar el servidor WebSocket sobre el servidor HTTP
const wss = new WebSocketServer({ server });

let games = new Map(); // Array para almacenar los juegos activos


function handleMultiPaddles(id, worker) {
	let game = games.get(id).state;
	let ws = games.get(id).ws;
	ws.on('message', (message) => {
		const parsedMessage = message.toString();
		if (parsedMessage === 'r-up' && game.paddles.right >= 150) {
			game.paddles.right -= 10;
		}
		else if (parsedMessage === 'r-down' && game.paddles.right <= 650) {
			game.paddles.right += 10;
		}
		else if (parsedMessage === 'l-up' && game.paddles.left >= 150) {
			game.paddles.left -= 10;
		}
		else if (parsedMessage === 'l-down' && game.paddles.left <= 650) {
			game.paddles.left += 10;
		}
		else if (parsedMessage === 'u-right' && game.paddles.right <= 650) {
			game.paddles.up += 10;
		}
		else if (parsedMessage === 'u-left' && game.paddles.right >= 150) {
			game.paddles.up -= 10;
		}
		else if (parsedMessage === 'd-right' && game.paddles.left <= 650) {
			game.paddles.down += 10;
		}
		else if (parsedMessage === 'd-left' && game.paddles.left >= 150) {
			game.paddles.down -= 10;
		}
		worker.postMessage({ type: 'PADDLE_UPDATE MULTI', left: game.paddles.left, right: game.paddles.right });
	});
}

function handlePaddles(id, worker) {
	let game = games.get(id).state;
	let ws = games.get(id).ws;
	ws.on('message', (message) => {
		const parsedMessage = message.toString();
		if (parsedMessage === 'r-up' && game.paddles.right >= 50) {
			game.paddles.right -= 10;
		}
		else if (parsedMessage === 'r-down' && game.paddles.right <= 550) {
			game.paddles.right += 10;
		}
		else if (parsedMessage === 'l-up' && game.paddles.left >= 50) {
			game.paddles.left -= 10;
		}
		else if (parsedMessage === 'l-down' && game.paddles.left <= 550) {
			game.paddles.left += 10;
		}
		worker.postMessage({ type: 'PADDLE_UPDATE', left: game.paddles.left, right: game.paddles.right });
	});
}

function getRandomNumberInRange(min, max) {
    let rand = Math.floor(Math.random() * (max - min + 1)) + min;

    while (rand === 0)
        rand = Math.floor(Math.random() * (max - min + 1)) + min;
    return rand;
}


function startGame(id) {
  return {
    id: id,
    ball: { x: 400, y: 300, dx: getRandomNumberInRange(-5, 5), dy: getRandomNumberInRange(-5, 5) }, // Posición y dirección de la bola
    paddles: { 
      left: 300 ,                      // Posición paleta izquierda
      right:300                       // Posición paleta derecha
    },
    score: { left: 0, right: 0 },             // Marcador inicial
	winner: null
};
}

function startMultiGame(id) {
	return {
	  id: id,
	  ball1: { x: 400, y: 400, dx: getRandomNumberInRange(-5, 5), dy: getRandomNumberInRange(-5, 5) }, // Posición y dirección de la bola
	  ball2: { x: 400, y: 400, dx: getRandomNumberInRange(-5, 5), dy: getRandomNumberInRange(-5, 5) },
	  paddles: { 
		left: 400 ,                      // Posición paleta izquierda
		right:400 ,                     // Posición paleta derecha
		up:   400 ,
		down: 400
	},
	paddlesLen: { 
		left: 100 ,                      // Posición paleta izquierda
		right:100 ,                     // Posición paleta derecha
		up:   100 ,
		down: 100
	},
	  score: { left: 10, right: 10, up: 10, down: 10 },             // Marcador inicial
	  winner: null
  };
  }

wss.on('connection', (ws) => {
	console.log('🎮 Nuevo jugador conectado');

	ws.on('message', (message) => {
		const parsedMessage = message.toString();
		if (parsedMessage === 'new solo-game') {
  			const worker = new Worker('./worker.js', { type: 'module' });
			const actualId = games.size;
			games.set(actualId, { worker: worker, ws: ws, state: startGame(actualId) });
			worker.setMaxListeners(20);
			worker.postMessage({ type: 'START SOLO-GAME', state: games.get(actualId).state});
			ws.send('Game created succesfully');
			handlePaddles(actualId, worker);
			worker.on('message', (message) => {
				if (message.type === 'UPDATE') {
					sendto(actualId, JSON.stringify(message.state)); // Envía estado actualizado al cliente
				} else if (message.type === 'END') {
					console.log(`🏆 Ganador de la partida ${actualId}: ${message.winner}`);
					worker.terminate();
				}
			});
		}
		else if (parsedMessage === 'new AI-game') {
			const worker = new Worker('./worker.js', { type: 'module' });
			const actualId = games.size;
			games.set(actualId, { worker: worker, ws: ws, state: startGame(actualId) });
			worker.setMaxListeners(20);
			worker.postMessage({ type: 'START AI-GAME', state: games.get(actualId).state});
			ws.send('Game created succesfully');
			handlePaddles(actualId, worker);
			worker.on('message', (message) => {
				if (message.type === 'UPDATE') {
					sendto(actualId, JSON.stringify(message.state)); // Envía estado actualizado al cliente
				} else if (message.type === 'END') {
					console.log(`🏆 Ganador de la partida ${actualId}: ${message.winner}`);
					worker.terminate();
				}
			});
		}
		else if (parsedMessage === 'new remote-game') {

		}
		else if (parsedMessage === 'new multiplayer-game (local)') {
			const worker = new Worker('./worker.js', { type: 'module' });
			const actualId = games.size;
			games.set(actualId, { worker: worker, ws: ws, state: startMultiGame(actualId) });
			worker.setMaxListeners(20);
			worker.postMessage({ type: 'MULTIPLAYER LOCAL-GAME', state: games.get(actualId).state});
			ws.send('Game created succesfully');
			handleMultiPaddles(actualId, worker);
			worker.on('message', (message) => {
				if (message.type === 'UPDATE') {
					sendto(actualId, JSON.stringify(message.state)); // Envía estado actualizado al cliente
				} else if (message.type === 'END') {
					console.log(`🏆 Ganador de la partida ${actualId}: ${message.winner}`);
					worker.terminate();
				}
			});
		}
		else if (parsedMessage === 'new multiplayer-game (remote)') {

		}
	});

	ws.on('close', () => console.log('🚪 Jugador desconectado'));
});

function sendto(clientid, state) {
  games.get(clientid).ws.send(state);
}

server.listen(PORT, () => {
	console.log(`🚀 Servidor WebSocket corriendo en puerto ${PORT}`);
  });