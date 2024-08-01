#include <ESP32Servo.h>
 Servo servo1;


int ServoPin = 34;
int TrigPin = 33;
int EchoPin = 32;
int ButtonPin = 26;



void setup() {
  servo1.attach(ServoPin);
  pinMode(26, INPUT);
  pinMode(34, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(32, INPUT);
  pinMode(14, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (digitalRead(26) = HIGH){

  
  while (bool object = false){

  int angle = -90;
  servo1.write(angle);
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  long duration = pulseIn(EchoPin,HIGH);
  int distance = ((duration * 0.034) / 2);
  if (distance <= 40){object = true;
tone(14, 262, 250);    
  }
  angle++;
  }
  }
}
