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
    { x: 1, y: 1, direction: -1 },
    { x: 10, y: 14, direction: 1 },
    { x: 10, y: 1, direction: 1 },
    { x: 1, y: 14, direction: 1 },
];


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
                                // check the player is not already in the game
                                if (game.players.indexOf(data.playerId) === -1) {
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

                                        // save the game
                                        game
                                            .save()
                                            .then(result => {
                                                // emit the game to the requesting player
                                                if (game.state === "playing") {
                                                    wss.clients.forEach(client => {
                                                        if (client.readyState === WebSocket.OPEN) {
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
                                        game.players[i].x = data.player.x;
                                        game.players[i].y = data.player.y;
                                        game.players[i].direction = data.player.direction;

                                        game.save()
                                            .then(result => {
                                                wss.clients.forEach(client => {
                                                    if (client.readyState === WebSocket.OPEN) {
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

    ws.send('Hi there, I am a WebSocket server');
});

module.exports = wss;