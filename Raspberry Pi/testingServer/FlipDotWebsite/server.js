var express = require('express');
var bodyParser = require('body-parser');

var app = express();
var path = require("path");
var urlencodedParser = bodyParser.urlencoded({
    extended: false
});

app.set('view engine', 'ejs');

app.use(express.static(path.join(__dirname, 'public'), {
    extensions: ['html', 'htm']
}));

app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname + '/index.html'));
});

app.get('/index', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});

app.get('/demo', function(req, res) {
    res.sendFile(__dirname + '/demo.html');
});

app.get('/about', function(req, res) {
    res.sendFile(__dirname + '/about.html');
});

function sendtoarduino(data){

  var serialport = require("serialport");
  var SerialPort = serialport.SerialPort;
  const Readline = serialport.parsers.Readline;
  const port = new serialport("/dev/ttyUSB0");
  const parser = new Readline();
  port.pipe(parser);
  //parser.on('readable', port.);
  var t = data.split(/\r?\n/);
  for(i in t){
    console.log("sending");
    console.log(t[i]);
    for(var j = 0; j < t[i].length; j++){
      port.write(new Buffer(t[i][j], 'ascii'));
    }
    
   // port.write(t[i]);
    port.write(new Buffer("\n", 'ascii'));
  }

//console.log("py");
//
//console.log(data.split(/\r?\n/));
//console.log("end");
//parser.on('open', function(){
 // console.log('Serial Port Opend');
  
 // /serialport.on('data', function(data){
//     console.log(data[0]);
  //});
//});
}

app.post('/demo', urlencodedParser, function(req, res) {
    var button = {
        data: req.body
    };
    var imageName = button.data.image; 
    console.log("User selects: " + imageName);
    var cmd = require('node-cmd');
const fs = require('fs');
 	if(fs.existsSync("lock")){
		console.log("lock exists");	
		return;	
	}
    if(imageName === "Christmas_Tree")
    {
	var argStr = ""
	for(var i = 0; i <2; i++)
	{
	   for(var j = 0; j < 3; j++)
	   {	
//console.log("running " + j );
	argStr += imageName + j + ".png ";
	   }	   
	}
	var d = '';
	//console.log(argStr);
	var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + argStr);
        	pyProcess.stdout.on('data',
function(data){
console.log(data);
d = data;
//sendtoarduino(d);
});	
pyProcess.stdout.on('error',
function(data){
console.log(data);
d = data;
//sendtoarduino(d);
});	

    }

    if(imageName === "Computer")
    {	
	   for(var j = 0; j < 1; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	
    }

    if(imageName === "CSE")
    {
	
	   for(var j = 0; j < 1; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
    }

    if(imageName === "Hello")
    {
	   for(var j = 0; j < 1; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
    }

    if(imageName === "Merry")
    {
	for(var i = 0; i <3; i++)
	{
	   for(var j = 0; j < 3; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
	}
    }

    if(imageName === "Tree")
    { console.log("i am in Tree");
	   for(var j = 0; j < 1; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
		console.log(imageName + j + ".png");
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
    }

    if(imageName === "UTA")
    {
	   for(var j = 0; j < 1; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
    }

    if(imageName === "Snow_Man")
    {
	   for(var j = 0; j < 1; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
    }

    if(imageName === "Reindeer")
    {
	for(var i = 0; i <2; i++)
	{
	   for(var j = 0; j < 5; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
	}
    }

    if(imageName === "Square")
    {
	for(var i = 0; i <2; i++)
	{
	   for(var j = 0; j < 6; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
	}
    }

    if(imageName === "Senior_Design")
    {
	for(var i = 0; i <2; i++)
	{
	   for(var j = 0; j < 4; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
	}
    }

    if(imageName === "Present")
    {
	for(var i = 0; i <2; i++)
	{
	   for(var j = 0; j < 5; j++)
	   {
	      var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName + j+ ".png",
        	function(data, err, stderr) {
          
            	if (err.includes("error")) 
		{
                   res.sendFile(__dirname + '/error.html');
           	} 
		else 
		{
                   console.log(err);
                   res.sendFile(__dirname + '/timer.html');
            	}
              });	
	   }	   
	}
    }



		
		
    //var pyProcess = cmd.get('python3 /home/pi/Desktop/testingServer/FlipDotWebsite/FlipDotStringGenerator.py ' + imageName,
        //function(data, err, stderr) {
          
            //if (err.includes("error")) {
                
                //this was the original
                //res.sendFile(__dirname + '/error.html');

                //IF statement always result in error, I don't know why 
                //res.sendFile(__dirname + '/timer.html');

           //} else {
                //console.log(err);
                //res.sendFile(__dirname + '/timer.html');
           // }
        //});

    // const pythonProcess = spawn('python',["", imageName]);

    //res.sendFile(__dirname + '/demo.html');
});

//app.listen(80);
app.listen(80);
console.log("Now listening to port: 80");
