// Module
var express = require('express');
var app = express();

// Define port
var port = 3000;

// View engine
app.set('view engine', 'jade');

// Set public folder
app.use(express.static(__dirname + '/public'));

// Serve interface
app.get('/', function(req, res){
  res.render('interface');
});

// Rest
var arest = require("arest")(app);

arest.addDevice('http','192.168.1.6');
//arest.addDevice('serial','/dev/cu.usbmodem1d11', 115200);

// Start server
app.listen(port);
console.log("Listening on port " + port);