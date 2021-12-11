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

  for(int i=0; i<(sizeof(data)-1), i++) {
    
    digitalWrite(LED_BUILTIN, data[i]);
  
  }
    
}
