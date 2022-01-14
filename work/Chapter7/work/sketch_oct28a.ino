#include <DHT.h>
#include <DHT_U.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
int RST=5;
int DAT=6;
int CLK=7;
ThreeWire myWire(DAT,CLK,RST);
RtcDS1302<ThreeWire> Rtc(myWire);
int DHTPIN=2;
DHT dht(DHTPIN,DHT11);

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

long timer=millis();
int h=0,m=0,s=0;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);  
  dht.begin();
  Rtc.Begin();
  RtcDateTime cp = RtcDateTime(__DATE__,__TIME__);
  Rtc.SetDateTime(cp);
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  lcd.setCursor(0,0);
  lcd.print(now.Month());
  lcd.setCursor(2,0);
  lcd.print("/");
  lcd.setCursor(3,0);
  lcd.print(now.Day());
  lcd.setCursor(0,1);
  lcd.print(now.Hour());
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(now.Minute());
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(now.Second());

  float hum=dht.readHumidity();
  float tem=dht.readTemperature();
  lcd.setCursor(9,0);
  lcd.print("t:");
  lcd.setCursor(11,0);
  lcd.print(tem);
  lcd.setCursor(9,1);
  lcd.print("h:");
  lcd.setCursor(11,1);
  lcd.print(hum);
  delay(100);
}
