const express = require("express");
const mongoose = require("mongoose");
const socketIO = require('socket.io');
const app = express();
const bcrypt = require('bcrypt');

// Body Parser
app.use(express.json({limit: '50mb'}));
app.use(express.urlencoded({ extended: true , limit: '50mb'}));

const jsonwebtoken = require("jsonwebtoken");

app.use(function (req, res, next) {
  if (req.headers && req.headers.authorization && req.headers.authorization.split(' ')[0] === 'JWT') {
    jsonwebtoken.verify(req.headers.authorization.split(' ')[1], 'supersecretpassword', function (err, decode) {
      if (err) req.user = undefined;
      req.user = decode;
      next();
    });
  } else {
    req.user = undefined;
    next();
  }
});

// API Routes
const authRoutes = require("./routes/auth");
app.use('/', authRoutes);

const gameRoutes = require("./routes/game");
app.use('/', gameRoutes);

app.get("/", (req, res) => {
  res.send("Ok");
});


//  DB Connection
mongoose.connect(
  process.env.DB_CONNECTION,
  { useNewUrlParser: true, useUnifiedTopology: true },
  () => {
    console.log("Database connection successful");
  }
);

app.enable('trust proxy')
app.use((req, res, next) => {
    req.secure ? next() : res.redirect('https://' + req.headers.host + req.url)
})

// Listen

const wss = require('./routes/game_sockets');
const server = app.listen(process.env.PORT);
server.on('upgrade', (req, socket, head) => {
  wss.handleUpgrade(req, socket, head, (ws) => {
    wss.emit('connection', ws, req);
  });
});