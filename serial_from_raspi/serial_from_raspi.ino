String datastring;
int rows; 
int cols;  

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  
  if(Serial.available()) {
    datastring = Serial.readStringUntil('\n');
    rows = Serial.readStringUntil('\n').toInt();
    cols = Serial.readStringUntil('\n').toInt();//, data, sizeof(data)-1);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
    delay(1000);

    if(rows == 35) {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW); 
      delay(1000);
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW); 

    
    }
  } 
}
