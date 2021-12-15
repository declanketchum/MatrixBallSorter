#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

#define MAX 7 //number of balls in queue
#define SENSE_SAMPLE 5 //take 5 color samples and average to find color



/* ada frui sensor instructions: 
   Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);


Servo sortServo;
Servo ElevatorServo;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

int queue[MAX] = {1, 1, 1, 1, 1, 1, 1}; 
int itemCount = 6;
int front = 0;
int rear = 5;

bool moveServo = false;
int nutrualPos = 104; 
int blackPos = 73; 
int whitePos = 138; 

//int ballTestArr[15] = {1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0};
 
uint16_t r, g, b, c, colorTemp, lux; //initize sensor variables
int threshHold = 2500; 
int senseArr[SENSE_SAMPLE] = {0, 0, 0, 0, 0};
int senseVal;
int senseColor;
int aveB;
int colorB; 
int droppingColor;

int elevatorSpeed = 50;


void setup() {
  Serial.begin(115200);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  sortServo.attach(3); //attach to digital pin ~3
  ElevatorServo.attach(5); //attach to digital pin ~3

  sortServo.write(nutrualPos);
  //delay(200);
}


void loop() {
  Serial.println("running");

  ElevatorServo.write(elevatorSpeed); 

//  colorTemp = tcs.calculateColorTemperature(r, g, b);
//  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c); //in kelvin
//  lux = tcs.calculateLux(r, g, b); //lumens per square meter
  
    for(int i =0; i < SENSE_SAMPLE; i++) {
      delay(100);
      tcs.getRawData(&r, &g, &b, &c); //get data from sensor r=red, g=green, b=blue, c=clear
      senseVal = c;
      Serial.print("senseVal: ");
      Serial.print(senseVal);
      if(senseVal >= threshHold) { //higher c val means more light refelcted means ball color is white
        senseColor = 0; //set color to white
      }else {
        senseColor = 5; //set color to black
      }
      
//      Serial.print("     sensecolor: ");
//      Serial.println(senseColor);
      senseArr[i] = senseColor;
    }

    
    aveB = average(senseArr, SENSE_SAMPLE);
    Serial.print("average: ");
    Serial.println(aveB);
    if(aveB >= 3) {
      colorB = 1 ; //black
       Serial.print("   ball color black: ");
       Serial.println(colorB);
    }else {
      colorB = 0; //white
      Serial.print("   ball color white: ");
      Serial.println(colorB);
    }
   enqueue();
   moveServo = true;

   Serial.print("front: ");
   Serial.print(queue[front]);
   Serial.print("   back: ");
   Serial.print(rear);
   Serial.println(queue[rear]);
   //delay(3000);
   

  if(moveServo) {
      droppingColor = dequeue();
//      sortServo.write(nutrualPos);
//      delay(200);
//      Serial.print("move nutrual:");
//      Serial.print(nutrualPos);
      if(droppingColor >= 1) {
      sortServo.write(blackPos);
//      Serial.print("   move black :");
//      Serial.print(blackPos);
      delay(200);
      }else {
      sortServo.write(whitePos);
//      Serial.print("  move white :");
//      Serial.println(whitePos);
      delay(200);}
  //    sortServo.write(nutrualPos);
  //    delay(1000);
  //    Serial.print("move nutrual:");
  //    Serial.print(nutrualPos);
     sortServo.write(nutrualPos);
     delay(200);
      moveServo = false;
  }else {
  
  }
  
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

int look() {
   return queue[front];
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

void enqueue() {
   if(!isFull()) {
      if(rear == MAX-1) {
         rear = -1;            
      }
      rear++;       
      queue[rear] = colorB;
      itemCount++;
   }
}

int dequeue() {
   int droppingB = queue[front];
   front++;
   if(front == MAX) {
      front = 0;
   }
   itemCount--;
   return droppingB;  
}
