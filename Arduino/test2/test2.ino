#include <Servo.h>

Servo myservo1;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);
  myservo1.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  float a = myservo1.read();                  // sets the servo position according to the scaled value
  Serial.println(a);
  delay(1000);                           // waits for the servo to get there
}

