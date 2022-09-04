var fs = require('fs'),
    http = require('http');

var server = http.createServer(function (req, res) {
  fs.readFile(__dirname + "/website.html", function (err,data) {
    if (err) {
      res.writeHead(404);
      res.end(JSON.stringify(err));
      return;
    }
    res.writeHead(200);
    res.end(data);
  });
}).listen(8080);