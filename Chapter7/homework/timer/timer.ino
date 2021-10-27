#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
long timer = millis();
a[3]={0,0,0}

void test(){
  if(a[0]>=60){
    a[0]-=60;
    a[1]+=1;
    if(a[1]>=60):{
      a[1]-=60;
      a[2]+=1;
    }
  }
}


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Now time：")
}

void loop() {
  if(millis()-timer>=1000){
    timer millis();
    lcd.setCursor(1,0);
    lcd.print('%2d:%2d:%2d' % (a[2],a[1],a[0]));
    a[0]+=1;
    test();
  }
}
