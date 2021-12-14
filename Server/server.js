var fs = require('fs');
var url = require('url');
var http = require('http');
var WebSocket = require('ws');
// function gửi yêu cầu(response) từ phía server hoặc nhận yêu cầu (request) của client gửi lên
function requestHandler(request, response) {
    fs.readFile('./index.html', function(error, content) {
        response.writeHead(200, {
            'Content-Type': 'text/html'
        });
        response.end(content);
    });
}
// create http server
var server = http.createServer(requestHandler);
var ws = new WebSocket.Server({
    server
});


var clients = [];
var message_btn = "";

function broadcast(socket, data) {
    console.log(clients.length);
    for (var i = 0; i < clients.length; i++) {
        if (clients[i] != socket) {
            clients[i].send(data);
        }
    }
}

var UIDReceived = '';

ws.on('connection', function(socket, req) {
    clients.push(socket);
    console.log("connected!");
    socket.on('message', function(message) {
        UIDReceived = message;
        console.log('received: %s', message);
        broadcast(socket, message);
        message_btn = message;
    });
    socket.on('close', function() {
        var index = clients.indexOf(socket);
        clients.splice(index, 1);
        console.log('disconnected');
    });
    //receive license plate
    socket.on('license_plate', function(message) {
        console.log("received from php: " + message);
    });
});


server.listen(3000, function() {
    console.log('listening on: 3000');
});