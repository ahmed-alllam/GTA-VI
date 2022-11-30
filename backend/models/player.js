const mongoose = require("mongoose");

const PlayerSchema = mongoose.Schema({
  username: {
    type: String,
    required: true
  },
  password: {
    type: String,
    required: true
  },
});

const bcrypt = require('bcrypt');

PlayerSchema.methods.comparePassword = function(password) {
  return bcrypt.compareSync(password, this.password);
};

module.exports = mongoose.model("Players", PlayerSchema);