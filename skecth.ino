#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Servo servo1;
int ServoPin = 18;
int TrigPin = 33;
int EchoPin = 32;
int JoystickPin = 12;
int BuzzerPin = 14;
int angle;
int distance;
int xValue;
bool objectDetected = false;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(18, 15);

  servo1.attach(ServoPin);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  angle = 90;
 
  Serial.begin(115200);
}

void loop() {
 int xValue = analogRead(JoystickPin);
 checkDistance(); 
 if (distance < 40){
  object();
 }
 if (xValue < 2048){
  Serial.print("left");
  angle = angle - 5;
  servo1.write(angle);
  delay(100);
 }
 else if (xValue > 2048){

  Serial.print("right");
  angle = angle + 5;
  servo1.write(angle);
  delay(100);
 }
 }
 


   
void checkDistance(){
digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);

     int duration = pulseIn(EchoPin, HIGH);
      distance = (duration * 0.034 / 2);
      Serial.print(distance);
      delay(1000);
     
}
void object(){
  display.clearDisplay();
  display.println(distance);
        display.display();
        Serial.print(distance);
        tone(BuzzerPin, 262, 250);
        delay(100);
  if (xValue < 2048){
  Serial.print("left");
  angle = angle - 5;
  servo1.write(angle);
  delay(1000);
 }
 else if (xValue > 2048){

  Serial.print("right");
  angle = angle + 5;
  servo1.write(angle);
 }
 }
 

void clearDisplay() {
  display.clearDisplay();
  display.display();
  Serial.print("Object Removed\n");
  noTone(BuzzerPin);
}
