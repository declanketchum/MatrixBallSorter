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


// Parameters

// Chooser servo is tuned
const int CENTER_SERVO_ANGLE = 114;
const int LEFT_SERVO_ANGLE = CENTER_SERVO_ANGLE - 25;
const int RIGHT_SERVO_ANGLE = CENTER_SERVO_ANGLE + 25;
const int CHOOSER_SIDE_DELAY = 400;
const int CHOOSER_CENTER_DELAY = 400;

// Stepper parameters
const int STEPPER_SPEED = 300;
const int STEPPER_ACCEL = 500;
const int STEPPER_STEPS_PER_COLUMN = 114;  // To be worked on...


int currColumn = 0;

//bool Matrix[][20] = {{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//                     {0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//                     {1,0,1,0,1,0,1,1,1,0,0,1,1,1,0,1,1,1,1,0},
//                     {0,1,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0},
//                     {1,0,0,1,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0},
//                     {0,1,0,1,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0},
//                     {1,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0},
//                     {0,1,1,0,1,0,1,1,1,0,0,0,1,0,0,1,0,0,0,0},
//                     {1,0,0,1,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0},
//                     {0,1,0,1,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0},
//                     {1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0},
//                     {0,1,1,0,1,0,1,0,0,0,0,1,1,1,0,1,1,1,1,0},
//                     {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//                     {0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

String MatrixString;
int MatCols; //25ish 
int MatRows; //35
int Area;



Servo chooser;
SpeedyStepper carousel;



void setup() {

  Serial.begin(115200);

  carousel.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);

  carousel.setSpeedInStepsPerSecond(STEPPER_SPEED);
  carousel.setAccelerationInStepsPerSecondPerSecond(STEPPER_ACCEL);


  // enable the stepper motors
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);

  // connect servos
  chooser.attach(LIMIT_SWITCH_X_PIN);
  // center the chooser servo
  chooser.write(CENTER_SERVO_ANGLE);

}



void loop() {

  // Completes one full horizontal row at a time
  // (Traverses all columns, then does next row)
  if(Serial.available() > 0) {

    MatrixString = Serial.readStringUntil('\n');
    MatRows = Serial.readStringUntil('\n').toInt();
    MatCols = Serial.readStringUntil('\n').toInt();
    Area = MatRows*MatCols; 
    
    int curCol = -1;
    for(int i = 0; i < Area; i++) {
      char ballColor = MatrixString.charAt(i);
      if(i % MatRows == 0) {
        curCol++;
      }
      
      ballCycle(curCol, ballColor);
      
    }
    
//    for (int x = 0; x < MatCols; x++) {
//      
//      for (int y = MatRows-1; y >= 0; y--) {
//    
//          bool ballInSpot = Matrix[y][x];
//          
//          ballCycle(x, ballInSpot);
//  
//          char message[40];
//          sprintf(message, "Column %d -- Row %d -- Ball %d", x, y, ballInSpot);
//          Serial.println(message);
//        }
//      }
  
    Serial.println("MATRIX COMPLETE!! Stopping...");
    delay(10000000);
  }
}



void ballCycle(int column, char ball) {
  /* Routine to drop a single ball of the right type
     into a certain column
  */

  // Drive stepper if necessary
  if (currColumn != column) {
    
    // drive stepper motor to appropriate column
    // this is a blocking function call
    carousel.moveToPositionInSteps(column * STEPPER_STEPS_PER_COLUMN);

    currColumn = column;
    delay(100);
  }

  // Drive servo to get appropriate ball
  if (ball == '0') {
    chooser.write(LEFT_SERVO_ANGLE);
  } else {
    chooser.write(RIGHT_SERVO_ANGLE);  
  }
  delay(CHOOSER_SIDE_DELAY);

  // Drive servo back to center to drop it
  chooser.write(CENTER_SERVO_ANGLE);
  delay(CHOOSER_CENTER_DELAY);
  
}
