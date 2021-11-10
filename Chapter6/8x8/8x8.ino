int DS=2;//貨物
int DT=3;//出發
int SH=4;//上貨
int vrx = A1;//搖桿x
int vry = A2;//搖桿y
int sw = A3;//搖桿按鈕
bool set_address[8][8]={//初始設定
    {0,0,0,0,1,1,0,0},/*開啟顯示器模組*/
    {0,0,0,0,1,0,0,1},/*選用原始碼模式*/
    {0,0,0,0,1,1,1,1},/*關閉測試模式*/
    {0,0,0,0,1,0,1,0},/*設置初始亮度*/
    {0,0,0,0,1,0,1,1},/*8只LED全用*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0}/*歸零*/
};
bool set_data[8][8]={//初始設定
    {0,0,0,0,0,0,0,1},/*開啟顯示器模組*/
    {0,0,0,0,0,0,0,0},/*選用原始碼模式*/
    {0,0,0,0,0,0,0,0},/*關閉測試模式*/
    {0,0,0,0,0,1,1,1},/*設置初始亮度*/
    {0,0,0,0,0,1,1,1},/*8只LED全用*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0}/*歸零*/
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
bool table_data[8][8]={
    {0,0,0,0,0,0,0,0},/*第1行數值*/
    {0,0,0,0,0,0,0,0},/*第2行數值*/
    {0,0,0,0,0,0,0,0},/*第3行數值*/
    {0,0,0,1,1,1,0,0},/*第4行數值*/
    {0,0,0,0,0,0,0,0},/*第5行數值*/
    {0,0,0,0,0,0,0,0},/*第6行數值*/
    {0,0,0,0,0,0,0,0},/*第7行數值*/
    {0,0,0,0,0,0,0,0}/*第8行數值*/
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
    pinMode(vrx,INPUT);
    pinMode(vry,INPUT);
    pinMode(sw,INPUT);
    max7219(set_address,set_data);
}
int snake_x[64]={3,3,3,3};/*蛇的身體位置紀錄表*/
int snake_y[64]={3,4,5,6};/*0是尾巴*/
int level=4;            /*長度*/
int head_x=3,head_y=5;  /*頭的位置*/
int way=0;              /*方向*/
int sleep=300;          /*速度*/
long timer=0;

void loop() {  
    if(millis()-timer>sleep){
        timer=millis();
        go();
        max7219(table_address,table_data);
    }
    read_way();
}
void read_way(){
    int x = analogRead(vrx);
    int y = analogRead(vry);
    if(x>768){
        if(way!=2){
            way=0;
        }
    }
    if(y>768){
        if(way!=3){
            way=1;
        }
    }
    if(x<256){
        if(way!=0){
            way=2;
        }
    }
    if(y<256){
        if(way!=1){
            way=3;
        }
    }
}
void go(){
    table_data[snake_x[0]][snake_y[0]]=0;/*尾巴的點暗*/
    /*先從尾巴開始縮*/
    for(int i=0;i<level-1;i++){
        snake_x[i]=snake_x[i+1];
        snake_y[i]=snake_y[i+1];
    }
    /*依照方向移動頭部座標*/
    change_way();
    /*紀錄頭部位置*/
    snake_x[level-1]=head_x;
    snake_y[level-1]=head_y;
    table_data[head_x][head_y]=1;/*頭的點亮*/
}


void change_way(){
    /*依照方向移動頭部座標*/
    if(way==0){
        head_y=(head_y+1)%8;
    }
    else if(way==1){
        head_x=(head_x+1)%8;
    }
    else if(way==2){
        head_y=(head_y+7)%8;
    }
    else{
        head_x=(head_x+7)%8;
    }
}



void setapple(int x,int y){
    while (true)
    {
        int i = random(7);
        int j = random(7);
        bool brk = false;
        for(int k=0;k<x.length();k++){
            if(x[k]!=i && y[k]!=j){
                brk = true;
            }
        }
        if(brk == true){
            break;
        }
    }
}


/* 
  第一步：建立一個go函式，
  第二步：
  第三步：
  第四步：
  第五步：
*/
