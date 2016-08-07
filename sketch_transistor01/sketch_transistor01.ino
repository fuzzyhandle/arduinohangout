const int ledPin =  6;      // the number of the LED pin

byte loopCount = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
//  pinMode(collPin, OUTPUT);

}

void loop() {



  for (int i = 0; i <= 255; i++)
  {
    analogWrite(ledPin, i);
//    digitalWrite(collPin, i % loopCount);
    delay(10);
  }
  delay(20);
  loopCount ++;
}

