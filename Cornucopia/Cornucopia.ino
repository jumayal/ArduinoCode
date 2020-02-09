void setup() {
  delay(3000);
  pinMode(9,INPUT);
  pinMode(8,INPUT);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
}
int pin = 4;
boolean value[6];
void loop() {
    for(int i=0; i<6;i++){
      value[i] = !(digitalRead(pin));
      pin++;
    }
    pin=4;
    Serial.print(value[0]);
    Serial.print(value[1]);
    Serial.print(value[2]);
    Serial.print(value[3]);
    Serial.print(value[4]);
    Serial.print(value[5]);
    Serial.println("");
//    if(((value[0] && value[1]) || !value[2]) && (value[3] && value[4] && value[5])){
//      digitalWrite(10, HIGH);
//    }else{
//      digitalWrite(10, LOW);
//    }
    if((value[0] && value[1] && value[2]) || ((value[3] && value[4]) || value[5])){
      digitalWrite(10, HIGH);
    }else{
      digitalWrite(10, LOW);
    }
//    if(((value[0] || value[1]) && (value[2] || value[3]) && (value[4] || value[5])){
//      digitalWrite(10, HIGH);
//    }else{
//      digitalWrite(10, LOW);
//    }
//    if(((value[0] && value[1]) || (value[2] && value[3]) || (value[4] && value[5])){
//      digitalWrite(10, HIGH);
//    }else{
//      digitalWrite(10, LOW);
//    }
//    if(value[0] && value[1} && !value[2] && value[3] && value[4] && value[5]){
//      digitalWrite(10, HIGH);
//    }else{
//      digitalWrite(10, LOW);
//    }
//     if(value[0] && (value[1] || value[2] || value[3] || value[4] || value[5])){
//      digitalWrite(10, HIGH);
//    }else{
//      digitalWrite(10, LOW);
//    }
}

