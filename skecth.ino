
#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Servo servo1;
int ServoPin = 18;
int TrigPin = 33;
int EchoPin = 32;
int JoystickPin = 12;
int BuzzerPin = 14;
int angle = 90;
int distance;
int yValue;
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
  pinMode(ResetPin, INPUT);
 
  Serial.begin(115200);
}

void loop() {
    

    int yValue = analogRead(JoystickPin);
    if (yValue < 2048) {
      Serial.println("left");
      angle = angle - 5;
      servo1.write(angle);
      checkDistance();
      if (distance < 40 && !objectDetected) {
        objectDetected = true;
        object();
      } 
      else if (distance >= 40 && objectDetected) {
        objectDetected = false;
        display.clearDisplay();
         clearDisplay();
      }
       yValue = analogRead(JoystickPin);
    }
    else if (yValue > 2048) {
      
      Serial.println("right");
      angle = angle + 5;
      servo1.write(angle);
      checkDistance();
      if (distance < 40 && !objectDetected) {
        objectDetected = true;
        object();
      } else if (distance >= 40 && objectDetected) {
        objectDetected = false;
        display.clearDisplay();
         clearDisplay();
      }
    yValue = analogRead(JoystickPin);
     
    }
    if (!objectDetected) {
      if (yValue < 2048) {
        angle = angle - 5;
        servo1.write(angle);
      } else if (yValue > 2048) {
        angle = angle + 5;
        servo1.write(angle);
      }
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
     
}
void object(){
display.println("OBJECT DETECTED");
        display.display();
        Serial.print("Object Detected\n");
        tone(BuzzerPin, 262, 250);
}
void clearDisplay() {
  display.clearDisplay();
  display.display();
  Serial.print("Object Removed\n");
  noTone(BuzzerPin);
  servo1.write(angle);
}
