int Ds=2;
int DT=3;
int SH=4;
bool num[10]={
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
void setup() {
  pinMode(Ds,OUTPUT);
  pinMode(DT,OUTPUT);
  pinMode(SH,OUTPUT);
/*  pinMode(buttom,INPUT);*/
}

void loop() {
  for(int i=0;i<10;i++){
      digitalWrite(DT,LOW);
      shiftOut(Ds, SH, MSBFIRST, num[1]);
      digitalWrite(DT,HIGH);
      delay(100);
  }
}
