
int pin[12] = {2,3,4,5,6,7,8,9,10,11,12,13};
int out[10][8]={
  {1,1,1,1,1,1,0,0},
  {0,1,1,0,0,0,0,0},
  {1,1,0,1,1,0,1,0},
  {1,1,1,1,0,0,1,0},
  {0,1,1,0,0,1,1,0},
  {1,0,1,1,0,1,1,0},
  {1,0,1,1,1,1,1,0},
  {1,1,1,0,0,1,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,0,0,1,1,0},
  };
void setup() {
  for(int i=0;i<15;i++){
    pinMode(pin[i],OUTPUT);
  }
  pinMode(A0,INPUT);
}
void play(){
  for(int i=9;i>-1;i--){
  
    for(int j=0;j<8;j++)
    {
      digitalWrite(pin[j],0);
    }
    for(int j=0;j<8;j++)
    {
      digitalWrite(pin[j],int(out[i][j]));
    } 
    for(int j=10;j<14;j++){
      digitalWrite(j,1);
      delay(200);
      digitalWrite(j,0);
    }
    delay(200);
  }
}
void loop() {
/*  char out[] = {3,3,4,5};
  for(int i=0;i<10;i++){
    for(int j=0;j<8;j++)
    {
      digitalWrite(int(out[i][j]),LOW);
    }
*/  
int state = digitalRead(A0);
  if(state == HIGH){
    play();
  }
}
