#include <Adafruit_NeoPixel.h>

#define LED_PIN 6 
#define LED_COUNT 59
byte channel =A0; //Green Wire
byte ctrlReset=9; //Orange Wire
byte ctrlStrobe=8; //Yellow Wire
Adafruit_NeoPixel strip(LED_COUNT,LED_PIN,NEO_GRB+NEO_KHZ800);
void setup() {
strip.begin();
  strip.show();
}

void loop() {
 for(int i=0; i<LED_COUNT;i++){
  strip.setPixelColor(i,high);
  strip.show();
 }
}
void sound(){
  findBand();
  setAll(Low,Mid,High);
  for(int i=0;i<NUM_LEDS;i++){
    leds[i].fadeLightBy(64);
  }
  showStrip();
}

void findBand(){
  readMSG();
  Low=max(spectrum[0],spectrum[1]);
  Low=max(spectrum[2],Low);
  Mid=max(spectrum[3],spectrum[4]);
  High=max(spectrum[5],spectrum[6]);
}

void readMSG(){
  digitalWrite(ctrlReset, HIGH);                     // Pulse the reset signal
  digitalWrite(ctrlReset, LOW);                      // Causes MSGEQ7s to latch spectrum values
  delayMicroseconds(75);                             // Delay to meet minimum reset-to-strobe time

  for(int i=0; i <7; i++)                            // Cycle through the 7 spectrum bands
  {
    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(40);                           // Wait for outputs to settle
    spectrum[i] = analogRead(channel)/4;   // Store current values from left & right channels 
    
    if(spectrum[i] < 30 && i!=0 && i!=1 ) spectrum[i] = 0;   // Filter out the noise at the bottom if there
    Serial.print("Looking into "+String(i) +" : "+ String(spectrum[i])+ "\n" );
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(30);                           // Delay to meet minimum strobe-to-strobe time
  }
}
