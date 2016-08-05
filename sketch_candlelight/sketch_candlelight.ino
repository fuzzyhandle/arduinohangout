/* Create a Candle light flame effect

Cover the LEDs with a tissue paper to diffuse the light and then observe the effect in a dark area
  
Refer to the corresponding fritzing diagram

*/
const int ledPin1 =  5;   
const int ledPin2 =  6;   
const int ledPin3 =  9;   

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite( ledPin1, random(0,20));
  delay(400);

  analogWrite( ledPin2, random(0,125));
  delay(300);
  analogWrite( ledPin3, random(0,125));      
  delay(300);
}
