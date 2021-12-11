byte data[1000];


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  
  while(!Serial.available()) {
    ;
  }

  Serial.readBytesUntil('\n', data, sizeof(data)-1);


  // This should turn the LED either on or off to represent a
  // 0 or 1 in the array, updating every half second
  
  for(int i=0; i<sizeof(data); i++) {

    // Not sure if this will work
    // May need to check case-wise:
    //   i.e. if bit == 0x00, led off,
    //      elif bit == 0xff, led on
    digitalWrite(LED_BUILTIN, bool(data[i]));
    delay(500);
  }
    
}
