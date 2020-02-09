byte channel =A0;
byte ctrlReset=9;
byte ctrlStrobe=8;
byte ledOne=2;
long spectrum[7];  
void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(ctrlReset,OUTPUT);
  pinMode(ctrlStrobe,OUTPUT);
  delay(10000);
}

void loop() {
  readMSG();

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
   if(spectrum[i] < 30) spectrum[i] = 0;   // Filter out the noise at the bottom if there
     Serial.print("Looking into "+String(i) +" : "+ String(spectrum[i])+ "\n" );
    digitalWrite(ctrlStrobe,HIGH)
    delayMicroseconds(30);                           // Delay to meet minimum strobe-to-strobe time
  }
}

