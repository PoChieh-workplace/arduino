int button = 5;
int speaker = 12;

void play() {
  for(int i=0;i<3;i++){
    tone(speaker,261.62);
    delay(250);
    noTone(speaker);
    delay(50);
  }
}

void setup() {
  pinMode(button,INPUT);
  pinMode(speaker,OUTPUT);
}

void loop() {
  int state = digitalRead(button);
  if(state == HIGH){
    play();
  }
}
