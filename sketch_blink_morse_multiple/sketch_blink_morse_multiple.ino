/* Morse Code

  Light up the LED to send a Morse code for a given string
  
  Use 1 LED for a DOT and 3 LEDs for a Dash
  
  To get the morse code just open the Serial Terminal and type in a string and hit ENTER.
  You should see the LED blinking with the Morse code for the String

  The circuit:
  Check the Fritzing diagram
  
  created 2016
  by Hrishikesh Date

  This example code is in the public domain.

*/
#define CHARSUPPORTED 37
const int  INTERVAL = 200;
const int  DOT = INTERVAL;
const int  DASH = INTERVAL * 3;
const int  GAPINWORDS = INTERVAL * 7;
const int  GAPINCHARS = INTERVAL * 3;

// constants won't change. Used here to set a pin number :
const int ledPin1 =  5;      // the number of the LED pin
const int ledPin2 =  6;      // the number of the LED pin
const int ledPin3 =  7;      // the number of the LED pin


// Variables will change :
int ledState = LOW;             // ledState used to set the LED


char alpha[CHARSUPPORTED] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                              'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                              'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8',
                              '9', '0', ' '
                            };

String dottie [CHARSUPPORTED] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                                  "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
                                  "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
                                  "-.--", "--..", ".----", "..---", "...--", "....-", ".....",
                                  "-....", "--...", "---..", "----.", "-----", "|"
                                };
bool stringComplete = false;
String inputString = "";

void setup() {
  // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  if (stringComplete) {
    String morsedmessage = toMorse(inputString);

    inputString = "";
    stringComplete = false;

    //Signal the message
    toSignal(morsedmessage);
  }
}

int getindexforelement (char a)
{
  for (int j = 0; j < CHARSUPPORTED; j++)
  {
    if (alpha[j] == a)
    {
      return j;
    }
  }
  return -1;
}
String toMorse(String msg)
{
  String message = msg;
  message.toUpperCase();
  String morse = "";
  for (int j = 0; j < message.length(); j++)
  {
    char chartosearch = message[j];
    int index = getindexforelement (chartosearch);
    if (index >= 0) {
      //Serial.println (dottie[index]);
      //Serial.println (index);
      morse.concat(dottie[index]);
      morse.concat(' ');
    }
    else {
      Serial.println ("Error");
    }
  }
  Serial.println(morse);
  return morse;
}
void signalandwaitdot(int d)
{
  digitalWrite(ledPin1, HIGH);
  delay(d);
  digitalWrite(ledPin1, LOW);
  delay(INTERVAL);
}

void signalandwaitdash(int d)
{
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  delay(d);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);    
  delay(INTERVAL);
}

void toSignal(String message) {
  for (int j = 0; j < message.length(); j++)
  {
    if (message[j] == '.')
    {
      signalandwaitdot(DOT);
    }
    else if (message[j] == '-')
    {
      signalandwaitdash(DASH);
    }
    else if (message[j] == '|') {
      //Don't do any signal just wait
      delay(GAPINWORDS);
    }
    else if (message[j] == ' ') {
      //Don't do any signal just wait
      delay(GAPINCHARS);
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || inChar == '\r' ) {
      stringComplete = true;
    }
    else {
      // add it to the inputString:
      inputString += inChar;
    }
  }
}

