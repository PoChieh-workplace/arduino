int DS=2;//貨物DIN
int DT=3;//出發CS
int SH=4;//上貨CLK

int vrx = A1;
int vry = A2;
int SW = A3;

int way = 1;
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
    {0,0,0,0,0,0,1,0},/*第1行數值*/
    {1,0,0,0,1,1,1,0},/*第2行數值*/
    {0,1,0,1,0,0,1,0},/*第3行數值*/
    {0,0,1,0,0,0,1,1},/*第4行數值*/
    {0,1,0,1,0,0,1,0},/*第5行數值*/
    {1,0,0,0,1,1,1,0},/*第6行數值*/
    {0,0,0,0,0,0,1,0},/*第7行數值*/
    {0,0,0,0,0,0,0,0}/*第8行數值*/
};

int set_second[8][8]={//初始設定
    {0,0,0,0,0,0,0,0},/*開啟(1)或關閉(0)顯示器模組*/
    {0,0,0,0,0,0,0,0},/*原始碼(0)解碼(1)模式*/
    {0,0,0,0,0,0,0,0},/*開啟(1)關閉(0)測試模式*/
    {0,0,0,0,0,0,0,0},/*設置初始亮度0*/
    {0,0,0,0,level,0,0,0},/*8行LED全用*/
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

void setway(){
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
  if(x>700 && y<700 && y>300){
    tmp=2;
  }
  if(x<300 && y<700 && y>300){
    tmp=3;
  }
  if(x>300 && x<700 && y>700){
    tmp=1;
  }
  if(x>300 && x<700 && y<300){
    tmp=4;
  }
  way = (tmp==5-way?way:tmp);
  Serial.println(way);
}








void loop() {
    max7219(table_address,wen_data);
    setway();
    delay(1000);
}
