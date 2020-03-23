#include <DS3231.h>
#include <FastLED.h>
#include <Wire.h>
byte A[] = {B11011,B10101,B00000,B01110,B01110};
byte B[] = {B00001,B01110,B01101,B01010,B00001};
byte C[] = {B00000,B01111,B01111,B01111,B00000};
byte D[] = {B00001,B01110,B01110,B01110,B00001};
byte E[] = {B00000,B01111,B00011,B01111,B00000};
byte up_F[] = {B00000,B01111,B00011,B01111,B01111};
byte G[] = {B00000,B01111,B01100,B01110,B00000};
byte H[] = {B01110,B01110,B00000,B01110,B01110};
byte I[] = {B00000,B11011,B11011,B11011,B00000};
byte J[] = {B00000,B11011,B11011,B01011,B10111};
byte K[] = {B01101,B01011,B00111,B01011,B01101};
byte L[] = {B01111,B01111,B01111,B01111,B00000};
byte M[] = {B10101,B01010,B01110,B01110,B01110};
byte N[] = {B01110,B00110,B01010,B01100,B01110};
byte O[] = {B00000,B01110,B01110,B01110,B00000};
byte P[] = {B00011,B01101,B00011,B01111,B01111};
byte Q[] = {B10011,B01101,B01001,B01001,B10010};
byte R[] = {B00001,B01110,B00001,B01101,B01110};
byte S[] = {B10000,B01111,B10001,B11110,B00001};
byte T[] = {B00000,B11011,B11011,B11011,B11011};
byte U[] = {B01110,B01110,B01110,B01110,B00000};
byte V[] = {B01110,B01110,B01110,B10101,B11011};
byte W[] = {B01110,B01110,B01110,B01010,B10101};
byte X[] = {B01110,B10101,B11011,B10101,B01110};
byte Y[] = {B01110,B10101,B11011,B11011,B11011};
byte Z[] = {B00000,B11101,B11011,B10111,B00000};
byte BLANK[] = {B11111,B11111,B11111,B11111,B11111};
byte ZERO[]={B10001,B01110,B01110,B01110,B10001};
byte ONE[] = {B11100,B10110,B11110,B11110,B11110};
byte TWO[] = {B10001, B01110,B11101,B11011,B00000};
byte THREE[] = {B00000,B11110,B10000,B11110,B00000};
byte FOUR[] = {B01110,B01110,B00000,B11110,B11110};
byte FIVE[] = {B10000,B01111,B00000,B11110,B00000};
byte SIX[] = {B00000,B01111,B00000,B01110,B00000};
byte SEVEN[] = {B00000,B11101,B11011,B10111,B01111};
byte EIGHT[] = {B00000,B01110,B00000,B01110,B00000};
byte NINE[] = {B00000,B01110,B00000,B11110,B11110};
byte COLON[] = {B10011,B10011,B11111, B10011,B10011};
byte SLASH[]= {B11110,B11101,B11011,B10111,B01111};
byte ENTER[] = {B100000};
#define NUM_LEDS 600 //Max 420
#define PIN 2 
#define UPDATES_PER_SECOND 100

typedef struct object{
  int x;
  int y;
}sprite;

sprite sun;
sprite moon;
CRGB leds[NUM_LEDS];
DateTime now;
RTClib RTC;
void setup() {
    delay( 3000 ); // power-up safety delay
    Serial.begin(57600);
    Wire.begin();
    FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(100); //0-255
    setAll(0,0,0);
}

int pixel;
int row;
int p;
int newLine;
byte color;
int firstDigit;
int secondDigit;


void loop(){
  now = RTC.now();
  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  printText();
  if((now.hour())>6 && (now.hour()<19)){
     placeSun(sun);
  }else{
    placeMoon(moon);
  }
  showStrip();
  delay(1000);
  clearAll();

}

void placeSun(sprite s){
  for(int i=1;i<6;i++){
    if((s.x+i>=0) && (s.x+i<30)){
      setPixel((s.x+i)+(s.y)*30,100,100,0);
      setPixel((s.x+i)+(s.y+4)*30,100,100,0);
    }
  }
  for(int j=1;j<4;j++){
    if((s.x>=0) && (s.x<30)){
      setPixel((s.x)+(s.y+j)*30,100,100,0);
    }
    if((s.x+6>=0) && (s.x+6<30)){
      setPixel((s.x+6)+(s.y+j)*30,100,100,0);
    }
  }
}
void placeMoon(sprite m){
  for(int i=1;i<6;i++){
    if((m.x+i>=0) && (m.x+i<30)){
      leds[(m.x+i)+(m.y)*30]=CRGB::DarkSlateGray;
      leds[(m.x+i)+(m.y+4)*30]=CRGB::DarkSlateGray;
    }
  }
  for(int j=1;j<4;j++){
    if((m.x>=0) && (m.x<30)){
      leds[(m.x)+(m.y+j)*30]=CRGB::DarkSlateGray;
    }
    if((m.x+6>=0) && (m.x+6<30)){
      leds[(m.x+6)+(m.y+j)*30]=CRGB::DarkSlateGray;
    }
  }
}

//up 1
//right 3
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

//7 oclock 3*4 at bottom right
void printText(){
  color=0;
  newLine=0;
  p=0;
  color=2;
  digitize(now.month());
  printDigits();
  color=1;
  printLetter(SLASH);
  color=2;
  digitize(now.day());
  printDigits();
  printLetter(ENTER);
  p=p+30;
  color=1;
  switch(now.hour()){
    case 1:
      moon.x=14;
      moon.y=12;
    case 13:
      printLetter(ZERO);
      printLetter(ONE);
      sun.x=14;
      sun.y=12;
      break;
    case 2:
      moon.x=17;
      moon.y=13;
    case 14:
      printLetter(ZERO);
      printLetter(TWO);
      sun.x=17;
      sun.y=13;
      break;
    case 3:
      moon.x=20;
      moon.y=14;
    case 15:
      printLetter(ZERO);
      printLetter(THREE);
      sun.x=20;
      sun.y=14;
      break;
    case 4:
      moon.x=23;
      moon.y=15;
    case 16:
      printLetter(ZERO);
      printLetter(FOUR);
      sun.x=23;
      sun.y=15;    
      break;
    case 5:
      moon.x=26;
      moon.y=16; 
    case 17:
      printLetter(ZERO);
      printLetter(FIVE);
      sun.x=26;
      sun.y=16;
      break;
    case 6:      
      moon.x=29;
      moon.y=17;
    case 18:
      printLetter(ZERO);
      printLetter(SIX);
      sun.x=29;
      sun.y=17;
      break;
    case 19:        
      moon.x=-4;
      moon.y=16;
    case 7:
      printLetter(ZERO);
      printLetter(SEVEN);
      sun.x=-4;
      sun.y=16;
      break;
    case 20:
      moon.x=-1;
      moon.y=15;
    case 8:
      printLetter(ZERO);
      printLetter(EIGHT);
      sun.x=-1;
      sun.y=15;
      break;
    case 21:
      moon.x=2;
      moon.y=14;
    case 9:
      printLetter(ZERO);
      printLetter(NINE);
      sun.x=2;
      sun.y=14;
      break;
    case 22:
      moon.x=5;
      moon.y=13;
    case 10:
      printLetter(ONE);
      printLetter(ZERO);
      sun.x=5;
      sun.y=13;
      break;
    case 23:
      moon.x=8;
      moon.y=12;
    case 11:
      printLetter(ONE);
      printLetter(ONE);
      sun.x=8;
      sun.y=12;
      break;
    case 0:
      moon.x=11;
      moon.y=11;
    case 12:
      printLetter(ONE);
      printLetter(TWO);
      sun.x=11;
      sun.y=11;
      break;
    default:
      break;
  }
  color=2;
  printLetter(COLON);
  color=1;
  digitize(now.minute());
  printDigits();
 }
 void digitize(int num){
  int mod;
  mod = num % 10;  //split last digit from number
  firstDigit=mod;
  num = num / 10;    //divide num by 10. num /= 10 also a valid one 
  mod = num % 10;  //split last digit from number
  secondDigit=mod;
 }
void printLetter(byte letter [5]){
   if(letter[0]>B11111){
      newLine++;
      p=150*newLine; //149 to go to next row
      return;
    }
  for(int i =0; i<5;i++){
   row=30*i+p;       
   for(int b =0; b<5;b++){
      pixel=row+b;
      if(!((letter[i]>>(4-b))&B00001)){
        if(color==1){
          setPixel(pixel,0,100,0);
        }else if(color ==2){
          setPixel(pixel,0,0,200);
        }else if(color ==3){
          setPixel(pixel,0,0,200);
        }else if(color ==4){
          setPixel(pixel,0,0,200);
        }
      }
    }
  }
  p= p+6;  //5 is the length of the letter but 6 to add an extra space
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

void clearAll(){
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, 0, 0, 0); 
  }
}
void printDigits(){
     switch(secondDigit){
    case 0:
      printLetter(ZERO);
      break;
    case 1:
      printLetter(ONE);
      break;
    case 2:
      printLetter(TWO);
      break;
    case 3:
      printLetter(THREE);
      break;
    case 4:
      printLetter(FOUR);
      break;
    case 5:
      printLetter(FIVE);
      break;
    case 6:
      printLetter(SIX);
      break;
    case 7:
      printLetter(SEVEN);
      break;
    case 8:
      printLetter(EIGHT);
      break;
    case 9:
      printLetter(NINE);
      break;
    default:
      break;
  }
  switch(firstDigit){
    case 0:
      printLetter(ZERO);
      break;
    case 1:
      printLetter(ONE);
      break;
    case 2:
      printLetter(TWO);
      break;
    case 3:
      printLetter(THREE);
      break;
    case 4:
      printLetter(FOUR);
      break;
    case 5:
      printLetter(FIVE);
      break;
    case 6:
      printLetter(SIX);
      break;
    case 7:
      printLetter(SEVEN);
      break;
    case 8:
      printLetter(EIGHT);
      break;
    case 9:
      printLetter(NINE);
      break;
    default:
      break;
  }
}
