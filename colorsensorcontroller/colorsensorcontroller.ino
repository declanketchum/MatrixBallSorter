#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

#define MAX 6

void setup() {
  Serial.begin(115200);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  int queue_in[MAX] = {0, 0, 0, 0, 0, 0}; //initialize queue with 6 white balls (must preload sorting tube with at least 5 white balls.
 
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux; //initize sensor variables
    // white = 0 and black =1
  int front = 0; //front index
  int rear = 4; //rear index
  int itemCount = 5; //initialize with 5 balls in queue
  int thresholdVal = 150;
  bool ballDropped = false;
  bool senseBall = true;
  int b5_color;
  int queue[MAX] = {0, 0, 0, 0, 0, 0}; //initialize queue with 6 white balls (must preload sorting tube with at least 5 white balls.

  tcs.getRawData(&r, &g, &b, &c); //get data from sensor r=red, g=green, b=blue, c=clear
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c); //in kelvin
  lux = tcs.calculateLux(r, g, b); //lumens per square meter


  if (senseBall) {
    //sense the ball's color. take 5 sensor values, if above threshold assum white if below assume black,
    int senseArr[5];
    int senseVal = c;
   // void loop() {
      for (int i = 0; i <= 4; i++) {
        int s;
        //take a few current c values (>150 is white, <150 is black)
        if (senseVal >= thresholdVal) {
          s = 0;
        } else {
          s = 5;
        }
        senseArr[i] = s;
      }
    //}
    
    int b5_average = average(senseVal, MAX);
    if(b5_average >=3) {
      b5_color = 1;
    }else {
      b5_color = 0;
    }
    Serial.print("ball 5 color:");
    Serial.println(b5_color);
    senseBall = false;
    } else{
    int ball_to_drop = dequeue(queue, front, itemCount);
    Serial.print("Ball dropped:" );
    Serial.println(ball_to_drop);
    //if ball to drop = 0
    //move servo to white
    //if ball to drop = 1
    //move servo to black
    //set ballDropped to true

     if (ballDropped) {
       enqueue(b5_color,rear, queue, itemCount, isFull);
     }

    if (isFull) {
      Serial.println("Queue is full!");
      //what do if full?! shouldnt ever be full so dequeue before enqueue
    }

  }
}

int look(int queue[], int front) { //fuction to look at the front ball in queue
return queue[front];
}

bool isFull(int itemCount) {
  return itemCount == MAX;
}

int siz(int itemCount) { //size of queue
  return itemCount;
}

//int isFull() {
//  return itemCount != M
//}

void enqueue(int color, int rear, int queue, int itemCount, bool isFull) { //function that adds the next ball to the queue (returns nothing)
  if (!isFull(itemCount)) {
    if (rear == MAX - 1) {
      rear = -1;
    }
    queue[++rear] = color;
    itemCount++;
  }//else wait for ball to drop?
}

int dequeue(int queue[], int front, int itemCount) { //function to remove one item and return that item's color
  int color = queue[front++];
  if (front == MAX) {
    front = 0;
  }
  itemCount--;
  return color;
  }
    
int average(int arr[], int n) {
   int sum = 0;
   int ave = 0;
   for (int i = 0; i < n; i++)
    sum += arr[i];
   ave = sum/n;
   return ave;
}
