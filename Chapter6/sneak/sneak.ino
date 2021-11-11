int DS=2;//貨物DIN
int DT=3;//出發CS
int SH=4;//上貨CLK

int vrx = A1;
int vry = A2;
int SW = A3;

int way = 4;
int level = 3;
bool set_address[8][8]={//初始設定
    {0,0,0,0,1,1,0,0},/*開啟或關閉顯示器模組*/
    {0,0,0,0,1,0,0,1},/*選用原始碼或解碼模式*/
    {0,0,0,0,1,1,1,1},/*開啟或關閉測試模式*/
    {0,0,0,0,1,0,1,0},/*亮度0~15*/
    {0,0,0,0,1,0,1,1},/*行數限制0~7*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零糕*/
    {0,0,0,0,0,0,0,0}/*當歸鴨*/
};
bool set_data[8][8]={//初始設定
    {0,0,0,0,0,0,0,1},/*開啟(1)或關閉(0)顯示器模組*/
    {0,0,0,0,0,0,0,0},/*原始碼(0)解碼(1)模式*/
    {0,0,0,0,0,0,0,0},/*開啟(1)關閉(0)測試模式*/
    {0,0,0,0,1,1,1,1},/*設置初始亮度0*/
    {0,0,0,0,0,1,1,1},/*8行LED全用*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零糕*/
    {0,0,0,0,0,0,0,0}/*當歸鴨*/
};
bool table_address[8][8]={
    {0,0,0,0,0,0,0,1},/*第1行地址*/
    {0,0,0,0,0,0,1,0},/*第2行地址*/
    {0,0,0,0,0,0,1,1},/*第3行地址*/
    {0,0,0,0,0,1,0,0},/*第4行地址*/
    {0,0,0,0,0,1,0,1},/*第5行地址*/
    {0,0,0,0,0,1,1,0},/*第6行地址*/
    {0,0,0,0,0,1,1,1},/*第7行地址*/
    {0,0,0,0,1,0,0,0}/*第8行地址*/
};
bool wen_data[8][8]={
    {0,0,0,0,0,0,0,0},/*第1行數值*/
    {0,0,0,0,0,0,0,0},/*第2行數值*/
    {0,0,0,0,0,0,0,0},/*第3行數值*/
    {0,0,0,0,0,0,0,0},/*第4行數值*/
    {0,0,0,0,0,0,0,0},/*第5行數值*/
    {0,0,0,0,0,0,0,0},/*第6行數值*/
    {0,0,0,0,0,0,0,0},/*第7行數值*/
    {0,0,0,0,0,0,0,0}/*第8行數值*/
};

int set_second[8][8]={//初始設定
    {0,0,0,0,0,0,0,0},/*開啟(1)或關閉(0)顯示器模組*/
    {0,0,0,0,0,0,0,0},/*原始碼(0)解碼(1)模式*/
    {0,0,0,0,0,0,0,0},/*開啟(1)關閉(0)測試模式*/
    {0,0,0,0,0,0,0,0},/*設置初始亮度0*/
    {0,0,0,0,0,0,0,0},/*8行LED全用*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零糕*/
    {0,0,0,0,0,0,0,0}/*當歸鴨*/
};

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
    Serial.begin(9600);
}
void setcurse(){
  set_second[4][4]=level;
}

void set_wen(){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      Serial.print(wen_data[i][j]);
    }
    Serial.println('\n');
  }
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      wen_data[i][j]=(set_second[i][j]==0?0:1);
      set_second[i][j] = (set_second[i][j]==0?0:set_second[i][j]-1);
    }
  }
}
void getway(){
  int x = analogRead(vrx);
  int y = analogRead(vry);
  int btway = analogRead(SW);
  /*Serial.print("wayx = ");
  Serial.println(x);
  Serial.print("wayy = ");
  Serial.println(y);
  Serial.print("way = ");
  Serial.println(btway);*/
  int tmp = way;
  if(x>600 && y<600 && y>400){
    tmp=2;
  }
  if(x<400 && y<600 && y>400){
    tmp=3;
  }
  if(x>400 && x<600 && y>600){
    tmp=1;
  }
  if(x>400 && x<600 && y<400){
    tmp=4;
  }
  way = (tmp==5-way?way:tmp);
}

int showapple=0;
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

int nowx =4,nowy=4;
void check(){
  if(showapple==1){
    if(set_second[nowx][nowy]>100){
      level+=1;
      showapple=0;
    }
  }
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





int endl =0;

void loop() {
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
    if(analogRead(SW)>500){
      endl=0;
    }
}
