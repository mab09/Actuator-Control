// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
   Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // send an intro:
  Serial.println("send 1 to switch ON and 0 to switch OFF");
  Serial.println();
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) {
    int thisChar = Serial.read();
    if (thisChar == '1'){
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
    else if (thisChar == '0'){
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    }
    else{
      for (int i=0; i<10; i++){
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      delay(50);
      }
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
    }
  }
}
