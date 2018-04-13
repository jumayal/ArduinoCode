int clearPin = 13;  //SRCLR Pin 10 (-) clears
int clockPin=12;    //SRCLK Pin 11 Up trigered
int latchPin = 11;  //RCLK Pin 12 Up Trigered
int dataPin =10;    //SER Pin 14
int rowA =7;  
int rowB=6;
int rowC=5;
int rowD=4;
int rowE=3;
int wiat = 500;
byte flow =B10000000;
byte led=0;
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
  digitalWrite(latchPin,LOW);
  digitalWrite(clearPin,LOW);
  digitalWrite(clearPin,HIGH);
  digitalWrite(rowA,HIGH);
  digitalWrite(rowB,HIGH);
  digitalWrite(rowC,HIGH);
  digitalWrite(rowD,HIGH);
  digitalWrite(rowE,LOW);
}
void loop() {

  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);

  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  delay(wiat);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  digitalWrite(rowE,HIGH);
  digitalWrite(rowD,LOW);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowE,HIGH);
  digitalWrite(rowD,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowD,HIGH);
  digitalWrite(rowC,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);

   shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowC,HIGH);
  digitalWrite(rowB,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);

   shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowB,HIGH);
  digitalWrite(rowA,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);

   shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowA,HIGH);
  digitalWrite(rowE,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);

   shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowE,HIGH);
  digitalWrite(rowD,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  digitalWrite(rowA,HIGH);
  digitalWrite(rowB,LOW);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  digitalWrite(rowB,HIGH);
  digitalWrite(rowC,LOW);

  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  digitalWrite(rowC,HIGH);
  digitalWrite(rowD,LOW);

  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  digitalWrite(rowD,HIGH);
  digitalWrite(rowE,LOW);

  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  delay(wiat);

  shiftOut(dataPin,clockPin,MSBFIRST,B11111111);
  delay(wiat);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  digitalWrite(rowE,HIGH);
  digitalWrite(rowD,LOW);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowE,HIGH);
  digitalWrite(rowD,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
  
  shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowD,HIGH);
  digitalWrite(rowC,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);

   shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowC,HIGH);
  digitalWrite(rowB,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);

   shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowB,HIGH);
  digitalWrite(rowA,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);

   shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowA,HIGH);
  digitalWrite(rowE,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);

   shiftOut(dataPin,clockPin,MSBFIRST,B00000000);
  delay(wiat);
  digitalWrite(rowE,HIGH);
  digitalWrite(rowD,LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin,LOW);
}
