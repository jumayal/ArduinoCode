
int clearPin = 13;  //SRCLR Pin 10 (-) clears
int clockPin=12;    //SRCLK Pin 11 Up trigered 
int latchPin = 11;  //RCLK Pin 12 Up Trigered
int dataPin =10;    //SER Pin 14
int rowA =7;  
int rowB=6;
int rowC=5;
int rowD=4;
int rowE=3;
int side=0;
int wait =1;
int initial_PORTD=B00001000;
void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clearPin, OUTPUT);
  pinMode(rowA, OUTPUT);
  pinMode(rowB, OUTPUT);
  pinMode(rowC, OUTPUT);
  pinMode(rowD,OUTPUT);
  pinMode(rowE,OUTPUT);
  digitalWrite(latchPin,LOW);
  digitalWrite(clearPin,LOW);
  digitalWrite(clearPin,HIGH);
  digitalWrite(rowA,HIGH);
  digitalWrite(rowB,HIGH);
  digitalWrite(rowC,HIGH);
  digitalWrite(rowD,HIGH);
  digitalWrite(rowE,LOW);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);

}

void loop() {

    icOn();
    PORTD=B11110000;
    showLights();
    delay(wait);
    shift(B10000,1);
    PORTD=B11101000;
    showLights();
   delay(wait);
    shift(B10000,1);
    PORTD=B11011000;
    showLights(); 
   delay(wait);
    shift(B10000,1);
    PORTD=B10111000;
    showLights();
   delay(wait); 
    shift(B10000,1);
    PORTD=B01111000;
    showLights();
    delay(wait);
    shift(B10000,1);
    PORTD=B11110000;
    showLights();
    
}



void shift(byte myDataOut, int range) {
  //This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  PORTB =B100000;
  //clear everything out just in case to
  //prepare shift register for bit shifting

  //for each bit in the byte myDataOut�
  //Reads from left to right 
  for (i=0; i<range; i++) {
    if ( myDataOut & (16>>i) ) {
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
  PORTB&=B110111;
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

void rowShift(){
  for(int i=0;i<4;i++){
    icOn();
    showLights();
    delay(wait);
    icOff();
    showLights();
  }
}

void icShiftOn(){
  icOn();
  showLights();
  delay(wait);

  for(int i=0;i<7;i++){
    icOff();
    showLights();
    delay(wait);
  }
}

void icShiftOff(){
  icOff();
  showLights();
  delay(wait);

  for(int i=0;i<7;i++){
    icOn();
    showLights();
    delay(wait);
  }
}

void chasingLED(){
  shift(B00000,5);
  for(int i=0;i<43;i++){
    shift(B11111,1);
    delay(50);
    showLights();
  }
}

void blank(){
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
}

