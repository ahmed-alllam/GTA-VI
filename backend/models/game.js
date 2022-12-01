const mongoose = require("mongoose");

const GameSchema = mongoose.Schema({
    id: {
        type: String,
        required: true,
    },
    // make list of players usernames
    players: {
        type: Array,
    },
    state: {
        type: String,
        // required: true,
    },
});

module.exports = mongoose.model("Games", GameSchema);