const int ledPin =  9;   

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int i =0;i<255;i++){
    analogWrite( ledPin, i);
    delay(8);
    }
   delay(1000);
    
    for (int i =255;i>=0;i-=5){
    analogWrite( ledPin, i);
    delay(50);
    }
    delay(1000);

    delay(1000);
}
