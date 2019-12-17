import processing.serial.*;

Serial myPort;

int out1;
int out2;
int out3;
int val;
//int Val1 = 0;
//int Val2 = 0;
//int Val3 = 0;


float beginX = 20.0;  // Initial x-coordinate
float beginY = 10.0;  // Initial y-coordinate
float endX = 300.0;   // Final x-coordinate
float endY = 300.0;   // Final y-coordinate
float distX;          // X-axis distance to move
float distY;          // Y-axis distance to move
float exponent = 4;   // Determines the curve
float x = 0.0;        // Current x-coordinate
float y = 0.0;        // Current y-coordinate
float step = 0.015;    // Size of each step along the path
float pct = 0.0;      // Percentage traveled (0.0 to 1.0)

// timout code
boolean runit = true;
int time;
int wait = 1000;


void setup() {

  size(1300, 950, P3D);
  background(255);
  
  String instructions = "Click anywhere in the window to shower your Comptuer Companion with confetti";
  String response1 = "Your companion's LED belt will match the confetti";
  String response2 = "It will be so happy it will wave its arm and spin its head";
  
// instructions
  fill(0);
  textSize(12);
  text(instructions, 20, 300);
  text (response1, 20, 315);
  text (response2, 20, 330);
 
  translate(200, 0, 0);
  robot();

  
      
   //Find your port name or number
  int portchoice = 3;
  String portName = Serial.list()[portchoice];
  println(Serial.list());
  myPort = new Serial(this, portName, 115200);


}

void robot(){
//head
fill(78,57,74);
noStroke();
rect(250, 50, 500, 200);

//neck
fill(102,86,75);
rect(450,250,100,50);


//body
fill(24,7,7);
rect(350,300,300,450);


//lowerbody
fill(8,36,78);
rect(300,750,400,100);


//ourleftshoulder
fill(255,255,0);
rect(250,350,100,100);


//ourleftarm
fill(154,24,24);
rect(150,350,100,250);

//ourlefthand
fill(29,94,54);
rect(100,600,200,50);


//ourrightshoulder
fill(235,100,64);
rect(650,350,100,100);


//ourrightarm
fill(198,136,162);
rect(750,350,100,250);


//ourrighthand
fill(0);
rect(700,600,200,50);


//ourlefteye
fill(0);
ellipse(300,200,100,100);
fill(0,0,255);
ellipse(300,200,20,20);

//ourrighteye
fill(0);
ellipse(700,200,100,100);
fill(0,0,255);
ellipse(700,200,20,20);
}   

void draw() {

}

void mousePressed() {
  int out1 = mouseX;
  int out2 = mouseY;
  float out3 = random(255);
  strokeWeight(4);
  stroke(200);

  noStroke();
  lights();
  fill(out1, out2, out3);
  
  float mx = map(mouseX, 0, 255, 0, 255);
  float my = map(mouseY, 0, 255, 0, 255);
  ellipse(mx, my, 20, 20);
  println(mx);
  println(my);
 
  
  int mouseXval = int(mx);
  int mouseYval = int(my);
  int val3 = int(out3);
  
  println(mouseXval);
  println(mouseYval);
  println(val3);
  myPort.write(mouseXval);
  myPort.write(mouseYval);
  myPort.write(val3);
  
}

  

///////////////////////////////

void sendDataOut() {
  
  //REMEMBER THIS ONLY SENDS OUT BYTES at a time ( 0-255) only!!!!!
  // Also the chars r g b are just something to parse between the numbers
  // check the arduion code for how this is used when the serial data is coming in.

  //myPort.write(out1);
  //myPort.write(out2);
  //myPort.write(out3);
  ////myPort.write('1');

}
