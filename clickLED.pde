
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

  size(255, 255, P3D);
  endX = width/2;
  endY = height/2;
  distX = endX - beginX;
  distY = endY - beginY;
  background(255);
  
  //size(200,200);
  
  // Find your port name or number
  int portchoice = 4;
  String portName = Serial.list()[portchoice];
  println(Serial.list());
 // myPort = new Serial(this, portName, 115200);


}   



void draw() {
  //mousePressed();
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
  
  ellipse(mouseX, mouseY, 10, 10);
 // println(((y/height)*120.0) - 40);

     //translate(0, 0, 0); 
     //fill(220);
     //text(out1, -80,-130);
     //text(out2, -30,-130);
     //text(out3, 20,-130);

  //rotateX(PI); // make the y axis point up 
  //translate(Xoffset, -Yoffset); // lower down the arm and move it to the middle so we can see it


//  sendDataOut();
  myPort.write(out1);
  myPort.write(out2);
  int val3 = int(out3);
  myPort.write(val3);
  println(out1);
  println(out2);
  println(val3);
}

///////////////////////////////
void sendDataOut() {
  //REMEMBER THIS ONLY SENDS OUT BYTES at a time ( 0-255) only!!!!!
  // Also the chars r g b are just something to parse between the numbers
  // check the arduion code for how this is used when the serial data is coming in.

  myPort.write(out1);
  myPort.write(out2);
  //myPort.write(out3);
  //myPort.write('1');
 
}
////////////////////////////////////////////////

//void nuMoveTo(int mX, int mY) {
 
//  if ((mX < 120) && (mY < 30)) {
//    // do nothing
//  } else {
//    pct = 0.0;
//    beginX = x;
//    beginY = y;
//    endX = mX;
//    endY = mY;
//    distX = endX - beginX;
//    distY = endY - beginY;
//  }
//}
