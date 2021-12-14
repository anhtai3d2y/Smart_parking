var express = require('express');
var app = express();
app.use(express.static("public"));
app.set('view engine', "ejs");
app.set('views', "./views");
var server = require("http").Server(app);
var io = require('socket.io')(server);
server.listen(process.env.PORT || 3030);
console.log('Server is running!');

io.on("connection", function(socket) {

    console.log("Co nguoi ket noi: " + socket.id);

    socket.on("disconnect", function() {
        console.log(socket.id + " da ngat ket noi");
    });

    socket.on("Client-send-data", function(data) {
        console.log(data);
        // io.sockets.emit("Server-send-data", data + "888");
        // socket.emit("Server-send-data", data + "888");
        socket.broadcast.emit("Server-send-data", data + "888");
    });
});

app.get('/', function(req, res) {
    res.render("homepage");
});

// io.on("connection", function(socket) {
//     console.log(socket.id);
//     //Listen
//     socket.on('license_plate', function(data) {
//         console.log(data);
//     })
// })