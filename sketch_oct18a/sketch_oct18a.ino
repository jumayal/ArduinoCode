/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 
int trigPin = 12;    // Trigger
int echoPin = 11;    // Echo
int past=0;
long duration, cm, inches;
struct node{
  int data;
  node *next;
};

struct List{
  node *head;
  node *tail;
  int amount;
};


void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
    
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
}

void addEnd(List *track,int value)
    {
      node *temp=new node;
      temp->data=value;
      temp->next=NULL;
      if(track->head==NULL)
      {
        track->head=temp;
        track->tail=temp;      }
      else
      {  
        track->tail->next=temp;
      }
      track->amount=track->amount +1;
    }
void push(List *track, int value){
      node *temp=new node;
      temp->data=value;
      temp->next=NULL;
      if(track->head==NULL)
      {
        track->head=temp;
        track->tail=temp;
      }
      else
      {  
        temp->next=track->head;
        track->head=temp;
      }
      track->amount=track->amount +1;
}

void shifty(List *track, int value){
  push(track,value);
  
}
List* makeList(){
  List* thing=new List;
  thing->head=NULL;
  thing->tail=NULL;
  thing->amount=0;
  return thing;
 }
 

