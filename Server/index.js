var express = require('express');
var database = require('./database');
var app = express();

app.get('/listUser', function(req, res) {
    database.getAllUser(function(resultQuery) {
        res.json(resultQuery);
    });
});

app.get('/findUser', function(req, res) {
    var license_plate = req.query.license_plate;

    database.getByLicensePlate(license_plate, function(resultQuery) {
        res.json(resultQuery);
    });
});

app.get('/insert', function(req, res) {
    var username = req.query.username;
    var license_plate = req.query.license_plate;
    var email = req.query.email;
    var phone_number = req.query.phone_number;

    database.insertData(username, license_plate, email, phone_number, function(resultQuery) {
        res.json(resultQuery);
    });
});


app.listen(3000, function() {
    console.log('listening on: 3000');
});