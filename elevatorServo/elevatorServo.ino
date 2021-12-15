#include <Servo.h>

Servo ElevatorServo;


void setup() {
  // put your setup code here, to run once:
  ElevatorServo.attach(3);

}
int sp = 160;

void loop() {
  // put your main code here, to run repeatedly:
  ElevatorServo.write(sp); 
  //delay(100); 

}
