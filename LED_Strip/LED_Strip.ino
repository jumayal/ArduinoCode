#include "FastLED.h"
#define NUM_LEDS 12 
CRGB leds[NUM_LEDS];
#define PIN 6 
#define LED_PIN 10

void setup() {
  // put your setup code here, to run once:
  delay( 3000 ); // power-up safety delay
    Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

   
    //FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(30);
    pinMode(LED_PIN,OUTPUT);
    pinMode(8,INPUT);
    digitalWrite(LED_PIN,HIGH);
    delay(1000);

}
 int j=0;
 int attempt = 0;
void loop() {
  setPixel(j, 50,100,78);
  showStrip();
  delay(30);
  setPixel(j,0,0,0);
  showStrip();
  if(digitalRead(8) == HIGH){
    while(digitalRead(8) !=LOW){
      for(int i=0;i<25;i++){
      setPixel(j,0,0,0);
      showStrip();
      delay(100);
      setPixel(j, random(1,255),random(1,255),random(1,255));
      showStrip();
      delay(100);
      }
    }
    while(digitalRead(8) == LOW){
      rainbowCycle(20);
    }
    setAll(0,0,0);
    while(digitalRead(8) == HIGH){
      setPixel(j,0,0,0);
      showStrip();
      delay(100);
      setPixel(j, random(1,255),random(1,255),random(1,255));
      showStrip();
      delay(100);
    }
    j=0;
  }
  j++;
  if(j == NUM_LEDS){
    j=0;
  }
}
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    if(digitalRead(8) == HIGH){
      break;
    }
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

//void setAll(byte red, byte green, byte blue) {
//  for(int i = 0; i < NUM_LEDS; i++ ) {
//    setPixel(i, red, green, blue); 
//  }
//  showStrip();
//}

