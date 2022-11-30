const mongoose = require("mongoose");

const GameSchema = mongoose.Schema({
    id: {
        type: String,
        required: true,
    },
    players: [
        {
            type: mongoose.Schema.Types.ObjectId,
            ref: "Player",
        },
    ],
    state: {
        type: String,
        // required: true,
    },
});

module.exports = mongoose.model("Games", GameSchema);