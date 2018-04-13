#define clearPin 13  //SRCLR Pin 10 (-) clears
#define clockPin 12    //SRCLK Pin 11 Up trigered 
#define latchPin 11  //RCLK Pin 12 Up Trigered
#define dataPin 10    //SER Pin 14
#define rowA  7 
#define rowB 6
#define rowC 5
#define rowD 4
#define rowE 3
#define initial_PORTD B00001
int startIndex; //When the next letter should start showing
int endIndex; // when the whole letter is showing
int outIndex;// when the letter is out of matrix
byte holder;
int alphabet=15; //number of letters using
int push=alphabet*5; //when all letters are seen 
int go; //how much to shift the displayed message
byte dark; // How much darkness to put infront of message

#define A {B11011,B10101,B00000,B01110,B01110}
#define B {B00001,B01110,B01001,B01110,B00001}
#define C {B11000,B10111,B01111,B10111,B11000}
#define D {B00011,B01101,B01101,B01101,B00011}
#define E {B00001,B01111,B00011,B01111,B00001}
#define up_F {B00000,B01111,B00011,B01111,B01111}
#define G {B11011,B10101,B01100,B10101,B10001}
#define H {B01110,B01110,B00000,B01110,B01110}
#define I {B00000,B11011,B11011,B11011,B00000}
#define J {B00000,B11011,B11011,B01011,B10111}
#define K {B01101,B01011,B00111,B01011,B01101}
#define L {B01111,B01111,B01111,B01111,B00000}
#define M {B10101,B01010,B01110,B01110,B01110}
#define N {B01110,B00110,B01010,B01100,B01110}
#define O {B10001,B01110,B01110,B01110,B10001}
#define P {B00011,B01101,B00011,B01111,B01111}
#define Q {B10011,B01101,B01001,B01001,B10010}
#define R {B00001,B01110,B00001,B01101,B01110}
#define S {B10011,B01111,B10011,B11101,B10011}
#define T {B00000,B11011,B11011,B11011,B11011}
#define U {B01110,B01110,B01110,B01110,B10001}
#define V {B01110,B01110,B01110,B10101,B11011}
#define W {B01110,B01110,B01110,B01010,B10101}
#define X {B01110,B10101,B11011,B10101,B01110}
#define Y {B01110,B10101,B11011,B11011,B11011}
#define Z {B00000,B11101,B11011,B10111,B00000}
#define blank {B11111,B11111,B11111,B11111,B11111}
#define smile {B10101,B10101,B11111,B01110,B10001}

byte phrase[][5]={I,blank,W,A,N,T,blank,T,O,blank,P,A,R,T,Y};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clearPin, OUTPUT);
  pinMode(rowA, OUTPUT);
  pinMode(rowB, OUTPUT);
  pinMode(rowC, OUTPUT);
  pinMode(rowD,OUTPUT);
  pinMode(rowE,OUTPUT);
  reset();
  allOff(10);
  showLights();
  digitalWrite(latchPin,LOW);
  digitalWrite(rowA,HIGH);
  digitalWrite(rowB,HIGH);
  digitalWrite(rowC,HIGH);
  digitalWrite(rowD,HIGH);
  digitalWrite(rowE,LOW);

}

void loop() {
  dark=10;
  int matrixLength = 122; //alpha*13
  for(int first=0;first<5;first++){
    for(long j=0;j<200;j++){
      for(int fRow=0;fRow<5;fRow++){
        allOff(10);
        shift(phrase[0][fRow],first);
        nextRow(fRow);
        showLights();
        reset();
      }
    }
  }
  for(int i=5;i<matrixLength;i++){ 
    if(i%5 ==0){
        dark=dark-1;
    }  
    for(long h=0;h<200;h++){
      for(int row=0;row<5;row++){
        if(i<54){
        allOff(dark);
        shift(phrase[0][row],5);
        shift(B11111,1);
        }
        for(int letter=1;letter<alphabet;letter++){
          
          startIndex=letter*5;
          endIndex=startIndex+5;
          outIndex=startIndex+53;
          
          if((startIndex<i)&&(i<endIndex)){
            shift(phrase[letter][row],(i-startIndex));
            shift(B11111,1);
          }else if((endIndex<=i)&&(i<=outIndex)){
            shift(phrase[letter][row],5);
            shift(B11111,1);
          }else if(i>outIndex){
            continue;
          }else{
            break;
          }
        }
        if(i> push){
          go=i-push;
          for(int m=0;m<go;m++){
            shift(B11111,1);
          }
        }
        nextRow(row);
        showLights();
        reset();
      }
    }
  }
}



void shift(byte myDataOut, int range) {
  //This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int l=0;
  PORTB =B100000;
  //prepare shift register for bit shifting

  //for each bit in the byte myDataOut�
  //Reads from left to right 
  for (l=0; l<range; l++) {
    if ( myDataOut & (16>>l) ) {
      PORTB=B100100;
    }
    //register shifts bits on upstroke of clock pin  
    PORTB|=B110000;
    //zero the data pin after shift to prevent bleed through
    PORTB =B100000;
  }
}

void showLights(){
  PORTB|=B001000;//Shows Lights
}

void reset(){
  PORTB=B000000;
  PORTB=B100000; 
}

void icOff(){
  shift(B11111,5);
}

void icOn(){
  shift(B00000,5);
}

void allOff( byte times){
  for( byte me=0;me<times;me++){
  shift(B11111,5);
  }
}

void nextRow(int axis){
  holder=initial_PORTD << axis; 
  holder = ~holder;
  holder= holder << 3;
  PORTD =holder;
}

