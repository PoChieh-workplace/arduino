int DS=2;
int DT=3;
int SH=4;
int buttom=7;
int num[10]={
  0x3F,
  0x6,
  0x5B,
  0x4F,
  0x66,
  0x6D,
  0x7D,
  0x27,
  0x7F,
  0x67
};
int i= 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(DS,OUTPUT);
  pinMode(DT,OUTPUT);
  pinMode(SH,OUTPUT);
  pinMode(buttom,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int but = digitalRead(buttom);
if (but == 0){
  digitalWrite(DT,0);
  shiftOut(DS,SH, MSBFIRST, num[i]);
  digitalWrite(DT,1);
  delay(100);
}
else{
  if (i == 9){
    i = 0;
  }
  else{
    i+=1;  
  }
  digitalWrite(DT,0);
  shiftOut(DS,SH, MSBFIRST, num[i]);
  digitalWrite(DT,1);
  delay(100);
}
}
