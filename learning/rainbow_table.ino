#include <Arduino.h>
#include <inttypes.h>
#include <FastLED.h>

// we have a 9 by 9 grid of LED's on pin A0
#define LED_DATA_PIN A0
#define NUM_LEDS 81 // 9 x 9 = 81
CRGB leds[NUM_LEDS];

// cycle through the rainbow
inline void cycle3(uint8_t& v0, uint8_t& v1, uint8_t& v2, uint8_t& curHi)
{
  // shift values
  if (curHi == 0) {
    v0--; v1++;
  } else if (curHi == 1) {
    v1--; v2++;
  } else if (curHi == 2) {
    v2--; v0++;
  }

  // allign curhi
  if (v0 <= 0 && curHi == 0)
    curHi = 1;
  else if (v1 <= 0 && curHi == 1)
    curHi = 2;
  else if (v2 <= 0 && curHi == 2)
    curHi = 0;
}

void setup() 
{
  // link the colors to the LEDs
  FastLED.addLeds <WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() 
{
  // this shifts the rainbow along the 81-led view
  static uint16_t offset = 0;
  
  // initialize the rainbow
  uint8_t r = 255, g = 0, b = 0, curHi = 0;

  // shift the rainbow
  for (int i = 0; i < offset; i++)
    cycle3(r, g, b, curHi);

  // set the colors
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(r, g, b);
    cycle3(r, g, b, curHi);
  }

  // apply the colors
  FastLED.show();

  // if you want it to go slower
  // the code written here actually runs slow enough
  // that you don't really need a delay
  //delay(5);

  // offset reached 24bit max (2^24)
  if (++offset > 16777216)
    offset = 0;

    
}


