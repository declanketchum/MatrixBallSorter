#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>
Servo sortServo;
Servo dropServo;

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);


#define MAX 6

void setup() {
  Serial.begin(115200);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  sortServo.attach(3);

}


int queue[MAX] = {0, 0, 0, 0, 0, 0}; 
int itemCount = 5;
int front = 0;
int rear = -1;
int droppingB; 
int nutrualPos = 104; 
int blackPos = 138; 
int whitePos = 73; 
int ballTestArr[15] = {1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0};

void loop() {
  uint16_t r, g, b, c, colorTemp, lux; //initize sensor variables
  int senseSample = 5; //take 5 color samples and average to find color
  int senseArr[senseSample] = {0, 0, 0, 0, 0};

  //
  tcs.getRawData(&r, &g, &b, &c); //get data from sensor r=red, g=green, b=blue, c=clear
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c); //in kelvin
  lux = tcs.calculateLux(r, g, b); //lumens per square meter

  int senseVal = c;
  int senseColor;
  int threshHold = 3000; 
  int colorB; 
  int aveB;
  bool sensingB = true;
//  delay(1000);

  if(senseVal >= threshHold) {
    senseColor = 0; //set color to white
  }else {
    senseColor = 5; //set color to black
  }
  
  if(sensingB) {
    for(int i =0; i < senseSample; i++) {
      senseArr[i] = senseColor;
//      Serial.print(senseArr[i]); 
//      Serial.print(senseVal);
//      Serial.println(", ");
    }
    aveB = average(senseArr, senseSample);
//    Serial.print("average: ");
//    Serial.println(aveB);
    if(aveB >= 3) {
      colorB = 1 ;
    }else {
      colorB = 0; 
    }
    sensingB = false;
  }

//  //drop ball in front
//    delay(300);
//    droppingB = dequeue(queue);
//    Serial.print("dropping ball: ");
//    Serial.println(droppingB);
//    //move servo
//    if(droppingB == 1) {
//      sortServo.write(blackPos);
//      delay(300);
//      Serial.print("Black: ");
//      Serial.println(blackPos);
//    }if(droppingB==0) {
//      sortServo.write(whitePos);
//      delay(300);
//      Serial.print("White: ");
//      Serial.println(whitePos);
//    }
//    sortServo.write(nutrualPos);
//    delay(300);
//    Serial.print("Nutral: ");
//    Serial.println(nutrualPos);
//
//    enqueue(queue, colorB);
////    Serial.print("sensed color: ");
////    Serial.println(colorB);
////    Serial.print("ball entering: ");
////    Serial.println(queue[rear]);
//
//    sensingB = true;


    
    Serial.print("nutral: "); 
    Serial.print(nutrualPos);
    sortServo.write(nutrualPos);
    delay(3000);
    Serial.print("  blcak: "); 
    Serial.print(blackPos);
    sortServo.write(blackPos);
    delay(3000);
    Serial.print("nutral: "); 
    Serial.print(nutrualPos);
    sortServo.write(nutrualPos);
    delay(3000);
    Serial.print("  white: "); 
    Serial.println(whitePos);
    sortServo.write(whitePos);
    delay(3000);
    //make sure there is time for servo to drop ball AND return so that balls go down
  //add b5 to queue 
  //sense new b5 
  
//  Serial.println();
  
  //Serial.print(senseVal);
//  //print sensor data
//  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
//  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
//  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
//  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
//  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
//  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
//  Serial.println(" ");
}

int average(int arr[], int n) {
   int sum = 0;
   int ave = 0;
   for (int i = 0; i < n; i++)
    sum += arr[i];
   ave = sum/n;
   return ave;
}

int look(int arr[]) {
   return arr[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int siz() {
   return itemCount;
}  

void enqueue(int arr[], int data) {
   if(!isFull()) {
      if(rear == MAX-1) {
         rear = -1;            
      }       
      arr[++rear] = data;
      itemCount++;
   }
}

int dequeue(int arr[]) {
   int data = arr[front++];
   if(front == MAX) {
      front = 0;
   }
   itemCount--;
   return data;  
}
