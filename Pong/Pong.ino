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
#define NINE {B00000,B01110,B00000,B00001,B00000}
#define COLON {B10011,B10011,B11111, B10011,B10011}
#define ENTER {B100000}

#define maxY 20
#define maxX 30
#define NUM_LEDS maxY*maxX
CRGB leds[NUM_LEDS];
#define PIN 2 
#define UPDATES_PER_SECOND 100
#define p1 17 //The pin number for reading the sensor
#define p2 18 //THe pin number for reading the sensor
#define INITBALLSPEED 3
#define INITPADDLESPEED 5
#define INCREASE_DIFFICULTY 10

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.

//Sprite that can be controlled
typedef struct object{
  int x;
  int y;
  byte direct;
}sprite;

//Sprite that moves on its own
typedef struct mv{
  int x;
  int y;
  float vectorX;
  float vectorY;
}movingSprite;

//For displaying words
byte phrase[][5]={C,O,V,E,R,ENTER,S,E,N,S,O,R};
int pixel; // for words
int row;  //Which row is the letter at
int p;  //The origin of the letter character
byte color;
int ArrayLength;
int newLine; //To hold the additional leds considering new lines
sprite paddleOne; // Player 1
sprite paddleTwo; //Player 2
movingSprite ball; //ball
byte direct;
int ballTime; //is a counter for ball
int paddleTime; //is a Counter for the paddle 

int ballSpeed; //The threshold for when the ball can update. Value is compared to the ball time
int paddleSpeed; //The threshold for when the paddle can update. Value is compared to the paddle time
int difficultCounter;
void setup() {
    delay(6000); // power-up safety delay

    FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(100); //0-255
    pinMode(p1,INPUT);
    pinMode(p2,INPUT);

    //Initializing sprite update
    ballTime=0;
    paddleTime=0;
    difficultCounter=0;
    ballSpeed=INITBALLSPEED;
    paddleSpeed=INITPADDLESPEED;
    setAll(0,0,0);
    paddleOne.x=1;
    paddleOne.y=0;
    paddleTwo.x=28;
    paddleTwo.y=0;
    ball.x=15;
    ball.y=6;
    placeBall(ball);
    placePaddle(paddleOne);
    placePaddle(paddleTwo);
    border();
    showStrip();
    paddleTwo.direct=0;
    paddleOne.direct=0;
    ball.vectorY=random(-1,2);
    ball.vectorX=random(-1,2);
}

void loop(){
  ballTime++;
  paddleTime++;
  if(paddleTime>paddleSpeed){
    if(digitalRead(p1) && paddleOne.y>1){
      paddleOne.y=paddleOne.y-1;
    }else if(paddleOne.y<maxY-4 && !digitalRead(p1) ){
      paddleOne.y=paddleOne.y+1;
    }
    if(digitalRead(p2)&& paddleTwo.y>1){
      paddleTwo.y=paddleTwo.y-1;
    }else if(paddleTwo.y<maxY-4 && !digitalRead(p2)){
      paddleTwo.y=paddleTwo.y+1;
    }
      paddleTime=0;
  }
  if(ballTime>ballSpeed){
    ball.x=ball.x+ball.vectorX;
    ball.y=ball.y+ball.vectorY;
    ballTime=0;
 
    if( ball.x+ball.vectorX == 1 && (ball.y+ball.vectorY>=paddleOne.y) && (ball.y+ball.vectorY<(paddleOne.y+4))){
      if((ball.y+ball.vectorY==paddleOne.y) &&(ball.vectorY>0)){
        ball.vectorY=ball.vectorY*-1;
      }else if((ball.y+ball.vectorY==paddleOne.y+3) &&(ball.vectorY<0)){
        ball.vectorY=ball.vectorY*-1;
      }else{
        ball.vectorY=ball.vectorY * pow(-1,random(0,2));
      }
      ball.vectorX=ball.vectorX*-1;
      difficultCounter++;
    }else if( ball.x+ball.vectorX == maxX-2 && (ball.y+ball.vectorY>=paddleTwo.y) && (ball.y+ball.vectorY<(paddleTwo.y+4))){
      if((ball.y+ball.vectorY==paddleTwo.y) &&(ball.vectorY>0)){
        ball.vectorY=ball.vectorY*-1;
      }else if((ball.y+ball.vectorY==paddleTwo.y+3) &&(ball.vectorY<0)){
        ball.vectorY=ball.vectorY*-1;
      }else{
        ball.vectorY=ball.vectorY * pow(-1,random(0,2));
      }
      ball.vectorX=ball.vectorX*-1;
    } else if((ball.x>=(maxX-1)) || (ball.x<1)){ //take this out when we can controll paddles
      endGame();
    }   if((ball.y<2) ||(ball.y>(maxY-3))){
      ball.vectorY=ball.vectorY*-1;
    }
    

  }
  if(difficultCounter > INCREASE_DIFFICULTY){
    ballSpeed=ballSpeed-1;
    difficultCounter=0;
  }
  placePaddle(paddleOne);
  placePaddle(paddleTwo);
  placeBall(ball);
  showStrip();
  delay(5);
  clearBall(ball);
  clearPaddle(paddleOne);
  clearPaddle(paddleTwo);
}

void showStrip() {
   FastLED.show();

}

void border(){
  for(int i=0;i<30;i++){
    leds[i].g=100;
    leds[i+(maxX*(maxY-1))].g=100;
  }
  for(int i=1;i<maxY;i++){
    leds[i*maxX].g=100;
    leds[(maxX-1)+30*i].g=100;
  }
}

void clearBorder(){
  for(int i=0;i<30;i++){
    leds[i].g=0;
    leds[i+(maxX*(maxY-1))].g=0;
  }
  for(int i=1;i<maxY;i++){
    leds[i*maxX].g=0;
    leds[(maxX-1)+30*i].g=0;
  }
}
void placeBall(movingSprite ball){
//  leds[ball.x + (ball.y+1)*30].r=100;
//  leds[ball.x-1 + (ball.y+1)*30].r=100;
//  leds[(ball.x -1) + ball.y*30].r=100;
  leds[ball.x + ball.y*30].b=50;
}

void placePaddle(sprite paddle){
  leds[paddle.x + (paddle.y)*30].r=100;
  leds[paddle.x + (paddle.y+1)*30].r=100;
  leds[paddle.x + (paddle.y+2)*30].r=100;
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

void clearBall(movingSprite ball){
   leds[ball.x + ball.y*30].b=0;
}

void clearPaddle(sprite paddle){
  leds[paddle.x + (paddle.y)*30].r=0;
  leds[paddle.x + (paddle.y+1)*30].r=0;
  leds[paddle.x + (paddle.y+2)*30].r=0;
}

void endGame(){
  clearAll();
  showStrip();
  color=0;
  newLine=0;
  for(int letter =0; letter<12;letter++){
    if(color==0){
        color=1;
      }else{
        color=0;
      }
    if(phrase[letter][0]>B11111){
      newLine=newLine+150;
      continue;
    }
    p= (letter*5)+newLine;
    for(int i =0; i<5;i++){
      row=30*i+p+newLine;
      for(int b =0; b<5;b++){
        pixel=row+b;
        if(!((phrase[letter][i]>>(4-b))&B00001)){
          if(color==0){
            setPixel(pixel,100,100,100);
          }else{
            setPixel(pixel,0,0,200);
          }
        }
      }
    }  
  }
  showStrip();
  while(!(digitalRead(p1) || digitalRead(p2))){
    border();
    showStrip();
    delay(1000);
    clearBorder();
    showStrip();
    delay(1000);
  }
  ballTime=0;
  paddleTime=0;
  
  ballSpeed=INITBALLSPEED;
  paddleSpeed=INITPADDLESPEED;
  setAll(0,0,0);
  paddleOne.x=1;
  paddleOne.y=0;
  paddleTwo.x=28;
  paddleTwo.y=0;
  ball.x=15;
  ball.y=6;
  placeBall(ball);
  placePaddle(paddleOne);
  placePaddle(paddleTwo);
  border();
  showStrip();
  paddleTwo.direct=0;
  paddleOne.direct=0;
  ball.vectorY=-1;
  ball.vectorX=1;
  
}
