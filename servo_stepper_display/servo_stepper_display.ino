#include <Servo.h>
#include <SpeedyStepper.h>


// CNC shield pinout
const int MOTOR_X_STEP_PIN = 2;
const int MOTOR_Y_STEP_PIN = 3;
const int MOTOR_X_DIR_PIN = 5;
const int MOTOR_Y_DIR_PIN = 6;
const int STEPPERS_ENABLE_PIN = 8;
const int LIMIT_SWITCH_X_PIN = 9;
const int LIMIT_SWITCH_Y_PIN = 10;


// Params
const int LEFT_SERVO_ANGLE = 80;
const int RIGHT_SERVO_ANGLE = 100;
const int CENTER_SERVO_ANGLE = 90;







Servo chooser;

SpeedyStepper carousel;


void setup() {

  // connect servos
  chooser.attach(LIMIT_SWITCH_X_PIN);

  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);


  carousel.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);

  carousel.setSpeedInStepsPerSecond(900);
  carousel.setAccelerationInStepsPerSecondPerSecond(600);


  // enable the stepper motors
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);
  
}



void loop() {

  // setup the motor so that it will rotate 2000 steps
  carousel.setupRelativeMoveInSteps(1600);
  
  
  while(!carousel.motionComplete())
  {
    carousel.processMovement();       // this call moves the motor
    
    if (false) {
      ;  // do something while stepper moving
    }
  }

  delay(1000);
}
