#include <FastLED.h>
#define A {B11011,B10101,B00000,B01110,B01110}
#define B {B00001,B01110,B01101,B01010,B00001}
#define C {B00000,B01111,B01111,B01111,B00000}
#define D {B00001,B01110,B01110,B01110,B00001}
#define E {B00000,B01111,B00011,B01111,B00000}
#define up_F {B00000,B01111,B00011,B01111,B01111}
#define G {B00000,B01111,B01100,B01110,B00000}
#define H {B01110,B01110,B00000,B01110,B01110}
#define I {B00000,B11011,B11011,B11011,B00000}
#define J {B00000,B11011,B11011,B01011,B10111}
#define K {B01101,B01011,B00111,B01011,B01101}
#define L {B01111,B01111,B01111,B01111,B00000}
#define M {B10101,B01010,B01110,B01110,B01110}
#define N {B01110,B00110,B01010,B01100,B01110}
#define O {B00000,B01110,B01110,B01110,B00000}
#define P {B00011,B01101,B00011,B01111,B01111}
#define Q {B10011,B01101,B01001,B01001,B10010}
#define R {B00001,B01110,B00001,B01101,B01110}
#define S {B10000,B01111,B10001,B11110,B00001}
#define T {B00000,B11011,B11011,B11011,B11011}
#define U {B01110,B01110,B01110,B01110,B00000}
#define V {B01110,B01110,B01110,B10101,B11011}
#define W {B01110,B01110,B01110,B01010,B10101}
#define X {B01110,B10101,B11011,B10101,B01110}
#define Y {B01110,B10101,B11011,B11011,B11011}
#define Z {B00000,B11101,B11011,B10111,B00000}
#define BLANK {B11111,B11111,B11111,B11111,B11111}
#define ZERO {B10001,B01110,B01110,B01110,B10001}
#define ONE {B00000,B11110,B11110,B11110,B11110}
#define TWO {B10001, B01110,B11101,B11011,B00000}
#define THREE {B00000,B11110,B10000,B11110,B00000}
#define FOUR {B01110,B01110,B00000,B11110,B11110}
#define FIVE {B10000,B01111,B00000,B11110,B00000}
#define SIX {B00000,B01111,B00000,B01110,B00000}
#define SEVEN {B00000,B11101,B11011,B10111,B01111}
#define EIGHT {B00000,B01110,B10001,B01110,B00000}
#define NINE {B00000,B01110,B00000,B01111,B01111}
#define COLON {B10011,B10011,B11111, B10011,B10011}
#define ENTER {B100000}
#define NUM_LEDS 600 //Max 420
#define PIN 2 
#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];



void setup() {
    delay( 3000 ); // power-up safety delay
    Serial.begin(9600);
    FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(100); //0-255
    setAll(0,0,0);
}


int pixel;
int row;
int p;
int newLine;
byte color;
byte phrase[][5]={I,E,E,E,ENTER,R,I,P,ENTER,R,I,P};
void loop(){
  color=0;
  newLine=0;
  p=0;
  for(int letter =0; letter<12;letter++){
    if(phrase[letter][0]>B11111){
      newLine++;
      p=149*newLine; //149 to go to next row
      continue;
    }
    for(int i =0; i<5;i++){
      row=30*i+p+newLine;
      for(int b =0; b<5;b++){
        pixel=row+b;
        if(!((phrase[letter][i]>>(4-b))&B00001)){
          if(color%2==0){
            setPixel(pixel,100,100,100);
          }else{
            setPixel(pixel,0,0,200);
          }
        }
      }
    }
    p= p+6;  //5 is the length of the letter but 6 to add an extra space
    color++;
  }
  showStrip();
  delay(1000);
}

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),red,green,blue);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void showStrip() {
   FastLED.show();

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

//Function Rainbow
void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
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

void clearAll(){
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, 0, 0, 0); 
  }
}
