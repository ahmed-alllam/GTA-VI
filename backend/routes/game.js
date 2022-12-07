const express = require("express");
const router = express.Router();
const mongoose = require("mongoose");
const Game = require("../models/game");
const Player = require("../models/player");

const app = express();


// make an array of default of positions of bullets
let defaultBullets = [
    { x: 1, y: 1},
    { x: 10, y: 14},
    { x: 10, y: 1},
    { x: 1, y: 14},
];

// make an array of default of positions of pellets
let defaultPellets = [
    { x: 9, y: 1},
    { x: 4, y: 14},
];

router.post("/create", (req, res, next) => {
    // check player is logged in
    if (req.user) {
        // create a new game
        const game = new Game({
            state: "waiting",
            // generate a random id of 4 characters
            id: Math.random().toString(36).substring(2, 6),
            // make list of bullets that contains dictionaries of x and y coordinates
            bullets: defaultBullets,
            // make list of pellets that contains dictionaries of x and y coordinates
            pellets: defaultPellets,
        });
        // save the game
        game
            .save()
            .then(result => {
                res.status(201).json({
                    message: "Game created",
                    game: result,
                });
            })
            .catch(err => {
                res.status(500).json({
                    error: err,
                });
            }
            );
    } else {
        res.status(401).json({
            message: "Unauthorized",
        });
    }
});

// router to get the game
router.get("/:gameId", (req, res, next) => {
    // check game exists
    Game
        .findById(req.params.gameId)
        .exec()
        .then(game => {
            if (game) {
                res.status(200).json({
                    game: game,
                });
            } else {
                res.status(404).json({
                    message: "Game not found",
                });
            }
        }
        );
});

// begin the socket.io code
// io.on("connection", socket => {
//     // when a player joins a game
//     socket.on("joinGame", data => {
//         // find the game
//         Game
//             .findById(data
//                 .gameId)
//             .exec()
//             .then(game => {
//                 // check the game exists
//                 if (game) {
//                     // check the game is waiting
//                     if (game.state === "waiting") {
//                         // check the player is not already in the game
//                         if (game.players.indexOf(data.playerId) === -1) {
//                             // check game is not full
//                             if (game.players.length < 4) {
//                                 // add the player to the game
//                                 game.players.push(data.playerId);
//                                 game.state = "in progress";
//                                 // save the game
//                                 game
//                                     .save()
//                                     .then(result => {
//                                         // emit the game to all players
//                                         socket.to(data.gameId).emit("game", {
//                                             game: result,
//                                         });
                                        
//                                         // assign random x and y coordinates to each player and emit to all players in the game
//                                         for (let i = 0; i < result.players.length; i++) {
//                                             // todo: make sure the coordinates are not already taken and in range of the board
//                                             let x = Math.floor(Math.random() * 10);
//                                             let y = Math.floor(Math.random() * 10);
//                                             socket.to(data.gameId).emit("updateMove", {
//                                                 playerId: result.players[i],
//                                                 x: x,
//                                                 y: y,
//                                             });
//                                         }
//                                     })
//                                     .catch(err => {
//                                         console.log(err);
//                                     });
//                             } else {
//                                 // emit error message
//                                 socket.emit("error", {
//                                     message: "Game is full",
//                                 });
//                             }

//                         } else {
//                             // emit error message
//                             socket.emit("error", {
//                                 message: "Player is already in game",
//                             });
//                         }
//                     }
//                 } else {
//                     // emit error message
//                     socket.emit("error", {
//                         message: "Game not found",
//                     });
//                 }
//             })
//             .catch(err => {
//                 console.log(err);
//                 socket.emit("error", {
//                     message: "Game not found",
//                 });
//             });
//     });

//     // when a player leaves a game
//     socket.on("leaveGame", data => {
//         // find the game
//         Game
//             .findById
//             (data.gameId)
//             .exec()
//             .then(game => {
//                 // check the game exists
//                 if (game) {
//                     // check the game is waiting
//                     if (game.state === "waiting") {
//                         // check the player is in the game
//                         if (game.players.indexOf(data.playerId) !== -1) {
//                             // remove the player from the game
//                             game.players.splice(game.players.indexOf(data.playerId), 1);
//                             // save the game
//                             game
//                                 .save()
//                                 .then(result => {
//                                     // emit the game to all players in the game
//                                     socket.to(data.gameId).emit("game", {
//                                         game: result,
//                                     });
//                                 })
//                                 .catch(err => {
//                                     console.log(err);
//                                 });
//                         } else {
//                             // emit error message
//                             socket.emit("error", {
//                                 message: "Player is not in game",
//                             });
//                         }
//                     }
//                 }
//             }
//             );
//     });

//     // when a new move, or update, is made
//     socket.on("updateGame", data => {
//         // take the game id from the data
//         const gameId = data.gameId;
//         // broadcast the game to all players inside the game
//         socket.broadcast.to(gameId).emit("game", {
//             game: data.game,
//         });

//         // save the game
//         Game
//             .findByIdAndUpdate
//             (gameId, data.game)
//             .exec()
//             .then(result => {

//             });
//     });

//     // updating a move by sending x and y coordinates and the player id to the server
//     socket.on("updateMove", data => {
//         const gameId = data.gameId;
//         const playerId = data.playerId;
//         const x = data.x;
//         const y = data.y;

//         socket.broadcast.to(gameId).emit("move", {
//             playerId: playerId,
//             x: x,
//             y: y,
//         });
//     });

//     // when a player disconnects
//     socket.on("disconnect", () => {
//         console.log("User disconnected");
//     });
// });

module.exports = router;