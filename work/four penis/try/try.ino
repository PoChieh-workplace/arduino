const float R = 10000.0;

void setup()
{
  Serial.begin( 9600 );
}

void loop()
{
  int value = analogRead( A0 );
  float r = ( 1023.0 - value ) / ( value / R );
  Serial.println( r );
  delay( 1000 );
}
