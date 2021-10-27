//LCD設置
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("Time!");
}


int second=0,minutes=0,hours=0;
void timeset(){
  if(second >=60){
    second -=60;
    minutes +=1;
  }
  if(minutes >=60){
    minutes -=60;
    hours +=1;
  }
}
void showtime(){
  String tmp = String(hours) + " : " + String(minutes) + " : " +String(second);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Time!");
  lcd.setCursor(1,1);
  lcd.print(tmp);
}


long timer = millis();
void loop(){
  if(millis()-timer>=1000){
    timer=millis();
    second +=1;
    timeset();
    showtime();
  }
}
