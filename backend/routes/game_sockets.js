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

// when a new connection is made
wss.on("connection", ws => {
    // when a message is received
    ws.on("message", message => {
        // parse the message
        const data = JSON.parse(message);
        // check the type of message
        switch (data.type) {
            // when a player joins a game
            case "joinGame":
                // find the game
                Game
                    .findById(data.game
                        .gameId)
                    .exec()
                    .then(game => {
                        // check the game exists
                        if (game) {
                            // check the game is waiting
                            if (game.state === "waiting") {
                                // check the player is not already in the game
                                if (game.players.indexOf(data.playerId) === -1) {
                                    // check game is not full
                                    if (game.players.length < 4) {
                                        // add the player to the game
                                        game.players.push(data.playerId);
                                        game.state = "in progress";
                                        // save the game
                                        game

                                            .save()
                                            .then(result => {
                                                // emit the game to all players
                                                wss.clients.forEach(client => {
                                                    if (client.readyState === WebSocket.OPEN) {
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
                                            message: "Game is full",
                                        }));
                                    }
                                } else {
                                    // emit error message
                                    ws.send(JSON.stringify({
                                        type: "error",
                                        message: "Player is already in game",
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
            // when a player leaves a game
            case "leaveGame":
                // find the game
                Game
                    .findById(data.game
                        .gameId)
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
                                                if (client.readyState === WebSocket.OPEN) {
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
                    
                    .findById(data.game
                        .gameId)
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
                                                if (client.readyState === WebSocket.OPEN) {
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
            // when a player starts a game
            case "startGame":
                // find the game
                Game
                    
                    .findById(data.game
                        .gameId)
                    .exec()
                    .then(game => {
                        // check the game exists
                        if (game) {

                            // check the game is waiting
                            if (game.state === "waiting") {
                                // check the player is in the game
                                if (game.players.indexOf(data.playerId) !== -1) {
                                    // check the game has enough players
                                    if (game.players.length >= 2) {
                                        // update the game
                                        game.state = "started";
                                        // save the game
                                        game
                                            .save()
                                            .then(result => {
                                                // emit the game to all players in the same game instance
                                                wss.clients.forEach(client => {
                                                    if (client.readyState === WebSocket.OPEN) {
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
                                            message: "Game does not have enough players",
                                        }));
                                    }
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
            default:
                break;
        }
    });

    ws.send('Hi there, I am a WebSocket server');
});

module.exports = wss;