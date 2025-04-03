import { parentPort } from 'worker_threads';

function getRandomNumberInRange(min, max) {
    let rand = Math.floor(Math.random() * (max - min + 1)) + min;

    while (rand === 0)
        rand = Math.floor(Math.random() * (max - min + 1)) + min;
    return rand;
}


function scorePoints(ball, state) {
    if (ball.x >= 800) {
        state.score.right--;
        ball.x = 400;
        ball.y = 400;
        ball.dx = getRandomNumberInRange(-10, 10);
        ball.dy = getRandomNumberInRange(-10, 10);
    }
    else if (ball.x <= 0) {
        state.score.left--;
        ball.x = 400;
        ball.y = 400;
        ball.dx = getRandomNumberInRange(-10, 10);
        ball.dy = getRandomNumberInRange(-10, 10);
    }
    if (ball.y >= 800) {
        state.score.down--;
        ball.x = 400;
        ball.y = 400;
        ball.dx = getRandomNumberInRange(-10, 10);
        ball.dy = getRandomNumberInRange(-10, 10);
    }
    else if (ball.y <= 0) {
        state.score.up--;
        ball.x = 400;
        ball.y = 400;
        ball.dx = getRandomNumberInRange(-10, 10);
        ball.dy = getRandomNumberInRange(-10, 10);
    }
}

function checkColl(ball) {
    // Colisiones con esquina superior izquierda
    if (ball.y <= 100 && ball.x <= 100) {
        if (ball.y < ball.x)
            ball.dx *= -1;
        else if (ball.y < ball.x)
            ball.dy *= -1;
        else {
            ball.dx *= -1;
            ball.dy *= -1;
        }
    }
    // Colisiones con esquina inferior izquierda
    if (ball.y >= 700 && ball.x <= 100) {
        if (ball.y - 600 < ball.x)
            ball.dx *= -1;
        else if (ball.y - 600 > ball.x)
            ball.dy *= -1;
        else {
            ball.dx *= -1;
            ball.dy *= -1;
        }
    }
    // Colisiones con esquina superior derecha
    if (ball.y <= 100 && ball.x >= 700) {
        if (ball.y < ball.x - 600)
            ball.dx *= -1;
        else if (ball.y > ball.x - 600)
            ball.dy *= -1;
        else {
            ball.dx *= -1;
            ball.dy *= -1;
        }
    }
    // Colisiones con esquina superior derecha
    if (ball.y >= 700 && ball.x >= 700) {
        if (ball.y < ball.x)
            ball.dx *= -1;
        else if (ball.y > ball.x)
            ball.dy *= -1;
        else {
            ball.dx *= -1;
            ball.dy *= -1;
        }
    }
}

function checkPaddleColl(ball, state) {
    // Colisión con paleta izquierda
    if (((ball.x >= 45 && ball.x <= 55) || (state.paddlesLen.left === 300 && ball.x <= 100))
        && (ball.y >= state.paddles.left - (state.paddlesLen.left / 2) && ball.y <= state.paddles.left + (state.paddlesLen.left / 2))) {
        if (state.paddlesLen.left !== 300) {
            ball.dx = getRandomNumberInRange(5, 10);
            ball.dy = (ball.y - state.paddles.left) / 10;
        }
        else
            ball.dx *= -1;
    }

    // Colisión con paleta derecha
    if (((ball.x >= 745 && ball.x <= 755) || (state.paddlesLen.right === 300 && ball.x >= 700))
        && (ball.y >= state.paddles.right - (state.paddlesLen.right / 2) && ball.y <= state.paddles.right + (state.paddlesLen.right / 2))) {
        if (state.paddlesLen.right !== 300) {
            ball.dx = getRandomNumberInRange(-5, -10);
            ball.dy = (ball.y - state.paddles.right) / 10;
        }
        else
            ball.dx *= -1;
    }

    //colision con la paleta superior
    if (((ball.y >= 745 && ball.y <= 755) || (state.paddlesLen.down === 300 && ball.y >= 700))
        && (ball.x >= state.paddles.down - (state.paddlesLen.down / 2) && ball.x <= state.paddles.down + (state.paddlesLen.down / 2))) {
        if (state.paddlesLen.right !== 300) {
            ball.dy = getRandomNumberInRange(-5, -10);
            ball.dx = (ball.x - state.paddles.down) / 10;
        }
        else
            ball.dy *= -1;
    }
    //colision con la paleta inferior
    if (((ball.y >= 45 && ball.y <= 55) || (state.paddlesLen.up === 300 && ball.x <= 100))
        && (ball.x >= state.paddles.up - (state.paddlesLen.up / 2) && ball.x <= state.paddles.up + (state.paddlesLen.up / 2))) {
        if (state.paddlesLen.right !== 300) {
            ball.dy = getRandomNumberInRange(-5, -10);
            ball.dx = (ball.x - state.paddles.up) / 10;
        }
        else
            ball.dy *= -1;
    }
}

function localMultiplayerGameLogic(state) {
    parentPort.on('message', (message) => {
        if (message.type === 'PADDLE_UPDATE MULTI') {   
            if (state.score.right) state.paddles.right = message.right;
            if (state.score.left) state.paddles.left = message.left;
            if (state.score.up) state.paddles.up = message.up;
            if (state.score.down) state.paddles.down = message.down;
        }
    });

    let alive = 4;
    let interval = setInterval(() => {
        state.ball1.x += state.ball1.dx;
        state.ball1.y += state.ball1.dy;
        state.ball2.x += state.ball2.dx;
        state.ball2.y += state.ball2.dy;

        // Anotación de puntos
        scorePoints(state.ball1, state);
        scorePoints(state.ball2, state);
        // Colisiones con esquinas
        checkColl(state.ball1);
        checkColl(state.ball2);
        // Colisiones con las paletas
        checkPaddleColl(state.ball1, state);
        checkPaddleColl(state.ball2, state);
        // Verificar ganador y muertes
        if (state.score.left === 0 || state.score.right === 0 || state.score.up === 0 || state.score.down == 0) {
            alive--;
            if (state.score.left === 0) { state.score.left--; state.paddlesLen.left = 600}
            if (state.score.right === 0) { state.score.right--; state.paddlesLen.right = 600}
            if (state.score.up === 0) { state.score.up--; state.paddlesLen.up = 600}
            if (state.score.down === 0) { state.score.down--; state.paddlesLen.down = 600}
            if (alive === 1) {
                if (state.score.left > 0) state.winner = 'left';
                if (state.score.right > 0) state.winner = 'right';
                if (state.score.up > 0) state.winner = 'up';
                if (state.score.down > 0) state.winner = 'down';
                parentPort.postMessage({ type: 'UPDATE', state });
                parentPort.postMessage({ type: 'END', winner: state.winner });
                clearInterval(interval);
                return;
            }
            parentPort.postMessage({ type: 'UPDATE', state });
        }

        // Enviar el estado actualizado al proceso principal
        parentPort.postMessage({ type: 'UPDATE', state });
    }, 16);
}


function SologameLogic(state) {
    parentPort.on('message', (message) => {
        if (message.type === 'PADDLE_UPDATE') {
            state.paddles.right = message.right;
            state.paddles.left = message.left;
        }
    });

    let interval = setInterval(() => {
        state.ball.x += state.ball.dx;
        state.ball.y += state.ball.dy;

        // Anotación de puntos
        if (state.ball.x >= 800) {
            state.score.left++;
            state.ball.x = 400;
            state.ball.y = 300;
            state.ball.dx = getRandomNumberInRange(-10, 10);
            state.ball.dy = getRandomNumberInRange(-10, 10);
        }
        else if (state.ball.x <= 0) {
            state.score.right++;
            state.ball.x = 400;
            state.ball.y = 300;
            state.ball.dx = getRandomNumberInRange(-10, 10);
            state.ball.dy = getRandomNumberInRange(-10, 10);
        }
        // Colisiones con los límites en Y
        if (state.ball.y <= 0 || state.ball.y >= 600) state.ball.dy *= -1;

        // Colisión con paleta izquierda
        if ((state.ball.x >= 45 && state.ball.x <= 55)
            && (state.ball.y >= state.paddles.left - 50 && state.ball.y <= state.paddles.left + 50)) {
            state.ball.dx = getRandomNumberInRange(5, 10);
            state.ball.dy = (state.ball.y - state.paddles.left) / 10;
        }

        // Colisión con paleta derecha
        if ((state.ball.x >= 745 && state.ball.x <= 755)
            && (state.ball.y >= state.paddles.right - 50 && state.ball.y <= state.paddles.right + 50)) {
            state.ball.dx = getRandomNumberInRange(-5, -10);
            state.ball.dy = (state.ball.y - state.paddles.right) / 10;
        }

        // Verificar ganador
        if (state.score.left === 10 || state.score.right === 10) {
            state.winner = state.score.left === 10 ? 'left' : 'right';
            parentPort.postMessage({ type: 'UPDATE', state });
            parentPort.postMessage({ type: 'END', winner: state.winner });
            clearInterval(interval);
            return;
        }

        // Enviar el estado actualizado al proceso principal
        parentPort.postMessage({ type: 'UPDATE', state });
    }, 16);
}


function raycasting(ball) {
    let ballX = ball.x;
    let ballY = ball.y;
    let dX = ball.dx;
    let dY = ball.dy;

    while ((ballX >= 50 && ballX <= 750) && (ballY >= 0 && ballY <= 600)) {
        ballX += dX;
        ballY += dY;
    }
    return ballY;
}

function AIgameLogic(state) {
    parentPort.on('message', (message) => {
        if (message.type === 'PADDLE_UPDATE') {
            state.paddles.left = message.left;
        }
    });

    let counter = 0;
    let AIObj = 300;
    let interval = setInterval(() => {
        state.ball.x += state.ball.dx;
        state.ball.y += state.ball.dy;

        if (counter === 60) {
            counter = 0;
            AIObj = raycasting(state.ball);
        }
        if (AIObj >= state.paddles.right + 40) state.paddles.right += 10;
        if (AIObj <= state.paddles.right - 40) state.paddles.right -= 10;
        // Anotación de puntos
        if (state.ball.x >= 800) {
            state.score.left++;
            state.ball.x = 400;
            state.ball.y = 300;
            state.ball.dx = getRandomNumberInRange(-10, 10);
            state.ball.dy = getRandomNumberInRange(-10, 10);
        }
        else if (state.ball.x <= 0) {
            state.score.right++;
            state.ball.x = 400;
            state.ball.y = 300;
            state.ball.dx = getRandomNumberInRange(-10, 10);
            state.ball.dy = getRandomNumberInRange(-10, 10);
        }
        // Colisiones con los límites en Y
        if (state.ball.y <= 0 || state.ball.y >= 600) state.ball.dy *= -1;

        // Colisión con paleta izquierda
        if ((state.ball.x >= 45 && state.ball.x <= 55)
            && (state.ball.y >= state.paddles.left - 50 && state.ball.y <= state.paddles.left + 50)) {
            state.ball.dx = getRandomNumberInRange(5, 10);
            state.ball.dy = (state.ball.y - state.paddles.left) / 10;
        }

        // Colisión con paleta derecha
        if ((state.ball.x >= 745 && state.ball.x <= 755)
            && (state.ball.y >= state.paddles.right - 50 && state.ball.y <= state.paddles.right + 50)) {
            state.ball.dx = getRandomNumberInRange(-5, -10);
            state.ball.dy = (state.ball.y - state.paddles.right) / 10;
        }

        // Verificar ganador
        if (state.score.left === 10 || state.score.right === 10) {
            state.winner = state.score.left === 10 ? 'left' : 'right';
            parentPort.postMessage({ type: 'UPDATE', state });
            parentPort.postMessage({ type: 'END', winner: state.winner });
            clearInterval(interval);
            return;
        }

        counter++;
        // Enviar el estado actualizado al proceso principal
        parentPort.postMessage({ type: 'UPDATE', state });
    }, 16);
}

// Manejar mensajes desde el proceso principal
parentPort.on('message', (message) => {
    if (message.type === 'START SOLO-GAME') {
        let gameState = message.state;
        console.log('🎮 Juego iniciado (solo) en Worker con estado:', gameState);
        SologameLogic(gameState);
    }
    else if (message.type === 'START AI-GAME') {
        let gameState = message.state;
        console.log('🎮 Juego iniciado (AI) en Worker con estado:', gameState);
        AIgameLogic(gameState);
    }
    else if (message.type === 'MULTIPLAYER LOCAL-GAME') {
        let gameState = message.state;
        console.log('🎮 Juego iniciado (multiplayer local) en Worker con estado:', gameState);
        localMultiplayerGameLogic(gameState);
    }
});

parentPort.setMaxListeners(40);