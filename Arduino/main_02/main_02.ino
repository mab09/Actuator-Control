#include <Servo.h>
#include <Time.h>
#include <TimeLib.h>

#define TIME_MSG_LEN 11 // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER 'T' // Header tag for serial time sync message
#define TIME_REQUEST 7 // ASCII bell character requests a time sync message 
Servo myservo;  // create servo object to control a servo
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.writeMicroseconds(1500); // send "stop" signal to ESC.
  delay(1000); // delay to allow the ESC to recognize the stopped signal
}
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  float sensorValue0 = analogRead(A0);
  float sensorValue = 5 * sensorValue0 / 1023;
  float signal = map(sensorValue0, 0, 1023, 1410, 1590);
  myservo.writeMicroseconds(signal); // Send signal to ESC.
  Serial.print("At Value= ");
  Serial.print(sensorValue0);
  Serial.print(",    The Voltage is= ");
  Serial.print(sensorValue);
  Serial.print("V");
  Serial.print("  and thruster at= ");
  Serial.print(signal);
  Serial.println(" MicroSeconds");
  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus() == timeNotSet)
    Serial.println("waiting for time sync");
  else
    digitalClockDisplay();
  delay(2000);
  // delay in between reads for stability
}
void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print("Time: ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print("  Date: ");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(year());
  Serial.println();
  Serial.println();
}
void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
void processSyncMessage() {
  // if time sync available from serial port, update time and return true
  while (Serial.available() >= TIME_MSG_LEN ) { // time message consists of header & 10 ASCII digits
    char c = Serial.read() ;
    Serial.print(c);
    if ( c == TIME_HEADER ) {
      time_t pctime = 0;
      for (int i = 0; i < TIME_MSG_LEN - 1; i++) {
        c = Serial.read();
        if ( c >= '0' && c <= '9') {
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number
        }
      }
      setTime(pctime); // Sync Arduino clock to the time received on the serial port
    }
  }
}
