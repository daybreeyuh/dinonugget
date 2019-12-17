////////////LED STRIP/////////
#include <Adafruit_NeoPixel.h>
#define LED_PIN    6
#define LED_COUNT 30

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

int proVal1;
int proVal2;
int proVal3;
int ColorVal[3] = {proVal1, proVal2, proVal3};

///////////SERVO////////
#include <Servo.h>

/////Servo one/////
Servo myservo;  // create servo object to control a servo
int Home = 90;
int Position1;
int Direction = HIGH;
int pos = 0;    // variable to store the servo position
int Speed = 10;

/////SERVO 2/////
Servo ARM;
int arm = 45;

int pos2 = 0;
  int Swing1 = 135;
  int Swing2 = 45;
  int Fluffy;


void setup() {
  //////////LED STRIP/////////
  Serial.begin(115200);
  strip.begin();

  /////////SERVO/////////
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  ARM.attach(2);
  myservo.write(Home);
  ARM.write(pos2);
  Position1 = Home;
}

void loop() {

  if (Serial.available()){  //READ SERIAL MONITOR AND STORE DATA FOR SERVO AND LED STRIP PROCESSING
    ColorVal[0] = Serial.read();
    ColorVal[1] = Serial.read();
    ColorVal[2] = Serial.read();
//  }

  //////ACTIVATE LED STRIP BASED ON STORED VALUES/////
  if (ColorVal[0] > 5) {
    chase(strip.Color(ColorVal[0], ColorVal[1], ColorVal[2]));
  }
  else {
  }

  /////TURN ROBOT HEAD IN CERTAIN DIRECTION.
  if(ColorVal[0] < 125){
    Direction = HIGH;
  }
  else
    Direction = LOW;
  
  switch (Direction) {
  case HIGH:
    Rotate_Head_CW(Home);
    chase(strip.Color(ColorVal[0], ColorVal[1], ColorVal[2]));
//    myservo.write(Home);
    //Sweep_ArmCW(arm);
    //Serial.println(Direction);
//    if(Fluffy != Swing1){
//    ARM.write(Swing1); 
//    Fluffy = Swing1;
//    }
//    else{
//    }
    break;
  case LOW:
    Rotate_Head_CCW(arm);
    chase(strip.Color(ColorVal[0], ColorVal[1], ColorVal[2]));
    //Sweep_ArmCCW(arm);
    //Serial.println(Direction);
//    if(Fluffy != Swing2){
//    ARM.write(Swing2);
//    Fluffy = Swing2;
//    }
//    else{
//    }
    break;
  default:
    break;
}
//  ARM.write(135);
//  ARM.write(45);

// Serial.println(ColorVal[0]);
  }
}

/////////LED STRIP FUNCTIONS/////////
static void chase(int c){
  for(int i = 0; i < strip.numPixels()+4; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(i-4, 0);
    strip.show();
    delay(25);
  }
}

////////SERVO FUNCTIONS//////////

void Rotate_Head_CW(int Home){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }                    // waits 15ms for the servo to reach the position
  }


void Rotate_Head_CCW(int Home){
    for (pos = 90; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    ARM.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    for (pos = 180; pos >= 90; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    ARM.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

}

void Sweep_ArmCW(int arm){
    for (pos2 = arm; pos2 <= 135; pos2 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    //Serial.println(pos2);
    ARM.write(pos2);       // tell servo to go to position in variable 'pos'
    delay(Speed);                       // waits 15ms for the servo to reach the position
  }
}

void Sweep_ArmCCW(int arm){
    for (pos2 = arm; pos2 >= 0; pos2 -= 1) { // goes from 180 degrees to 0 degrees
    ARM.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(Speed);                       // waits 15ms for the servo to reach the position
  }
}


void Sweep_Arm(int arm){
ARM.write(arm);
//  for(pos2 = 135;pos2 >= 45;pos2 -= 1){
//    ARM.write(pos2);
//    delay(Speed);
//  }
//  for(pos2 = 45;pos2 >= 135;pos2 += 1){
//    ARM.write(pos2);
//    delay(Speed);
//}
}
