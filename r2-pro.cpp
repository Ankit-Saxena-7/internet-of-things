// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_MPR121.h>

/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

// Torch toggle
#include <Particle.h>
const int pinIRQ = D6;

// Torch toggle
// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Torch toggle
// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

// Torch toggle
volatile bool capTouched;
void capISR()
{
  capTouched = true;
}

// Torch toggle
int ledTorch = D3;

// Wheels movement
const int vStop = 0;
const int vCW = 125;
const int vCCW = 250;

// Head rotation
const int vStopHead = 0;
const int vCWHead = 125;
const int vCCWHead = 250;

// Wheels movement
bool vMoveForward = false;
bool vMoveBackward = false;
bool vMoveLeft = false;
bool vMoveRight = false;
bool vMoveStop = false;
bool vMoveHead = false;

// Wheels movement
int leftWheel = D5;
int rightWheel = D7;
int domeHead = D4;

void setup() 
{
    //Torch toggle
    Serial.begin(9600);
    
    // Torch toggle
    pinMode(ledTorch, OUTPUT);
        
    // Wheels movement
    pinMode(leftWheel, OUTPUT);
    pinMode(rightWheel, OUTPUT);
    pinMode(domeHead, OUTPUT);
    
    // Toggle torch
    pinMode(pinIRQ, INPUT_PULLUP);
    attachInterrupt(pinIRQ, capISR, FALLING);
    digitalWrite(ledTorch, LOW);
   
    // Wheels movement
    Spark.function("moveForwardParticle", moveForward);
    Spark.function("moveBackwardParticle", moveBackward);
    Spark.function("moveLeftParticle", moveLeft);
    Spark.function("moveRightParticle", moveRight);
    Spark.function("moveStopParticle", moveStop);
    
    // Head rotation
    Spark.function("moveHeadParticle", moveHead);
}

void loop() 
{
    // Toggle torch
    if (capTouched)
    {
        capTouched = false;
        Serial.print("teehee");
        // Get the currently touched pads
        currtouched = cap.touched();
      
        for (uint8_t i=0; i<12; i++) {
            
            // it if *is* touched and *wasnt* touched before, alert!
            if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
                Serial.print(i); Serial.println(" touched");
            
                int selectedWire = i;
              
                if (selectedWire == 9) {
                    digitalWrite(ledTorch, HIGH);
                }
                else if(selectedWire == 11) {
                    digitalWrite(ledTorch, LOW);
                }

            }
            // if it *was* touched and now *isnt*, alert!
            if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
                Serial.print(i); Serial.println(" released");

            }
        }
    
        // reset our state
        lasttouched = currtouched;
    }
  
    // Wheels movement
    if(vMoveForward == true){
        analogWrite(leftWheel, vCW);
        analogWrite(rightWheel, vCW);                
        Particle.publish("R2-D2-Leia-Message", "Only-Hope", PUBLIC);
    }
    else if(vMoveBackward == true){
        analogWrite(leftWheel, vCCW);
        analogWrite(rightWheel, vCCW);
        Particle.publish("R2-D2-Leia-Message", "Only-Hope", PUBLIC);
    }
    else if(vMoveLeft == true){
        analogWrite(leftWheel, vCW);
        analogWrite(rightWheel, vCCW);
        Particle.publish("R2-D2-Leia-Message", "Only-Hope", PUBLIC);
    }
    else if(vMoveRight == true){
        analogWrite(leftWheel, vCCW);
        analogWrite(rightWheel, vCW);
        Particle.publish("R2-D2-Leia-Message", "Only-Hope", PUBLIC);
    }
    else if(vMoveStop == true){
        analogWrite(leftWheel, vStop);
        analogWrite(rightWheel, vStop);
        Particle.publish("R2-D2-Leia-Message", "Only-Hope", PUBLIC);
    }
    
    // Move head
    if(vMoveHead == true){
        analogWrite(domeHead, vCWHead);
        delay(500);
        analogWrite(domeHead, vStopHead);
        analogWrite(domeHead, vCCWHead);
        delay(500);
        analogWrite(domeHead, vStopHead);
    }
}

// Wheels movement
int moveForward(String command){
    vMoveForward = true;
    vMoveBackward = false;
    vMoveLeft = false;
    vMoveRight = false;
    vMoveStop = false;
}

// Wheels movement
int moveBackward(String command){
    vMoveForward = false;
    vMoveBackward = true;
    vMoveLeft = false;
    vMoveRight = false;
    vMoveStop = false;
}

// Wheels movement
int moveLeft(String command){
    vMoveForward = false;
    vMoveBackward = false;
    vMoveLeft = true;
    vMoveRight = false;
    vMoveStop = false;
}

// Wheels movement
int moveRight(String command){
    vMoveForward = false;
    vMoveBackward = false;
    vMoveLeft = false;
    vMoveRight = true;
    vMoveStop = false;
}

// Wheels movement
int moveStop(String command){
    vMoveForward = false;
    vMoveBackward = false;
    vMoveLeft = false;
    vMoveRight = false;
    vMoveStop = true;
    vMoveHead = false;
}

// Move head
int moveHead(String command){
    vMoveHead = true;
}
