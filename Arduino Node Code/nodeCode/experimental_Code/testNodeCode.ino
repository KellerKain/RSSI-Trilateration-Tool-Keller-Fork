/* 
This code serves to test the functionality of the arduino and 
update the orginal code 
*/


#include "Xbee.h" //Includes the Xbee library from arduino software
#include "Timerone.h" // Includes the Timeone library
#include "definitions.h"

/*
The following creates Xbee objects and the classes for storing data within 
the xbee.h header file
*/

XBee xbee = XBee();
ZBRxResponse rx; //Creates the Class for the rx response within the Xbee Library
ZBTxRequest tx; //Stores Payload class data within the Xbee Library

// Mode Variable 
int mode = ANCHOR_NODE; // Sets the default mode to anchor


//Setup code that intializes the ZigBee radio 
void setup() {
    pinMode(2,INPUT); //sets the pin mode for determining the mode of the radio
  
    Serial.begin(9600); 
    xbee.setSerial(Serial); // Sets the serial port to the port definied by arduino
    
    Timer1.initialize(); // set a timer of length second - this code breaks analogWrite on digital pins 9 and 10
  
    // get initial mode setting and query for intial anchor list
    if(digitalRead(2)) {
      delay(1000);  // give the XBee time to connect to the coordinator
      Timer1.attachInterrupt( timerISR ); // attach the service routine here
      // anchorSearch(); //Most likely depricated/not useful
      mode = MOBILE_NODE;
      Serial.println("Mobile Mode");
    }
    // added in so that in the event of a switch the service routine is removed
    // Removes the need for a loop function in the orginal code
    else {
        if(mode != ANCHOR_NODE) { 
            mode = ANCHOR_NODE;
            Serial.println("Anchor Mode");
            Timer1.attachInterrupt( timerISR ); //removes the service routine
        }
        else { 
            mode = ANCHOR_NODE;
            Serial.println("Anchor Mode");
         }
    }
    
  }



