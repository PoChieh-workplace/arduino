void setup() {
 pinMode(A0,INPUT);
 Serial.begin(9600);
}

void loop() {
  int Read = analogRead(A0);
  Serial.print(Read);
  delay(100);
};
