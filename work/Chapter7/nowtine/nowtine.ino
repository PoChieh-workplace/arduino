#include<Wire.h>
#include<ThreeWire.h>
#include<RtcDS1302.h>
int RST=5;
int DAT=6;
int CLK=7;
ThreeWire myWire(DAT,CLK, RST);
RtcDS1302<ThreeWire> Rtc(myWire);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__,__TIME__);
  Rtc.SetDateTime(compiled);
}

void loop() {
  // put your main code here, to run repeatedly:
  RtcDateTime now = Rtc.GetDateTime();
  String Date =  String(now.Year())+"/"+String(now.Month())+"/"+String(now.Day());
  String nowtime = String(now.Hour())+ ":" +String(now.Minute())+ ":" + String(now.Second());
  Serial.print(Date + nowtime + '\n');
  delay(100);
}
