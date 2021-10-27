int vrx = A1;
int vry = A2;
int SW = A3;

int nowi=4,nowj=4;
int number = 4;
int way = 1;

int DS=2;//貨物DIN
int DT=3;//出發CS
int SH=4;//上貨CLK

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


bool high_data[8][8]={
    {0,0,0,0,0,0,0,0},/*第1行數值*/
    {0,0,0,0,0,0,0,0},/*第2行數值*/
    {0,0,0,0,0,0,0,0},/*第3行數值*/
    {0,0,0,0,0,0,0,0},/*第4行數值*/
    {0,0,0,0,0,0,0,0},/*第5行數值*/
    {0,0,0,0,0,0,0,0},/*第6行數值*/
    {0,0,0,0,0,0,0,0},/*第7行數值*/
    {0,0,0,0,0,0,0,0}/*第8行數值*/
};

void setup(){
  max7219(set_address,set_data);
  Serial.begin(9600);
  set_second[4][4]=1;
}

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
int shownext(int i,int j){
  if(way==1 and i>0){
    return high_data[i-1][j];
  }
  if(way==2 and i<7){
    return high_data[i][j+1];
  }
  if(way==3 and i<7){
    return high_data[i+1][j];
  }
  if(way==4 and i>7){
    return high_data[i][j-1];
  }
  return 0;
}

void setdat(){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      high_data[i][j] = bool(set_second[i][j]==0?0:1);
    }
  }
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      set_second[i][j] = (set_second[i][j]>0?(set_second[i][j]-1):0);
    }
  }
}

void data(int i,int j){
  switch(way){
    case 1:
      set_second[i+1][j]=number;
      nowi+=1;
      break;
    case 2:
      set_second[i][j+1]=number;
      nowj+=1;
      break;
    case 3:
      set_second[i-1][j]=number;
      nowi-=1;
      break;
    case 4:
      set_second[i][j-1]=number;
      nowj-=1;
      break;
  }
}

int wayx,wayy;
void getboom(){
  int x = analogRead(A1);
  int y = analogRead(A2);
  int button = analogRead(A3);
  wayx = (x>700?1:0);
  wayx = (x<300?-1:wayx);
  wayy = (y>700?1:0);
  wayy = (y<300?-1:wayy);
  if(wayx==0 and wayy==1){
    way = 1;
  }
  if(wayx==1 and wayy==0){
    way = 2;
  }
  if(wayx==0 and wayy==-1){
    way = 3;
  }
  if(wayx==-1 and wayy==0){
    way = 4;
  }
}

void loop(){
  for(int i=0;i<10;i++){
    getboom();
    delay(100);
  }
  max7219(table_address,high_data);
  setdat();
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      Serial.print(high_data[i][j]);
    }
    Serial.print('\n');
  }
  data(nowi,nowj);
}
