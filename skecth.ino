#include <ESP32Servo.h>

Servo servo1;
int ServoPin = 34;
int TrigPin = 33;
int EchoPin = 32;
int ButtonPin = 26;
int BuzzerPin = 14;

void setup() {
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

      // Check if an object is detected within 40 cm
      if (distance <= 40) {
        Serial.print("Object Detected");
        tone(BuzzerPin, 262, 250); // Sound the buzzer
        servo1.write(180);
        delay(1000) ;
      } else {
        servo1.write(0); // Continue rotating servo (speed depends on servo type)
      }

      delay(15); // Small delay for stability
    }
  }
}
