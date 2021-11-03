/*
  Skeleton framework for ball matrix display Arduino code
  Author: Luke Raus
  Last revised: 2 Nov 2021
*/

#include <Servo.h>
Servo sortServo;
Servo columnServo;

int currColumn;

bool Matrix[][4] = { {1,1,1,1},
                     {0,1,1,1},
                     {0,0,1,1},
                     {1,0,0,1} };
int MatCols = 4;
int MatRows = 4;

void setup() {
  // initialize serial communications
  Serial.begin(115200);
  
  sortServo.attach(3);
  columnServo.attach(9);
}


void loop() {

  for (int y = MatRows-1; y >= 0; y--) {

    delay(200);

    for (int x = 0; x < MatCols; x++) {

      bool ballInSpot = Matrix[y][x];
      
      ballCycle(x, ballInSpot);
      Serial.println( "Column: " + String(x) + ", Row: " + String(y) + " Ball: " + String(ballInSpot) );
    }
  }

  delay(10000000);
}



void setSort(int state) {
  // Drive servo to angle corresponding to a sorter state
  float commands[] = {60.0, 10.0, 110.0};
  sortServo.write(commands[state]);
}


void setColumn(int column) {
  // Send command to stepper motor
  columnServo.write( column * 30.0 );
}


void ballCycle(int column, bool ball) {
  /* Routine to drop a single ball of the right type
     into a certain column
  */
    
  if (currColumn != column) {
   // set stepper motor X position
   setColumn( column );
   currColumn = column;
   delay(500);
  }
  
  // Set servo to state to grab ball
  setSort( ball + 1 );
  delay(500);
  
  // Bring servo back to neutral to drop ball
  setSort( 0 );
  delay(500);
  
  }
