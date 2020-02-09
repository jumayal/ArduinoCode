void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);

}

int value;
void loop() {
  // put your main code here, to run repeatedly:
  value=analogRead(A0);
  Serial.println(value);
  
}
