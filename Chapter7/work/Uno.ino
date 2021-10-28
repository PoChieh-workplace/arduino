
#include<Wire.h>
#include<ThreeWire.h>
#include<RtcDS1302.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
int RST=5;
int DAT=6;
int CLK=7;
int DHTPIN = 2;
DHT dht(DHTPIN,DHT11);
ThreeWire myWire(DAT,CLK, RST);
RtcDS1302<ThreeWire> Rtc(myWire);
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Rtc.Begin();
  dht.begin();
  RtcDateTime compiled = RtcDateTime(__DATE__,__TIME__);
  Rtc.SetDateTime(compiled);
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  RtcDateTime now = Rtc.GetDateTime();
  String Date =  String(now.Year())+"/"+String(now.Month())+"/"+String(now.Day());
  String nowtime = String(now.Hour())+ ":" +String(now.Minute())+ ":" + String(now.Second());
  Serial.print(Date + nowtime + '\n');
  lcd.setCursor(0,0);
  lcd.print(Date + nowtime);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0,1);
  lcd.print("t:");
  lcd.setCursor(2,1);
  lcd.print(t);
  lcd.setCursor(9,1);
  lcd.print("h:");
  lcd.setCursor(11,1);
  lcd.print(h);
  delay(100);
}
