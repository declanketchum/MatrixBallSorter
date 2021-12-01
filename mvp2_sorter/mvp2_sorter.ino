
#include <Servo.h>
Servo sortServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  sortServo.attach(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n');
    Serial.println(received);
    if (received == "0") {
      ballCycle(0);
    } else if (received == "1") {
      ballCycle(1);
    }
  }

}



void setSort(int state) {
  // Drive servo to angle corresponding to a sorter state
  float commands[] = {115.0, 135.0, 95.0};
  sortServo.write( commands[state] );
}



void ballCycle(bool ball) {
  /* Routine to drop a single ball of the right type
     into a certain column
  */
  
  // Set servo to state to grab ball
  setSort( ball + 1 );
  delay(400);
  
  // Bring servo back to neutral to drop ball
  setSort( 0 );
  delay(5);
  
  }
