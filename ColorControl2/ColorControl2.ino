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
//bool sensingB = true;
bool moveServo = false; 

void loop() {
  uint16_t r, g, b, c, colorTemp, lux; //initize sensor variables
  int senseSample = 5; //take 5 color samples and average to find color
  int senseArr[senseSample] = {0, 0, 0, 0, 0};
  Serial.println("running");

  //
//  colorTemp = tcs.calculateColorTemperature(r, g, b);
//  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c); //in kelvin
//  lux = tcs.calculateLux(r, g, b); //lumens per square meter

  int senseVal;
  int senseColor;
  int threshHold = 3000; 
  int colorB; 
  int aveB;
//  delay(1000);
//    Serial.print("sensing b? beginng: ");
//    Serial.println(sensingB);
  
  //if(sensingB) {
//    Serial.print("sensing b? during sense: ");
//    Serial.println(sensingB);
    for(int i =0; i < senseSample; i++) {
      tcs.getRawData(&r, &g, &b, &c); //get data from sensor r=red, g=green, b=blue, c=clear
      senseVal = c;
      Serial.print("senseVal: ");
      Serial.print(senseVal);
      if(senseVal >= threshHold) { //higher c val means more light refelcted means ball color is white
        senseColor = 0; //set color to white
      }else {
        senseColor = 5; //set color to black
      }
      
      Serial.print("     sensecolor: ");
      Serial.println(senseColor);
      senseArr[i] = senseColor;
    }

    
    aveB = average(senseArr, senseSample);
    Serial.print("average: ");
    Serial.print(aveB);
    if(aveB >= 3) {
      colorB = 1 ; //black
       Serial.print("   ball color black: ");
       Serial.print(colorB);
    }else {
      colorB = 0; //white
      Serial.print("   ball color white: ");
      Serial.println(colorB);
    }
    moveServo = true;

if(moveServo) {
    sortServo.write(nutrualPos);
    delay(1000);
    Serial.print("move nutrual:");
    Serial.print(nutrualPos);
    if(colorB >= 1) {
    sortServo.write(blackPos);
    Serial.print("   move black :");
    Serial.print(blackPos);
    delay(1000);
    }else {
    sortServo.write(whitePos);
    Serial.print("  move white :");
    Serial.println(whitePos);
    delay(1000);}
//    sortServo.write(nutrualPos);
//    delay(1000);
//    Serial.print("move nutrual:");
//    Serial.print(nutrualPos);
    moveServo = false;
}else {
  
}
    
      
////      sensingB = false;
////      Serial.print("sensing b? after sense: ");
////      Serial.println(sensingB);
//  //} else {
////      Serial.print("sensing b? before drop: ");
////      Serial.println(sensingB);
//    //drop ball in front
//      delay(1000);
//      droppingB = dequeue(queue);
//      Serial.print("   dropping ball color: ");
//      Serial.print(droppingB);
//      //move servo
//      if(droppingB >= 1) {
//        sortServo.write(blackPos);
//        delay(1000);
//        Serial.print("   move Black: ");
//        Serial.print(blackPos);
//      }if(droppingB <= 1) {
//        sortServo.write(whitePos);
//        delay(1000);
//        Serial.print("   move White: ");
//        Serial.print(whitePos);
//      }
//      sortServo.write(nutrualPos);
//      delay(1000);
//      Serial.print("   move Nutral: ");
//      Serial.println(nutrualPos);
  
      //enqueue(queue, colorB);
  //    Serial.print("sensed color: ");
  //    Serial.println(colorB);
  //    Serial.print("ball entering: ");
  //    Serial.println(queue[rear]);
  
      //sensingB = true;
      //Serial.print("sensing b? end: ");
      //Serial.println(sensingB);
  //}


//    
//    Serial.print("nutral: "); 
//    Serial.print(nutrualPos);
//    sortServo.write(nutrualPos);
//    delay(3000);
//    Serial.print("  blcak: "); 
//    Serial.print(blackPos);
//    sortServo.write(blackPos);
//    delay(3000);
//    Serial.print("nutral: "); 
//    Serial.print(nutrualPos);
//    sortServo.write(nutrualPos);
//    delay(3000);
//    Serial.print("  white: "); 
//    Serial.println(whitePos);
//    sortServo.write(whitePos);
//    delay(3000);
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
