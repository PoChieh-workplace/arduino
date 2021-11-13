//===========8*8初始設定===========
bool set_address[8][8]={
    {0,0,0,0,1,1,0,0},
    {0,0,0,0,1,0,0,1},
    {0,0,0,0,1,1,1,1},
    {0,0,0,0,1,0,1,0},
    {0,0,0,0,1,0,1,1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};
bool set_data[8][8]={
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1},
    {0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};
bool table_address[8][8]={
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,1,1},
    {0,0,0,0,0,1,0,0},
    {0,0,0,0,0,1,0,1},
    {0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,1},
    {0,0,0,0,1,0,0,0}
};


//===========8*8顯示陣列===========
bool wen_data[8][8]={
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

//===========時間計算陣列===========
int set_second[8][8]={
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};


//===========8*8 pin角===========
int DS=2;
int DT=3;
int SH=4;


//===========搖桿 pin角===========
int vrx = A1;
int vry = A2;
int SW = A3;


//===========蛇蛇 變數===========
int way = 4;
int level = 3;
int nowx =4,nowy=4;



//===========系統變數===========
int endl =0;
int showapple=0;


void max7219(bool address[8][8],bool data[8][8]){
    for(int i = 0; i < 8; i++){
        digitalWrite(DT, LOW);//貨車開門
        for (int j = 0; j < 8; j++)  {
            digitalWrite(SH, LOW);//活塞收回
            digitalWrite(DS, address[i][j]);
            digitalWrite(SH, HIGH);//活塞推出
        }
        for (int j = 0; j < 8; j++)  {
            digitalWrite(SH, LOW);//活塞收回
            digitalWrite(DS, data[i][j]);
            digitalWrite(SH, HIGH);//活塞推出
        }
        digitalWrite(DT, HIGH);//貨車出發
    }
}

void setup() {
    pinMode(DS,OUTPUT);
    pinMode(DT,OUTPUT);
    pinMode(SH,OUTPUT); 
    max7219(set_address,set_data);
}


//===========開頭設置===========
void setcurse(){
  way = 4;
  level = 3;
  nowx =4,nowy=4;
  showapple=0;
  set_second[4][4]=level;
  for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
        set_second[i][j]=0;
      }
    }
}


//===========顯示器輸出===========
void set_wen(){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      wen_data[i][j]=(set_second[i][j]==0?0:1);
      set_second[i][j] = (set_second[i][j]==0?0:set_second[i][j]-1);
    }
  }
}


//===========食物設置===========
void setapple(){
  int x=random(8),y=random(8);
  if(set_second[x][y]!=0){
    setapple();
  }
  else{
    set_second[x][y]=300;
    showapple=1;
  }
}


//===========觸碰偵測===========
void check(){
  if(showapple==1){
    if(set_second[nowx][nowy]>100){
      level+=1;
      showapple=0;
    }
  }
  if(set_second[nowx][nowy]<=100 and set_second[nowx][nowy]!=0){
    endl=1;
  }
}


//===========方位取得===========
void getway(){
  int x = analogRead(vrx);
  int y = analogRead(vry);
  int btway = analogRead(SW);
  int tmp = way;
  if(x>650){
    tmp=2;
  }
  if(x<350){
    tmp=3;
  }
  if(y>650){
    tmp=1;
  }
  if(y<350){
    tmp=4;
  }
  way = (tmp==5-way?way:tmp);
}

void set_way(){
  switch(way){
    case 1:
      nowx =(nowx==7?0:nowx+1);
      break;
    case 2:
      nowy =(nowy==7?0:nowy+1);
      break;
    case 3:
      nowy =(nowy==0?7:nowy-1);
      break;
    case 4:
      nowx =(nowx==0?7:nowx-1);
      break;
  }
  check();
  set_second[nowx][nowy] = level;
}


//===========流程===========
void loop() {
  long sneaktimer=millis();
  long musictimer=millis();
  
  max7219(table_address,wen_data);
  setcurse();
  while(endl==0){
    for(int i=0;i<5;i++){
      getway();
      delay(500/level);
    }
    set_wen();
    set_way();
    
    if(showapple==0){
      setapple();
    }
    max7219(table_address,wen_data);
  }
  
  //=======結束畫面=======
  for(int i=0;i<8;i++){
    if(i%2==0){
      for(int j=0;j<8;j++){
        wen_data[i][j]=1;
        max7219(table_address,wen_data);
        delay(20);
      }
    }
    else{
      for(int j=7;j>=0;j--){
        wen_data[i][j]=1;
        max7219(table_address,wen_data);
        delay(20);
      }
    }
  }
  for(int i=0;i<8;i++){
    if(i%2==0){
      for(int j=0;j<8;j++){
        wen_data[i][j]=0;
        max7219(table_address,wen_data);
        delay(20);
      }
    }
    else{
      for(int j=7;j>=0;j--){
        wen_data[i][j]=0;
        max7219(table_address,wen_data);
        delay(20);
      }
    }
  }
  
  
  //=======重新開始=======
  while(endl==1){
    if(analogRead(SW)>500){
      endl=0;
    }
  }
}
