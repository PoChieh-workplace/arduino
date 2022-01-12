#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
short level=1;
int point=0;

void lcd_light(){
  lcd.setCursor(0,0);
  lcd.print(String("level:")+level);
  lcd.setCursor(0,1);
  lcd.print(String("point:")+point);
}

void lcd_setup(){
  point=0;
  level=1;
  lcd.init();
  lcd.backlight();
  lcd_light();
}


int tick_time=1000;
byte shape_idx[8][5] = {
  0,0,1,1,0, 0,0,0,1,0, 1,1,1,0,1, 0,1,2,3,0, 0,1,2,3,0, 0,0,1,0,0, 0,0,1,1,0, 1,1,0,0,0,
};
byte shape_idy[8][5] = {
  0,1,0,1,0, 0,1,2,2,0, 0,1,2,2,0, 1,1,1,1,1, 1,1,1,1,1, 0,1,1,2,0, 0,1,1,2,0, 0,1,1,2,0,
};



int DS=2;//貨物
int DT=3;//出發
int SH=4;//上貨
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

byte work[21][8] = {
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  
  1,1,1,1, 1,1,1,1,
};

bool table_data[16][8] = {
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0,
};


//max7219
void set_max7219(){
    bool address[8][8]={//初始設定
        {0,0,0,0,1,1,0,0},/*開啟顯示器模組*/
        {0,0,0,0,1,0,0,1},/*選用原始碼模式*/
        {0,0,0,0,1,1,1,1},/*關閉測試模式*/
        {0,0,0,0,1,0,1,0},/*設置初始亮度*/
        {0,0,0,0,1,0,1,1},/*8只LED全用*/
    };
    bool data[8][8]={//初始設定
        {0,0,0,0,0,0,0,1},/*開啟顯示器模組*/
        {0,0,0,0,0,0,0,0},/*選用原始碼模式*/
        {0,0,0,0,0,0,0,0},/*關閉測試模式*/
        {0,0,0,0,0,0,0,0},/*設置初始亮度*/
        {0,0,0,0,0,1,1,1},/*8只LED全用*/
    };
    for(int i = 0; i < 5; i++){
        digitalWrite(DT, LOW);//貨車開門
        for(int k = 0; k < 2; k++){//依次放入四車貨物
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
        }
        digitalWrite(DT, HIGH);//貨車出發
    }
    //歸零
    for(int i = 0; i < 8; i++){
        digitalWrite(DT, LOW);//貨車開門
        for(int k = 0; k < 2; k++){//依次放入四車貨物
            for (int j = 0; j < 8; j++)  {
                digitalWrite(SH, LOW);//活塞收回
                digitalWrite(DS, table_address[i][j]);
                digitalWrite(SH, HIGH);//活塞推出
            }
            for (int j = 0; j < 8; j++)  {
                digitalWrite(SH, LOW);//活塞收回
                digitalWrite(DS, 0);
                digitalWrite(SH, HIGH);//活塞推出
            }
        }
        digitalWrite(DT, HIGH);//貨車出發
    }
}

void max7219(bool address[8][8],bool data[16][8]){
    for(int i = 0; i < 8; i++){
        digitalWrite(DT, LOW);//貨車開門
        for(int k = 0; k < 2; k++){//依次放入四份貨物
            for (int j = 0; j < 8; j++)  {
                digitalWrite(SH, LOW);//活塞收回
                digitalWrite(DS, address[i][j]);
                digitalWrite(SH, HIGH);//活塞推出
            }
            for (int j = 0; j < 8; j++)  {
                digitalWrite(SH, LOW);//活塞收回
                digitalWrite(DS, data[(j+k*8)][7-i]);
                digitalWrite(SH, HIGH);//活塞推出
            }
        }
        digitalWrite(DT, HIGH);//貨車出發
    }
}

//搖桿設定
int vrx=A1,vry=A2,sw=A3;
int boom_x,boom_y,boom_button;
int way = 0;
void updata_boom_inf(){
  boom_x = analogRead(vrx);
  boom_y = analogRead(vry);
  boom_button = digitalRead(sw);
  if(boom_x>768){
    if(way == 0){
      way=4;  /*上*/
      turn_facing();
    }
  }
  else if(boom_y>768){
    if(way == 0){
      way=1;  /*左*/
      block_move(1);
    }
    
  }
  else if(boom_x<256){
    if(way == 0){
      way=3;
      tick_time=100;
    }
  }
  else if(boom_y<256){
    if(way == 0){
      way=2;  /*右*/
      block_move(2);
    }
  }
  else{
    way=0;
    tick_time=1000;
  }
}

//面板替換
void updata_table_data_inf(){
  for(int i=4;i<20;i++){
    for(int j=0;j<8;j++){
      table_data[i-4][j] = bool(work[i][j]);
    }
  }
}


bool reset = true;
int block_x=0,block_y=3;
byte shape = 0;
byte facing = 1;
byte block_i[5] = {0,0,0,0,0};
byte block_j[5] = {0,0,0,0,0};

//方塊位址更新
void inf_update(){
  for(byte i=0 ;i<sizeof(block_i);i++){
      work[block_i[i]+block_x][block_j[i]+block_y]=2;
  }
}

//方塊轉向
void turn_facing(){
  byte maxi = 0;
  byte maxj = 0;
  for(byte i=0;i<sizeof(block_i);i++){
    work[block_i[i]+block_x][block_j[i]+block_y]=0;
    maxi = maxi>block_i[i]?maxi:block_i[i];
    maxj = maxj>block_j[i]?maxj:block_j[i];
  }
  if(facing ==1 || facing==3){
    for(byte i=0;i<sizeof(block_i);i++){
      if(work[block_j[i]+block_x][block_i[i]+block_y]==1|| block_i[i]+block_y>7){
        return;
      }
    }
    facing = (facing >=4?1:facing+1);
    for(byte i=0;i<sizeof(block_i);i++){
      byte tmp = block_i[i];
      block_i[i] = block_j[i];
      block_j[i] = tmp;
    }
  }
  
  else{
    for(byte i=0;i<sizeof(block_i);i++){
      if(work[maxi-block_i[i]+block_x][maxj-block_j[i]+block_y]==1 || maxj-block_j[i]+block_y>7){
        return;
      }
    }
    facing = (facing >=4?1:facing+1);
    for(byte i=0;i<sizeof(block_i);i++){
      block_i[i]= maxi-block_i[i];
      block_j[i]= maxj-block_j[i];
    }
  }
  inf_update();
}

//方塊位移
void block_move(byte side){
  if(side==2){
    byte minj = 100;
    bool allow_move=true;
    for(byte i=0;i<sizeof(block_i);i++){
      minj = minj<block_j[i]?minj:block_j[i];
    }
    for(byte i=block_x;i<block_x+sizeof(block_i);i++){
      if(work[i][minj-1]==1 || block_y+minj<1){
        allow_move=false;
      }
    }
    if(allow_move==true){
      for(byte i=0;i<sizeof(block_i);i++){
        work[block_i[i]+block_x][block_j[i]+block_y]=0;
      }
      block_y-=1;
    }
  }
  else if(side==1){
    byte maxj = 0;
    bool allow_move=true;
    for(byte i=0;i<sizeof(block_i);i++){
      maxj = maxj>block_j[i]?maxj:block_j[i];
    }
    for(byte i=block_x;i<block_x+sizeof(block_i);i++){
      if(work[i][maxj+1]==1){
        allow_move=false;
      }
    }
    if (maxj+block_y<7 &&  allow_move==true){
      for(byte i=0;i<sizeof(block_i);i++){
        work[block_i[i]+block_x][block_j[i]+block_y]=0;
      }
      block_y+=1;
    }
  }
  inf_update();
}



//方塊墜落
void blockdown(){
  bool block_stop = false;
  for(byte i=0 ;i<sizeof(block_i);i++){
    if(work[block_i[i]+block_x+1][block_j[i]+block_y] == 1){
      for(byte q=0 ;q<sizeof(block_j);q++){
        work[block_i[q]+block_x][block_j[q]+block_y]=1;
      }
      reset=true;
      return;
    }
  }
  for(byte i=0 ;i<sizeof(block_i);i++){
    for(byte j=0 ;j<sizeof(block_j);j++){
      work[block_i[i]+block_x][block_j[i]+block_y]=0;
    }
  }
  block_x+=1;
  inf_update();
}

void spawn(){
  shape = random(sizeof(shape_idx)/5);
  for(byte i=0;i<5;i++){
    block_i[i] = shape_idx[shape][i];
    block_j[i] = shape_idy[shape][i];
  }
  block_x=0;
  block_y=3;
  reset = false;
}

void _point(){
  byte tmp_tick=1;
  for(byte i = 19;i>0;){
    bool getpoint = true;
    for(byte j=0;j<8;j++){
      if(work[i][j]!=1){
        getpoint = false;
        break;
      }
    }
    if(getpoint == true){
      point+= 100*tmp_tick;
      lcd_light();
      tmp_tick+=1;
      for(byte j=0;j<8;j++){
        work[i][j]=0;
      }
      for(byte k=i;k>0;k--){
        for(byte j=0;j<8;j++){
          work[k][j]=work[k-1][j];
        }
      }
      continue;
    }
    i--;
  }
}

void _setup(){
  for(int i=0;i<20;i++){
    for(int j=0;j<8;j++){
      work[i][j]=0;
    }
  }
  for(int i=0;i<16;i++){
    for(int j=0;j<8;j++){
      table_data[i][j]=0;
    }
  }
}

int game_start=0;
void end_game(){
  for(int i=0;i<8;i++){
    if(work[0][i]==1){
      Serial.println(String("game_reseting"));
      for(int k=0;k<16;k++){
        for(int j=0;j<8;j++){
          table_data[k][j]= table_data[k][j]==1?0:1;
        }
        delay(50);
        max7219(table_address,table_data);
      }
      lcd_setup();
      _setup();
      game_start=0;
      break;
    }
  }
}



long block_time_delay = millis();
long max7219_delay = millis();

void setup() {
  pinMode(DS,OUTPUT);
  pinMode(DT,OUTPUT);
  pinMode(SH,OUTPUT); 
  lcd_setup();
  set_max7219();
  Serial.begin(9600);
}



void loop() {

  //遊戲初始畫面
  while(game_start==0){
    updata_boom_inf();
    if(boom_button==1){
      game_start=1;
      Serial.println(String("Start"));
    }
  }
  
  //遊戲開始
  updata_table_data_inf();
  updata_boom_inf();
  
  if(millis()- block_time_delay >=tick_time/level){
    block_time_delay = millis();
    blockdown();
    if(reset == true){
      _point();
      lcd_light();
      spawn();
    }
  }
  if(millis()- max7219_delay >=(tick_time/level)/3){
    max7219_delay = millis();
    max7219(table_address,table_data);
    level=int(point/500+1);
    end_game();
  }
  
}
