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
bool table_data[16][8]={
    {0,0,0,0,0,0,1,0},/*第1行數值*/
    {1,0,0,0,1,1,1,0},/*第2行數值*/
    {0,1,0,1,0,0,1,0},/*第3行數值*/
    {0,0,1,0,0,0,1,1},/*第4行數值*/
    {0,1,0,1,0,0,1,0},/*第5行數值*/
    {1,0,0,0,1,1,1,0},/*第6行數值*/
    {0,0,0,0,0,0,1,0},/*第7行數值*/
    {0,0,0,0,0,0,0,0},/*第8行數值*/
    
    {0,1,0,1,0,0,1,0},/*第1行數值*/
    {0,1,1,1,1,1,1,1},/*第2行數值*/
    {0,1,1,1,0,1,1,0},/*第3行數值*/
    {1,1,1,1,1,1,1,0},/*第4行數值*/
    {0,1,1,1,0,1,1,0},/*第5行數值*/
    {0,1,1,1,1,1,1,1},/*第6行數值*/
    {0,1,0,1,0,0,1,0},/*第7行數值*/
    {0,0,0,0,0,0,0,0},/*第8行數值*/
};
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
int start=0;
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
                digitalWrite(DS, data[(j+k*8+start)%16][7-i]);
                digitalWrite(SH, HIGH);//活塞推出
            }
        }
        digitalWrite(DT, HIGH);//貨車出發
    }
}
void setup() {
    pinMode(DS,OUTPUT);
    pinMode(DT,OUTPUT);
    pinMode(SH,OUTPUT); 
    set_max7219();
}

void loop() {
    max7219(table_address,table_data);
    start++;
    delay(100);
}
