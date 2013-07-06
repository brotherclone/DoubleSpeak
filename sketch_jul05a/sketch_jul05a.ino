/*
Voice Box Demo Sketch
Written by Ryan Owens
SparkFun Electronics

Uses the Voice Box Shield from SparkFun to send the message "All your base are belong to us" and a series
of robot sounds to the SpeakJet chip on the shield. 

A speaker can be plugged directly into the SPK+ and - pins on the shield.

*/

//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <SoftwareSerial.h>

//Define the Pin Numbers for the sketch.
/*#define E0  4
#define E1  3
#define E2  7
#define E3  8
#define E4  9
#define E5  10
#define E6  11
#define E7  12
*/
#define RDY  13
#define RES  6
#define SPK  5

#define txPin  2

//Create a SoftSerial Objet
SoftwareSerial speakjet = SoftwareSerial(0, txPin);

//The message array contains the command for sounds to be sent in order to inunciate the words "All your base belong to us." Check the SpeakJet Manual for more information
//on producing words
                                                  //All              Your         Base                 Are     Belong                       to          us
char message[] = {20, 96, 21, 114, 22, 88, 23, 5, 8, 135, 8, 146, 5, 128, 153, 5, 170, 154, 8, 188, 5, 152, 5, 170, 8,128,146,8,135,8,144,5,8,191,162,5,8,134,187};

//The sounds array contains the commands to send robot sounds to the SpeakJet chip.
char sounds[] = {200, 201, 202, 203, 220, 221, 222};

void setup()  
{
  //Configure the pins for the SpeakJet module
  pinMode(txPin, OUTPUT);
  pinMode(SPK, INPUT);
  
  //Set up a serial port to talk from Arduino to the SpeakJet module on pin 3.
  speakjet.begin(9600);    
  
  //Configure the Ready pin as an input
  pinMode(RDY, INPUT);
  
  //Configure Reset line as an output
  pinMode(RES, OUTPUT);
       
  //Configure all of the Event pins as outputs from Arduino, and set them Low.
 /* for(int i=E0; i<=E7; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  */
  //All I/O pins are configured. Reset the SpeakJet module
  digitalWrite(RES, LOW);
  delay(100);
  digitalWrite(RES, HIGH);
  
}

void loop()
{  
  //Send "All Your Base are Belong to Us" to the SpeakJet module
  speakjet.print(message);
  //Wait before sending the next string.
  delay(3000);    
  //Send the robotic sounds to the module.
  speakjet.print(sounds);
  delay(3000);
}
