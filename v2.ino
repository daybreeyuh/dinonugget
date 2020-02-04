

// SD NOTES
// This version has both buttons enabled and also I put in the first led.
// NOTE: you will need to add your own analogWrite command to control the second led
// To figure out how to use this, check out the fading sketch.

// Michael_Jackson_-_Beat_It.mid file converted.
// The notes and melodies are contained in the notes.h file,  tracks.h files
// attached as tabs

// To reduce the number of tracks and free up some memory I removed all but 4 of the orginal melody arrays.
// this version only has Melody3, Melody4, Melody5, Melody6 tracks (arrays)
// This means that you can choose with this code 2 of those 4 tracks to play.
// When modifying this make sure you replace arrays with the same names and check
// That there is a MelodyX_length var for each Array
// i.e. static const uint16_t Melody1_Length    = sizeof( Melody1 ) / sizeof(uint16_t);


#include "notes.h"
#include "tracks.h"
#include <avr/pgmspace.h>

// constants won't change. They're used here to set pin numbers:
const int button2Pin = 4;     // momentary btn
const int button1Pin = 5;     // toggle btn

const int led2Pin =  10;     // this is for led analog out or second speaker
const int led1Pin =  12;      // this is for led digital out

const int speakPin = 11;    // pin for speaker
const int speakPin2 = 9;    // optional second pin for second speaker

const int analogInPin0 = A0;  // Analog input pin for the pot
const int analogInPin1 = A1;  // Analog input pin  for the photocell

int sensorValue0 = 0;        // value read from the pot
int outputValue0 = 0;        // value output after map

int sensorValue1 = 0;        // value read from the photo cell
int outputValue1 = 0;        // valuer output from map

int button1State = 0;         // variable for reading toggle btn
int button2State = 0;         // variable for reading the momentary btn


uint8_t tempoToPlay  = 6;
uint16_t MelodyACount = 0;
uint16_t MelodyBCount = 0;

boolean Pong = false;


void setup()  {
  Serial.begin(9600);
  pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

}



void loop() {
  // resets the speaker if it was switched in the middle of note.
  noTone(speakPin);
  noTone(speakPin2);
  

  // read the btn pins
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  //Serial.println(button1State);

  // read the pot and read the photocell
  sensorValue0 = analogRead(analogInPin0);
  // photocell
  //sensorValue1 = analogRead(analogInPin1);

  // map it to tempo for the melody player ( 0/ fast  - 15 /slow
  outputValue0 = map(sensorValue0, 0, 1023, 0, 15);

  //take this form the analogWrite to show the led fade
  // you might want to reverse the values so the led fades works relative to tempo
  outputValue1 = map(sensorValue0, 0, 1023, 0, 255);

  Serial.print("Tempo ");
  Serial.println(outputValue0);

  // toggle
  if ( button1State == HIGH) {
    //Serial.println("ON");

    if (button2State == HIGH) {
      //music A
     play_Next_Melody_Data(Melody5, Melody5_Length, outputValue0,MelodyACount);
     // a ping pong version for 2 speakers
     //play_PingPongSpNext_Melody_Data(Melody4, Melody4_Length, outputValue0,MelodyACount);
      
      Serial.print("A  ");
      Serial.println(MelodyACount);
    } else {
      // music B
    
      play_Next_Melody_Data(Melody3, Melody3_Length, outputValue0,MelodyBCount); 
     // a ping pong version for 2 speakers
     // play_PingPongSpNext_Melody_Data(Melody3, Melody3_Length, outputValue0,MelodyBCount);
      Serial.print("B  ");
      Serial.println(MelodyBCount);
    }
    // blink the led on or off after each
   // digitalWrite(led1Pin, !digitalRead(led1Pin));
    digitalWrite(led1Pin, !digitalRead(led1Pin));
    // fade the led to control its brightness
    analogWrite(led2Pin, outputValue1);

    
   }

}


void play_Next_Melody_Data(const uint16_t MelodyData[], const uint16_t MelodyLength, const uint8_t tempo, uint16_t &MelodyCount ) {

  // 8th Octave Frequencies C8 to B8, lower octaves are calculated from this
  static const uint16_t Freq8[] PROGMEM = { 4186 , 4435 , 4699  , 4978 , 5274 , 5588 , 5920 , 6272 , 6645 , 7040 , 7459 , 7902 };

  // Grab the next note and play a note or a rest
  uint16_t data = pgm_read_word((uint16_t *)&MelodyData[ MelodyCount ]);

  if ((data & 0xF) == 0xF)
  {
    noTone(speakPin);
    
    
  }
  else
  {
    uint16_t Freq = pgm_read_word(&Freq8[data & 0xF]) / ( 1 << (8 - (data >> 4 & 0xF)) );
    tone(speakPin, Freq);
  }

  int16_t Duration = data >> 8;
  while (Duration--) delay(tempo);

  MelodyCount++;

  if   (MelodyCount > MelodyLength) {
    MelodyCount = 0;
  }

}


void play_PingPongSpNext_Melody_Data(const uint16_t MelodyData[], const uint16_t MelodyLength, const uint8_t tempo, uint16_t &MelodyCount ) {

  // 8th Octave Frequencies C8 to B8, lower octaves are calculated from this
  static const uint16_t Freq8[] PROGMEM = { 4186 , 4435 , 4699  , 4978 , 5274 , 5588 , 5920 , 6272 , 6645 , 7040 , 7459 , 7902 };

  // Grab the next note and play a note or a rest
  uint16_t data = pgm_read_word((uint16_t *)&MelodyData[ MelodyCount ]);

  if ((data & 0xF) == 0xF)
  {

    // I removed the noTone as the next Tone command will disble the previous
//   if ( Pong )  { 
//    noTone(speakPin);  
//   } else {
//    noTone(speakPin2);
//   }
   
    
    
  }
  else
  {
    uint16_t Freq = pgm_read_word(&Freq8[data & 0xF]) / ( 1 << (8 - (data >> 4 & 0xF)) );
   // this will bounce between the 2 speakers
   if ( Pong )  { 
    tone(speakPin, Freq);  
   } else {
     tone(speakPin2, Freq);
   }
    Pong = !Pong;
    
  }

  int16_t Duration = data >> 8;
  while (Duration--) delay(tempo);

  MelodyCount++;

  if   (MelodyCount > MelodyLength) {
    MelodyCount = 0;
  }

}
