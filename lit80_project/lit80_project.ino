
#include <FastLED.h>
#include "FastLED.h"
#define NUM_LEDS 57 //Max 420
CRGB leds[NUM_LEDS];
#define PIN 10 
#define UPDATES_PER_SECOND 100
// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
byte spectrum[7];
byte channel =A0; //Green Wire
byte ctrlReset= 9; //Orange Wire
byte ctrlStrobe=8; //Yellow Wire
byte holder;
void setup() {
    delay( 3000 ); // power-up safety delay
    Serial.begin(9600);
    pinMode(A0,INPUT);
    pinMode(ctrlReset,OUTPUT);
    pinMode(ctrlStrobe,OUTPUT);
    FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(200);
}


int lol=0;
void loop()
{
  //delay(500);
  setAll(0, 0,0);
  lol=analogRead(channel);
  Serial.println(lol);
  if(970<lol){ //white
    Sparkle(255, 255, 255, 30);
  }else if((lol>300)&&(lol<355)){ //black
    police();
  }else{ //nothing
    rainbowCycle(30);
  }
}

void showStrip() {
   FastLED.show();

}
void police(){
  strobeRed();
  delay(50);
  strobeBlue();
  delay(50);
}
void strobeRed()
{
  for (int i = 0; i < 6; i++)
  {
    for (int dot = 0; dot < NUM_LEDS; dot++) {
      if (dot % 2 == 0)
      {
        leds[dot] = CRGB::Red;
        FastLED.show();
        leds[dot] = CRGB::Black;
      }
    }
  }
}
void strobeBlue()
{
  for (int i = 0; i < 6; i++)
  {
    for (int dot = 0; dot < NUM_LEDS; dot++) {
      if (dot % 2 == 1)
      {
        leds[dot] = CRGB::Blue;
        FastLED.show();
        leds[dot] = CRGB::Black;
      }
    }
  }
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
////Function RGBLoop()
//void RGBLoop(){
//  for(int j = 0; j < 3; j++ ) { 
//    // Fade IN
//    for(int k = 0; k < 256; k++) { 
//      switch(j) { 
//        case 0: setAll(k,0,0); break;
//        case 1: setAll(0,k,0); break;
//        case 2: setAll(0,0,k); break;
//      }
//      showStrip();
//      delay(3);
//    }
//    // Fade OUT
//    for(int k = 255; k >= 0; k--) { 
//      switch(j) { 
//        case 0: setAll(k,0,0); break;
//        case 1: setAll(0,k,0); break;
//        case 2: setAll(0,0,k); break;
//      }
//      showStrip();
//      delay(3);
//    }
//  }
//}
//
////------------------------------------------------
////Fades in and out of color
//void FadeInOut(byte red, byte green, byte blue){
//  float r, g, b;
//      
//  for(int k = 0; k < 256; k=k+1) { 
//    r = (k/256.0)*red;
//    g = (k/256.0)*green;
//    b = (k/256.0)*blue;
//    setAll(r,g,b);
//    showStrip();
//  }
//     
//  for(int k = 255; k >= 0; k=k-2) {
//    r = (k/256.0)*red;
//    g = (k/256.0)*green;
//    b = (k/256.0)*blue;
//    setAll(r,g,b);
//    showStrip();
//  }
//}
//
////-------------------------------------------------------
////Function Rainbow
void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }

    //juan added
    lol=analogRead(channel);
    Serial.println(lol);
    if(970<lol){ //white
      return;
    }else if((lol>300)&&(lol<355)){ //black
      return;
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
//
////Moves it left to right and such function
//void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
//  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
//}
//
//void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
//  for(int i =((NUM_LEDS-EyeSize)/2); i>=0; i--) {
//    setAll(0,0,0);
//    
//    setPixel(i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      setPixel(i+j, red, green, blue); 
//    }
//    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
//    
//    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      setPixel(NUM_LEDS-i-j, red, green, blue); 
//    }
//    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
//    
//    showStrip();
//    delay(SpeedDelay);
//  }
//  delay(ReturnDelay);
//}
//
//void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
//  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2); i++) {
//    setAll(0,0,0);
//    
//    setPixel(i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      setPixel(i+j, red, green, blue); 
//    }
//    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
//    
//    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      setPixel(NUM_LEDS-i-j, red, green, blue); 
//    }
//    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
//    
//    showStrip();
//    delay(SpeedDelay);
//  }
//  delay(ReturnDelay);
//}
//
//void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
//  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
//    setAll(0,0,0);
//    setPixel(i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      setPixel(i+j, red, green, blue); 
//    }
//    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
//    showStrip();
//    delay(SpeedDelay);
//  }
//  delay(ReturnDelay);
//}
//
//void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
//  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
//    setAll(0,0,0);
//    setPixel(i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      setPixel(i+j, red, green, blue); 
//    }
//    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
//    showStrip();
//    delay(SpeedDelay);
//  }
//  delay(ReturnDelay);
//}
////Twinkle sound
//
////random twinkle
//void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
//  setAll(0,0,0);
//  
//  for (int i=0; i<Count; i++) {
//     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
//     showStrip();
//     delay(SpeedDelay);
//     if(OnlyOne) { 
//       setAll(0,0,0); 
//     }
//   }
//  
//  delay(SpeedDelay);
//}
//
//Sparkle
void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
   int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}
//
////Runing lights
//void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
//  int Position=0;
//  
//  for(int j=0; j<NUM_LEDS*2; j++)
//  {
//      Position++; // = 0; //Position + Rate;
//      for(int i=0; i<NUM_LEDS; i++) {
//        // sine wave, 3 offset waves make a rainbow!
//        //float level = sin(i+Position) * 127 + 128;
//        //setPixel(i,level,0,0);
//        //float level = sin(i+Position) * 127 + 128;
//        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
//                   ((sin(i+Position) * 127 + 128)/255)*green,
//                   ((sin(i+Position) * 127 + 128)/255)*blue);
//      }
//      
//      showStrip();
//      delay(WaveDelay);
//  }
//}
//
//
////Meteor rain
//void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
//  setAll(0,0,0);
//  
//  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
//    
//    
//    // fade brightness all LEDs one step
//    for(int j=0; j<NUM_LEDS; j++) {
//      if( (!meteorRandomDecay) || (random(10)>5) ) {
//        fadeToBlack(j, meteorTrailDecay );        
//      }
//    }
//    
//    // draw meteor
//    for(int j = 0; j < meteorSize; j++) {
//      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
//        setPixel(i-j, red, green, blue);
//      } 
//    }
//   
//    showStrip();
//    delay(SpeedDelay);
//  }
//}
//
//void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
//  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
//    for (int q=0; q < 3; q++) {
//      for (int i=0; i < NUM_LEDS; i=i+3) {
//        setPixel(i+q, red, green, blue);    //turn every third pixel on
//      }
//      showStrip();
//     
//      delay(SpeedDelay);
//     
//      for (int i=0; i < NUM_LEDS; i=i+3) {
//        setPixel(i+q, 0,0,0);        //turn every third pixel off
//      }
//    }
//  }
//}
//
//void fadeToBlack(int ledNo, byte fadeValue) {
// #ifdef ADAFRUIT_NEOPIXEL_H 
//    // NeoPixel
//    uint32_t oldColor;
//    uint8_t r, g, b;
//    int value;
//    
//    oldColor = strip.getPixelColor(ledNo);
//    r = (oldColor & 0x00ff0000UL) >> 16;
//    g = (oldColor & 0x0000ff00UL) >> 8;
//    b = (oldColor & 0x000000ffUL);
//
//    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
//    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
//    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
//    
//    strip.setPixelColor(ledNo, r,g,b);
// #endif
// #ifndef ADAFRUIT_NEOPIXEL_H
//   // FastLED
//   leds[ledNo].fadeToBlackBy( fadeValue );
// #endif  
//}
//
//
