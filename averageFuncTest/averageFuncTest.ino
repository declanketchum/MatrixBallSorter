void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int MAX = 4;
  int arra[4] = {1, 4, 3, 4};
  Serial.print(average(arra, MAX));

}

int average(int arr[], int n) {
   int sum = 0;
   int ave = 0;
   for (int i = 0; i < n; i++)
    sum += arr[i];
   ave = sum/n;
   return ave;
}
