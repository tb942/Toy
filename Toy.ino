/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
 modified to C syntax on 30 Jan 2017 for use with the sdunio environment
 by Michael Mayer
*/

#include <Servo.h>

Servo(myservo);  	// create servo "object" to control a servo

const uint8_t servoPin = PD4;
const uint8_t potPin = PD6;  	// analog pin used to connect the potentiometer
const uint8_t  button1 = PA1;    // the pin that the pushbutton is attached to
const uint8_t  button2 = PA2;    // the pin that the pushbutton is attached to
const uint8_t  button3 = PA3;    // the pin that the pushbutton is attached to
const uint8_t leds[] = {PB5, PB4 ,PC3, PC4, PC5, PC6, PC7, PD1};        // the pin that the LED is attached to

uint8_t currentPos = 0b00000001;
uint8_t values = 0b00000000;
uint16_t val;        // variable to read the value from the analog pin
bool servoInvert = false;


void setup() {
  myservo_attach(servoPin);	// attaches the servo on pin 9 to the servo object
  
  // initialize the button pin as a input:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  // initialize the LED as an output:
  for(uint8_t i=0;i<8;i++){
    pinMode(leds[i], OUTPUT);
  }
}


void loop() {

  val = analogRead(potPin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 160*(servoInvert)+10, 160*(!servoInvert)+10);     // scale it to use it with the servo (value between 0 and 180)
  myservo_write(val);                  // sets the servo position according to the scaled value

  if(digitalRead(button1)){
    while(digitalRead(button1)){}
    currentPos <<= 1;
    if(currentPos == 0){
      currentPos = 0b00000001;
    }
  }
  if(digitalRead(button2)){
    while(digitalRead(button2)){}
    values &= ~currentPos;
  }
  if(digitalRead(button3)){
    while(digitalRead(button3)){}
    values |= currentPos;
  }

  for(uint8_t i=0;i<8;i++){
    digitalWrite(leds[i], ((values >> i) % 2));
  }

  if(values==0b00000000){
    servoInvert = false;
  }else if(values==0b11111111){
    servoInvert = true;
  }
}
