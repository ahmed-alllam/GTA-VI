const mongoose = require("mongoose");

const GameSchema = mongoose.Schema({
    id: {
        type: String,
        required: true,
    },
    // make list of players that contains dictionaries of player id and score, and x and y coordinates and direction
    players: {
        type: Array,
    },
    state: {
        type: String,
        // required: true,
    },
});

module.exports = mongoose.model("Games", GameSchema);