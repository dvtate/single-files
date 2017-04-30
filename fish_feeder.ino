#include "Arduino.h"
#include <Servo.h> 
#include <inttypes.h>

#define MILISECONDS_PER_DAY 5000


Servo feedServo; 


void feedFish(uint8_t& slotNum, int8_t initialPosition = -180){
  // 360 / 9 = 40 degrees
  feedServo.write(40 * slotNum);
  delay(500);

  feedServo.write(initialPosition);

  slotNum++;
  
}


void setup(){
  
  feedServo.attach(4); 
  feedServo.write(-180);

} 


void loop(){ 
  static uint32_t msRemaining = MILISECONDS_PER_DAY;
  static uint8_t slot = 0;

  // wait 
  delay(5);  
  msRemaining -= 5;

  
  if (msRemaining == 0) {
    feedFish(slot, 180);
    msRemaining = MILISECONDS_PER_DAY;
    return; 
  }
}
