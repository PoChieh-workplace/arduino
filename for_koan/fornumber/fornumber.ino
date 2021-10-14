int DS=2;//發貨
int DT=3;//出貨
int SH=4;//上貨
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

 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);
 pinMode(A0, INPUT);
 pinMode(A1, INPUT);
}
int a[4] ={0,0,0,0};
int get1 =0;
int get2 =0;
void loop() {
  if(digitalRead(A0)==0){
    if(get1 >=1){
      a[1]+=2;
      if(get1 >=30){
        a[1]+=1;
      }
    }
    get1=0;
  }
  if(digitalRead(A1)==0){
    if(get2 >=1){
      a[3]+=2;
      if(get2 >=30){
        a[3]+=1;
      }
    }
    get2=0;
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
  for(int i=0;i<2;i++){
    
  }
  // put your main code here, to run repeatedly:
  for(int i=0;i<100;i++){
    set7Seg(a[0],0);
    set7Seg(a[1],1);
    set7Seg(a[2],2);
    set7Seg(a[3],3);
    if(digitalRead(A0)==1){
      get1+=1;
    }
    if(digitalRead(A1)==1){
      get2+=1;
    }
    delay(4);
  }
}
