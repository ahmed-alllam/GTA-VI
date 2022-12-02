const express = require("express");
const router = express.Router();
const mongoose = require("mongoose");
const Game = require("../models/game");
const Player = require("../models/player");
// const socketIO = require("socket.io");
const http = require("http");
// use websocket
const WebSocket = require("ws");

const app = express();
let server = http.createServer(app);
const wss = new WebSocket.Server({ server });


// make an array of default of positions of players
let defaultPositions = [
    { x: 5, y: 3, direction: 0 },
    { x: 6, y: 10, direction: 1 },
    { x: 2, y: 10, direction: 1 },
    { x: 8, y: 4, direction: 0 },
];

// make an array of default of positions of bullets
let defaultBullets = [
    { x: 1, y: 1},
    { x: 10, y: 14},
    { x: 10, y: 1},
    { x: 1, y: 14},
    { x: 3, y: 6},
    { x: 1, y: 6},
];

// make an array of default of positions of pellets
let defaultPellets = [
    { x: 9, y: 1},
    { x: 4, y: 14},
    { x: 7, y: 13},
    { x: 9, y: 9},
    { x: 10, y: 4},
    { x: 2, y: 3},
];


// when a new connection is made
wss.on("connection", ws => {
    // when a message is received
    // give each player a random id
    let playerId = Math.floor(Math.random() * 1000000000);
    ws.playerId = playerId;

    ws.on("message", message => {
        // parse the message
        const data = JSON.parse(message);
        // check the type of message
        switch (data.type) {
            // when a player joins a game
            case "joinGame":
                // find the game
                Game
                    .findOne({
                        id: data
                            .game.gameId
                    })
                    .exec()
                    .then(game => {
                        // check the game exists
                        if (game) {
                            // check the game is waiting
                            if (game.state === "waiting" || (game.state === "playing" && game.players.length < 4)) {
                                // todo: check the player is not already in the game

                                for (let i = 0; i < game.players.length; i++) {
                                    if (game.players[i].id === data.playerId) {
                                        ws.send(JSON.stringify({
                                            type: "error",
                                            message: "Player is already in game",
                                        }));
                                        return;
                                    }
                                }

                                // check game is not full
                                if (game.players.length < 4) {
                                    // add the player to the game
                                    game.players.push({
                                        id: data.playerId,
                                        score: 0,
                                        x: defaultPositions[game.players.length].x,
                                        y: defaultPositions[game.players.length].y,
                                        direction: defaultPositions[game.players.length].direction,
                                    });


                                    if (game.players.length >= 2) {
                                        game.state = "playing";
                                        // todo: start game
                                    } else {
                                        game.state = "waiting";
                                    }

                                    console.log(ws.playerId);
                                    game.players_ids.push(ws.playerId);

                                    // save the game
                                    game
                                        .save()
                                        .then(result => {
                                            // emit the game to the requesting player
                                            if (game.state === "playing") {
                                                wss.clients.forEach(client => {
                                                    if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                                        client.send(JSON.stringify({
                                                            type: "gameStarted",
                                                            game: game
                                                        }));
                                                    }
                                                });
                                            } else if (game.state === "waiting") {
                                                // if state is waiting, send the game
                                                ws.send(JSON.stringify({
                                                    type: "gameJoined",
                                                    game: game
                                                }));
                                            }
                                        })
                                        .catch(err => {
                                            console.log(err);
                                        });
                                } else {
                                    // emit error message
                                    ws.send(JSON.stringify({
                                        type: "error",
                                        message: "Game is full",
                                    }));
                                }

                            } else {
                                // emit error message
                                ws.send(JSON.stringify({
                                    type: "error",
                                    message: "Game is not waiting",
                                }));
                            }
                        } else {
                            // emit error message
                            ws.send(JSON.stringify({
                                type: "error",
                                message: "Game not found",
                            }));
                        }
                    })
                    .catch(err => {
                        console.log(err);
                        ws.send(JSON.stringify({
                            type: "error",
                            message: "An error ecurred " + err.message,
                        }));
                    });
                break;
            // when a player leaves a game
            case "leaveGame":
                // find the game
                Game
                    .findOne({
                        id: data
                            .game.gameId
                    })
                    .exec()
                    .then(game => {
                        // check the game exists
                        if (game) {
                            // check the game is waiting
                            if (game.state === "waiting") {
                                // check the player is in the game
                                if (game.players.indexOf(data.playerId) !== -1) {
                                    // remove the player from the game
                                    game.players.splice(game.players.indexOf(data.playerId), 1);
                                    // save the game
                                    game
                                        .save()
                                        .then(result => {
                                            // emit the game to all players in the same game instance
                                            wss.clients.forEach(client => {
                                                if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                                    client.send(JSON.stringify({
                                                        type: "game",
                                                        game: result,
                                                    }));
                                                }
                                            });
                                        })
                                        .catch(err => {
                                            console.log(err);
                                        });
                                } else {
                                    // emit error message
                                    ws.send(JSON.stringify({
                                        type: "error",
                                        message: "Player is not in game",
                                    }));
                                }
                            } else {
                                // emit error message
                                ws.send(JSON.stringify({
                                    type: "error",
                                    message: "Game is not waiting",
                                }));
                            }
                        } else {
                            // emit error message
                            ws.send(JSON.stringify({
                                type: "error",
                                message: "Game not found",
                            }));
                        }
                    })
                    .catch(err => {
                        console.log(err);
                        ws.send(JSON.stringify({
                            type: "error",
                            message: "Game not found",
                        }));
                    });
                break;
            // when a player updates a game
            case "updateGame":
                // find the game
                Game
                    .findOne({
                        id: data
                            .game.gameId
                    })
                    .exec()
                    .then(game => {
                        // check the game exists
                        if (game) {
                            // check the game is waiting
                            if (game.state === "waiting") {
                                // check the player is in the game
                                if (game.players.indexOf(data.playerId) !== -1) {
                                    // update the game
                                    game.name = data.game.name;
                                    game.state = data.game.state;
                                    // save the game
                                    game
                                        .save()
                                        .then(result => {
                                            // emit the game to all players in the same game instance
                                            wss.clients.forEach(client => {
                                                if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                                    client.send(JSON.stringify({
                                                        type: "game",
                                                        game: result,
                                                    }));
                                                }
                                            });
                                        })
                                        .catch(err => {
                                            console.log(err);
                                        });
                                } else {
                                    // emit error message

                                    ws.send(JSON.stringify({
                                        type: "error",
                                        message: "Player is not in game",
                                    }));
                                }
                            } else {
                                // emit error message
                                ws.send(JSON.stringify({
                                    type: "error",
                                    message: "Game is not waiting",
                                }));
                            }
                        } else {
                            // emit error message
                            ws.send(JSON.stringify({
                                type: "error",
                                message: "Game not found",
                            }));
                        }
                    })
                    .catch(err => {
                        console.log(err);
                        ws.send(JSON.stringify({
                            type: "error",
                            message: "Game not found",
                        }));
                    });
                break;
                // end  todo
                c
            // when player makes a move
            case "move":
                // find the game
                Game
                    .findOne({
                        id: data
                            .game.gameId
                    })
                    .exec()
                    .then(game => {
                        // check the game exists
                        if (game) {
                            // check the game is in progress
                            if (game.state === "playing") {
                                // loop over the players and check if one had the same id as the player who made the move
                                for (let i = 0; i < game.players.length; i++) {
                                    if (game.players[i].id === data.playerId) {
                                        // check the player is the current player
                                        // update the players position in the game

                                        console.log("before" + game.players[i]);

                                        game.players.set(i, {
                                            id: game.players[i].id,
                                            score: game.players[i].score,
                                            bullets: game.players[i].bullets,
                                            health: game.players[i].health,
                                            isPowerful: game.players[i].isPowerful,
                                            x: data.player.x,
                                            y: data.player.y,
                                            direction: data.player.direction,
                                        });

                                        console.log("after" + game.players[i]);

                                        game.save()
                                            .then(result => {
                                                wss.clients.forEach(client => {
                                                    if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                                        client.send(JSON.stringify({
                                                            type: "gameUpdated",
                                                            game: result,
                                                        }));
                                                    }
                                                });
                                            })
                                            .catch(err => {
                                                console.log(err);
                                            });
                                        break;
                                    }
                                }
                            } else {
                                // emit error message
                                ws.send(JSON.stringify({
                                    type: "error",
                                    message: "Game is not in progress",
                                }));
                            }
                        } else {
                            // emit error message
                            ws.send(JSON.stringify({
                                type: "error",
                                message: "Game not found",
                            }));
                        }
                    })
                    .catch(err => {
                        console.log(err);
                        ws.send(JSON.stringify({
                            type: "error",
                            message: "Game not found",
                        }));
                    });
                break;
            default:
                break;
        }
    });

    // every 4000ms, add a new random bullet and pellet to the game and emit the game to all players in the game
    setInterval(() => {
        Game
            .find({
                state: "playing",
            })
            .exec()
            .then(games => {
                games.forEach(game => {
                    // add a new bullet
                    game.bullets.push({
                        // get x and y from the list above
                        x: defaultBullets[Math.floor(Math.random() * defaultBullets.length)].x,
                        y: defaultBullets[Math.floor(Math.random() * defaultBullets.length)].y,
                    });
                    // add a new pellet
                    game.pellets.push({
                        // get x and y from the list above
                        x: defaultPellets[Math.floor(Math.random() * defaultPellets.length)].x,
                        y: defaultPellets[Math.floor(Math.random() * defaultPellets.length)].y,
                    });
                    // save the game
                    game
                        .save()
                        .then(result => {
                            // emit the game to all players in the same game instance
                            wss.clients.forEach(client => {
                                if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                    client.send(JSON.stringify({
                                        type: "gameUpdated",
                                        game: result,
                                    }));
                                }
                            });
                        })
                        .catch(err => {
                            console.log(err);
                        });
                });
            })
            .catch(err => {
                console.log(err);
            });
    }, 3000);

    ws.send('Hi there, I am a WebSocket server');
});

module.exports = wss;