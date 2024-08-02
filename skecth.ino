#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Servo servo1;
int ServoPin = 18;
int TrigPin = 33;
int EchoPin = 32;
int ButtonPin = 26;
int BuzzerPin = 14;
int angle = 0;
int rotations = 0;
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
  pinMode(ButtonPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  if (digitalRead(ButtonPin) == HIGH) {
    rotations = 0;
    while (rotations < 2) {  

    
      noTone(BuzzerPin);
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);

      long duration = pulseIn(EchoPin, HIGH);
      int distance = (duration * 0.034 / 2);

      while (distance <= 40) {
        display.println("OBJECT DETECTED");
        display.display();
        Serial.print("Object Detected\n");
        tone(BuzzerPin, 262, 250);
        servo1.write(angle);  
        objectDetected = true;
      }  
        if (objectDetected) {
          objectDetected = false;
          display.clearDisplay();
          display.setCursor(18, 15);
          display.display();
        }
        servo1.write(angle);
        angle += 20;
        if (angle >= 180) {
          angle = 0;
          rotations++;
        }
      

      delay(1000);
    }
    servo1.write(90);
    servo1.detach();
  }
}


      delay(15); 
      
    }
  }
}
