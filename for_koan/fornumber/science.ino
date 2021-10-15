int DS=2;//發貨
int DT=3;//出貨
int SH=4;//上貨
int testA0=0,testA1=0;
int digit_pin[4]={10,11,12,13};
int num_pin[10]={0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
void set7Seg(int number,int digit_show){
  for(int i=0;i<4;i++){
    digitalWrite(digit_pin[i], HIGH);
  }
  digitalWrite(DT, LOW);
  shiftOut(DS, SH,MSBFIRST, num_pin[number]);
  digitalWrite(DT,HIGH);

  digitalWrite(digit_pin[digit_show],LOW);
  delay(4);
}
void setup() {
  // put your setup code here, to run once:
  for(int i=2;i<14;i++){
    pinMode(i, OUTPUT);
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}
int a[4] ={0,0,0,0};
int get1 =0;
int get2 =0;
int hadpin(int n,int k){
  if(n >=1){
      a[k]+=2;
      if(n >=30){
        a[k]+=1;
      }
  }
  return 0;
}
void loop() {
  if(testA0==0){
    get1 = hadpin(get1,1);
  }
    
  if(testA1==0){
    get2 = hadpin(get2,3);
  }
  for(int i=0;i<2;i++){
    if(a[i*2+1]>9){
      a[i*2]+=1;
      a[i*2+1]-=10;
      
    }
    if(a[i*2+1]>9){
      a[i*2+1]-=10;
    }
  }
  // put your main code here, to run repeatedly
  for(int j=0;j<4;j++){
    set7Seg(a[j],j);
  }
  if(digitalRead(A0)==1){
    get1+=1;
  }
  testA0=(digitalRead(A0)==1?1:0);
  if(digitalRead(A1)==1){
    get2+=1;
  }
  testA1=(digitalRead(A1)==1?1:0);
  delay(4);
}
