int vrx = A1;
int vry = A2;
int SW = A3;
void setup(){
  Serial.begin(9600);
}
void loop(){
  int x = analogRead(A1);
  int y = analogRead(A2);
  int button = analogRead(A3);
  String text = ("VRx = "+ String(x) + ",VRy = "+ String(y) +",SW = "+ String(button));
  
  Serial.print(text);
  delay(100);
}
