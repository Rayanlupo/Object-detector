#include <ESP32Servo.h>

Servo servo1;
int ServoPin = 34;
int TrigPin = 33;
int EchoPin = 32;
int ButtonPin = 26;
int BuzzerPin = 14;
int angle = 0;
void setup() {
  servo1.attach(ServoPin);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ButtonPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // Start servo operation when the button is pressed
  if (digitalRead(ButtonPin) == HIGH) {
    while (true) {  
      angle = angle + 5;
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
        tone(BuzzerPin, 262, 250); // Sound the buzzer
        servo1.write(angle); // Stop servo (neutral position for continuous servo)
      } else {
        servo1.write(angle); // Continue rotating servo (speed depends on servo type)
      }
      
      delay(15); // Small delay for stability
    }
  }
}
