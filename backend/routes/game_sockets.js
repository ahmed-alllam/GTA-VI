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
    { x: 1, y: 1 },
    { x: 10, y: 14 },
    { x: 10, y: 1 },
    { x: 1, y: 14 },
    { x: 3, y: 6 },
    { x: 1, y: 6 },
];

// make an array of default of positions of pellets
let defaultPellets = [
    { x: 9, y: 1 },
    { x: 4, y: 14 },
    { x: 7, y: 13 },
    { x: 9, y: 9 },
    { x: 10, y: 4 },
    { x: 2, y: 3 },
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
                                        bullet: 0,
                                        health: 3,
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
            // when player makes a move
            case "move":
                // find the game
                Game
                    .findOneAndUpdate({
                        id: data

                            .game.gameId
                    }, {
                        $set: {
                            "players.$[player].x": data.player.x,
                            "players.$[player].y": data.player.y,
                            "players.$[player].direction": data.player.direction,
                        }
                    }, {
                        arrayFilters: [{
                            "player.id": data.playerId
                        }],
                        new: true
                    })
                    .exec()
                    .then(game => {
                        // emit the game to all players in the game
                        wss.clients.forEach(client => {
                            if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                client.send(JSON.stringify({
                                    type: "gameUpdated",
                                    game: game
                                }));
                            }
                        });
                    })
                    .catch(err => {
                        console.log(err);
                    });
                break;
            case "removeBullet":
                Game
                    .findOneAndUpdate({
                        id: data

                            .game.gameId
                    }, {
                        // remove 
                        $pull: {
                            "bullets": { x: data.bullet.x, y: data.bullet.y }
                        }
                    }, {
                        new: true
                    })
                    .exec()
                    .then(game => {
                        // emit the game to all players in the game
                        wss.clients.forEach(client => {
                            if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                client.send(JSON.stringify({
                                    type: "gameUpdated",
                                    game: game
                                }));
                            }
                        });
                    })
                    .catch(err => {
                        console.log(err);
                    });



                break;
            // same but for pellets
            case "removePellet":
                Game
                    .findOneAndUpdate({
                        id: data
                            .game.gameId
                    }, {
                        $pull: {
                            "pellets": { x: data.pellet.x, y: data.pellet.y }
                        }
                    }, {
                        new: true
                    })
                    .exec()
                    .then(game => {
                        // emit the game to all players in the game
                        wss.clients.forEach(client => {
                            if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                client.send(JSON.stringify({
                                    type: "gameUpdated",
                                    game: game
                                }));
                            }
                        });
                    })
                    .catch(err => {
                        console.log(err);
                    });


                break;
            // updateBullets
            case "updateBullets":
                // update the bullets that player has
                Game
                    .findOneAndUpdate({
                        id: data
                            .game.gameId
                    }, {
                        $set: {
                            "players.$[player].bullets": data.player.bullets
                        }
                    }, {
                        arrayFilters: [{
                            "player.id": data.playerId
                        }],
                        new: true
                    })
                    .exec()
                    .then(game => {
                        // emit the game to all players in the game
                        wss.clients.forEach(client => {
                            if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                client.send(JSON.stringify({
                                    type: "gameUpdated",
                                    game: game
                                }));
                            }
                        });
                    })
                    .catch(err => {
                        console.log(err);
                    });

                break;
            // updateScore
            case "updateScore":
                // update the score of the player
                Game
                    .findOneAndUpdate({
                        id: data
                            .game.gameId
                    }, {
                        $set: {
                            "players.$[player].score": data.player.score
                        }
                    }, {
                        arrayFilters: [{
                            "player.id": data.playerId
                        }],
                        new: true
                    })
                    .exec()
                    .then(game => {
                        // emit the game to all players in the game
                        wss.clients.forEach(client => {
                            if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                client.send(JSON.stringify({
                                    type: "gameUpdated",
                                    game: game
                                }));
                            }
                        });
                    })
                    .catch(err => {
                        console.log(err);
                    });

                break;

            case "shoot":
                Game
                    .findOneAndUpdate({
                        id: data
                            .game.gameId
                    }, {
                        $inc: {
                            "players.$[player].bullets": -1
                        },
                    }, {
                        arrayFilters: [{
                            "player.id": data.playerId
                        }],
                        new: true
                    })
                    .exec()
                    .then(game => {
                        // emit the game to all players in the game
                        wss.clients.forEach(client => {
                            if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                                if (client.playerId !== ws.playerId) {
                                    client.send(JSON.stringify({
                                        type: "shoot",
                                        x: data.x,
                                        y: data.y,
                                        direction: data.direction,
                                    }));
                                }
                            }
                        });
                    })
                    .catch(err => {
                        console.log(err);
                    });
                break;

            case "playerHit":
                Game
                    .findOneAndUpdate({
                        id: data
                            .game.gameId
                    }, {
                        $set: {
                            // "state": "players.$[player].health === 1 && players.length === 2 ? 'finished' : state",
                            $cond: {
                                if: {
                                    $and: [{
                                        $eq: ["$players.$[player].health", 1]
                                    }, {
                                        $eq: [{
                                            $size: "$players"
                                        }, 2]
                                    }]
                                },
                                then: "finished",
                                else: "$state"
                            }
                        },
                        $inc: {
                            "players.$[player].health": -1
                        },
                        $pull: {
                            $cond: {
                                if: {
                                    $eq: ["$players.$[player].health", 0]
                                },
                                then: {
                                    "players": {
                                        id: data.playerId
                                    },
                                    "players_ids": ws.playerId
                                },
                                else: {}
                            }
                        },
                    }, {
                        arrayFilters: [{
                            "player.id": data.playerId
                        }],
                        new: false
                    })
                    .exec()
                    .then(result => {
                        // emit the game to all players in the game
                        // if the player with the id health is 0, then the player is dead
                        for (let i = 0; i < result.players.length; i++) {
                            if (result.players[i].id === data.playerId) {
                                if (result.players[i].health === 1) {
                                    if (result.players.length === 2) {
                                        wss.clients.forEach(client => {
                                            if (client.readyState === WebSocket.OPEN && result.players_ids.includes(client.playerId)) {
                                                if (ws.playerId != client.playerId) {
                                                    client.send(JSON.stringify({
                                                        type: "gameWon",
                                                        game: result,
                                                    }));
                                                }
                                            }
                                        });
                                    } else {
                                        wss.clients.forEach(client => {
                                            if (client.readyState === WebSocket.OPEN && result.players_ids.includes(client.playerId)) {
                                                client.send(JSON.stringify({
                                                    type: "playerDied",
                                                    player: data.playerId,
                                                }));
                                            }
                                        });
                                    }
                                } else {
                                    wss.clients.forEach(client => {
                                        if (client.readyState === WebSocket.OPEN && result.players_ids.includes(client.playerId)) {
                                            client.send(JSON.stringify({
                                                type: "gameUpdate",
                                                game: result,
                                            }));
                                        }
                                    });
                                }
                            }
                        }
                    })
                    .catch(err => {
                        console.log(err);
                    });

                break;
            default:
                break;
        }
    });

    ws.on("close", () => {
        console.log("Client disconnected");

        Game
            .findOneAndUpdate({
                players_ids: ws.playerId
            }, {
                $pull: {
                    players_ids: ws.playerId
                }
            }, {
                new: true
            })
            .exec()
            .then(game => {
                if (game.players_ids.length === 0) {
                    // delete the game
                    game
                        .remove()
                        .then(result => {
                            console.log("Game deleted");
                        })
                        .catch(err => {
                            console.log(err);
                        });
                } else {
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
                }
            }
            )
            .catch(err => {
                console.log(err);
            }
            );
    });

    // every 3000ms, add a new random bullet and pellet to the game and emit the game to all players in the game
    setInterval(() => {
        Game
            .updateMany({
                state: "playing",
            }, {
                $push: {
                    $cond: {
                        if: {
                            $lt: [{
                                $size: "$bullets"
                            }, 4]
                        },
                        then: {
                            bullets: defaultBullets[Math.floor(Math.random() * defaultBullets.length)]
                        },
                        else: {}
                    },
                    $cond: {
                        if: {
                            $lt: [{
                                $size: "$pellets"
                            }, 3]
                        },
                        then: {
                            pellets: defaultPellets[Math.floor(Math.random() * defaultPellets.length)]
                        },
                        else: {}
                    }
                }
            }, {
                new: true,
            })
            .exec()
            .then(result => {
                console.log(JSON.stringify(result));
                console.log(result);
                // result.forEach(game => {
                //     wss.clients.forEach(client => {
                //         if (client.readyState === WebSocket.OPEN && game.players_ids.includes(client.playerId)) {
                //             client.send(JSON.stringify({
                //                 type: "gameUpdated",
                //                 game: game,
                //             }));
                //         }
                //     });
                // });
            })
            .catch(err => {
                console.log(err);
            }
            );

    }, 3000);

    ws.send('Hi there, I am a WebSocket server');
});

module.exports = wss;