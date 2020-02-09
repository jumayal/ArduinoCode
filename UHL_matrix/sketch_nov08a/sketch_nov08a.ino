#include <FastLED.h>

#define NUM_LEDS 595

#define MAX_SHOTS 3
#define MIN_SHOTS 1

#define SPEED_OF_SHOT 4

#define MIN_WAIT_BETWEEN_SHOTS 250
#define MAX_WAIT_BETWEEN_SHOTS 1250


CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812, 6>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop()
{

  // SHOOT THERE
  // Get random number of shots [0,4]
  // for (int i = 1; i <= number; i++)
  //     Shoot there (green)
  //     Delay random time [0.5,2] seconds
  // end

  int numShots = rand() % ((MAX_SHOTS - MIN_SHOTS) + 1) + MIN_SHOTS;
  for (int currShot = 1; currShot <= numShots; currShot++)
  {
    Serial.println("Green shot");
    doGreenShot();
  }

  int range = MAX_WAIT_BETWEEN_SHOTS - MIN_WAIT_BETWEEN_SHOTS;
  int delayBetweenShot = rand() % (range) + MIN_WAIT_BETWEEN_SHOTS;
  delay(delayBetweenShot);

  // SHOOT BACK
  // Get random number of shots [0,4]
  // for (int i = 1; i <= number; i++)
  //     Shoot back (red)
  //     Delay random time [0.5,2] seconds
  // end

  numShots = rand() % ((MAX_SHOTS - MIN_SHOTS) + 1) + MIN_SHOTS;
  for (int currShot = 1; currShot <= numShots; currShot++)
  {
    Serial.println("Red shot");
    doRedShot();
  }
  
  range = MAX_WAIT_BETWEEN_SHOTS - MIN_WAIT_BETWEEN_SHOTS;
  delayBetweenShot = rand() % (range) + MIN_WAIT_BETWEEN_SHOTS;
  delay(delayBetweenShot);
}


/*
 * Calls the shoot method with the green parameter
 */
void doGreenShot()
{
  int startingPin = 0; // The LED to start at

  for (int i = startingPin; i < NUM_LEDS-11; i+=2)
  {
    fill_solid(leds+i, 10, CRGB::Red);
    FastLED.show(); // Show changes
    leds[i] = CRGB::Black; // Set the first one to black
    leds[i+1] = CRGB::Black; // Set the first one to black
    leds[i+2] = CRGB::Black; // Set the first one to black
    leds[i+3] = CRGB::Black; // Set the first one to black
    delay(SPEED_OF_SHOT+3);
  }

  clearEnds();
  FastLED.show();
}

/*
 * Calls the shoot method with the red parameter
 */
void doRedShot()
{

  int startingPin = NUM_LEDS - 10; // The LED to start at

  for (int i = startingPin; i >= 0; i-=2)
  {
    int location = NUM_LEDS - i;
    fill_solid(leds + i, 10, CRGB::Green);
    FastLED.show(); // Show changes
    leds[i+7] = CRGB::Black; // Set the first one to black
    leds[i+8] = CRGB::Black; // Set the first one to black
    leds[i+9] = CRGB::Black; // Set the first one to black
    leds[i+10] = CRGB::Black; // Set the first one to black
    delay(SPEED_OF_SHOT);
  }
  clearEnds();
  FastLED.show();

}

void clearEnds()
{
  for (int i = NUM_LEDS - 1; i >= NUM_LEDS - 12; i--)
  {
    leds[i] = CRGB::Black; 
  }

  for (int i = 0; i <= 12; i++)
  {
    leds[i] = CRGB::Black; 
  }
  FastLED.show();
}
