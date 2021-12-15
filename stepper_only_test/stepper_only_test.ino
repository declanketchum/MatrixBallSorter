#include <SpeedyStepper.h>


// CNC shield pinout
const int MOTOR_X_STEP_PIN = 2;
const int MOTOR_Y_STEP_PIN = 3;
const int MOTOR_X_DIR_PIN = 5;
const int MOTOR_Y_DIR_PIN = 6;
const int STEPPERS_ENABLE_PIN = 8;
const int LIMIT_SWITCH_X_PIN = 9;
const int LIMIT_SWITCH_Y_PIN = 10;


// Stepper parameters
const int STEPPER_SPEED = 300;
const int STEPPER_ACCEL = 400;
const int STEPPER_STEPS_PER_RUN = 140;  // To be worked on...

SpeedyStepper carousel;



void setup() {

  Serial.begin(115200);

  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);


  carousel.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);

  carousel.setSpeedInStepsPerSecond(STEPPER_SPEED);
  carousel.setAccelerationInStepsPerSecondPerSecond(STEPPER_ACCEL);

  // enable the stepper motors
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);
 
}


void loop() {
  carousel.moveRelativeInSteps( STEPPER_STEPS_PER_RUN );
  delay(500);
}
