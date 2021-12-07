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

void setup(void) {
  Serial.begin(115200);

  // white = 0 and black =1
  int queue[MAX] = {0, 0, 0, 0, 0, 0}
  int front = 0;
  int rear = 4;
  int itemCount = 5;

  int look() {
    return queue[front];
  }

  bool isEmpty() {
    return itemCount == MAX;
  }

  int siz() {
    return itemCount;
  }

  void enqueue(int color) {
    if(!isFull()) {
      if(rear == MAX-1) {
        rear = -1;
      }
      queue[++rear] = color;
      itemCount++;
    }
  }

  int dequeue() {
    int color = queue[front++];

    if(front == MAX) {
      front = 0;
    }

    itemCount--;
    return color;
  }

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

//take a few current c values (>150 is white, <150 is black)
  int senseVal[5];
//majority rules to set b5_color
//once ball drops, clear 
  

  int main() {
    enqueue(b5_color)

    if(isFull()) {
      Serial.println("Queue is full!");
    }

    int ball_to_drop = dequeue();

    Serial.println("Ball dropped:  %d\n", ball_to_drop)
  }
}
