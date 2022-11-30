const express = require('express');
const router = express.Router();
const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');

const Player = require('../models/player');

router.post('/signup', (req, res, next) => {
    // check that the username is not already taken
    Player
        .find
        ({
            username: req.body.username
        })
        .exec()
        .then(player => {
            if (player.length >= 1) {
                return res.status(409).json({
                    message: 'Username already exists'
                });
            } else {
                // hash the password
                bcrypt.hash(req.body.password, 10, (err, hash) => {
                    if (err) {
                        return res.status(500).json({
                            error: err
                        });
                    } else {
                        // create a new player
                        const player = new Player({
                            username: req.body.username,
                            password: hash
                        });
                        // save the player
                        player
                            .save()
                            .then(result => {
                                console.log(result);
                                res.status(201).json({
                                    message: 'Player created'
                                });
                            })
                            .catch(err => {
                                console.log(err);
                                res.status(500).json({
                                    error: err
                                });
                            });
                    }
                });
            }
        });
});

router.post('/signin', (req, res, next) => {
    let fetchedPlayer;
    Player.findOne
        ({
            username
                : req.body.username
        })
        .then(player => {
            if (!player) {
                return res.status(401).json({
                    message: 'Auth failed'
                });
            }
            fetchedPlayer = player;
            return bcrypt.compare(req.body.password, player.password);
        }
        )
        .then(result => {
            if (!result) {
                return res.status(401).json({
                    message: 'Auth failed'
                });
            }
            const token = jwt.sign(
                {
                    username: fetchedPlayer.username, userId: fetchedPlayer
                        ._id
                },
                'supersecretpassword',
                {
                    expiresIn
                        : '1h'
                }
            );
            res.status(200).json({
                token: token,
                expiresIn: 3600,
                userId: fetchedPlayer._id
            });
        })
        .catch(err => {
            return res.status(400).json({
                message: 'Invalid authentication credentials!'
            });
        }
        );
});

module.exports = router;