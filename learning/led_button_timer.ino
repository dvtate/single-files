#include "Arduino.h"
#include <inttypes.h>

#define BUTTON_PIN 4
#define BUZZ_PIN 5

#define RED_LED_PIN 8
#define GREEN_LED_PIN 9


BiLED_pwm ind(9,8);

void setup(){
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  
  Serial.begin(9600);
  
}

void loop(){

  static uint8_t timeRemaining = 255;
  
  // wait until the button is pressed
  if (digitalRead(BUTTON_PIN)) {
    
    // wait until button is released
    while (digitalRead(BUTTON_PIN))
      delay(5);
    
    // start the timer
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    
    // wait until time runs out
    for (uint8_t timeRemaining = 0; timeRemaining < 255; timeRemaining++) {
      
      // change the LED color
      analogWrite(GREEN_LED_PIN, 255 - timeRemaining);
      analogWrite(RED_LED_PIN, timeRemaining);
      
      // they answered the question in time
      for (uint8_t wait = 0; wait < 4; wait++) {
        if (digitalRead(BUTTON_PIN))
          goto finished_question;
        delay(10);
      }
    }
    
    // they ran out of time
    tone(BUZZ_PIN, 500, 750);
  }

// the question was answered or they ran out of time
finished_question:
  
  // turn off the LEDs 
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
 
  // wait until the button is pressed again
  while (digitalRead(BUTTON_PIN))
    delay(5);

    
}
