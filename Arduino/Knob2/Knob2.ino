#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  float sensorValue0 = analogRead(A0);
  float sensorValue = 5 * sensorValue0 / 1023;
  float ang = 180* sensorValue0 / 1023;
  myservo.write(ang);                  // sets the servo position according to the scaled value
  Serial.print("At Value= ");
  Serial.print(sensorValue0);
  Serial.print(",    The Voltage is= ");
  Serial.print(sensorValue);
  Serial.print("V");
  Serial.print("  and Angle is= ");
  Serial.print(myservo.read());
  Serial.println(" Degrees");
  delay(1000);                           // waits for the servo to get there
}

