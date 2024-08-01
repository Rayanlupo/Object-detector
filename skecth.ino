#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Servo servo1;
int ServoPin = 18;
int TrigPin = 33;
int EchoPin = 32;
int ButtonPin = 26;
int BuzzerPin = 14;
Adafruit_SSD1306 display(128,64, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(18,15);
  
  servo1.attach(ServoPin);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // Start servo operation when the button is pressed
  if (digitalRead(ButtonPin) == HIGH) {

    while (true) {  // Keep running the loop
      // Measure distance using the ultrasonic sensorù
      noTone(BuzzerPin);
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);

      long duration = pulseIn(EchoPin, HIGH);
      int distance = (duration * 0.034 / 2);

      
      if (distance <= 40) {
        display.println("OBJECT DETECTED");
         display.display();
        Serial.print("Object Detected\n");
        tone(BuzzerPin, 262, 250);
        servo1.write(180);
        delay(1000) ;
      } else {
        servo1.write(0); 
        }

      delay(15); 
      
    }
  }
}
