const int redPin = 11;     // the number of the LED red pin
const int greenPin = 10;     // the number of the LED green pin
const int bluePin = 9;     // the number of the LED blue pin

const int buttonPin = 13;     // the number of the pushbutton pin
const int sensorPin = A0;     // the number of the LDR sensor pin

int buttonState = 0;         // variable for reading the pushbutton status
int sensorValue = 0;         // variable for reading the LDR sensor

bool lidClosed = false;         // set boolean value to show lid is open

// array for LED colours
unsigned int rgbColour[3];

void setup() {
  // start serial
  Serial.begin(9600);
  
  // Start with LED off, set all LED pins to 0 and call the rgb set colour routine
  rgbColour[0] = 0;
  rgbColour[1] = 0;
  rgbColour[2] = 0;
  setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);

  // set the initial seed to the current LDR sensor value
  randomSeed(analogRead(sensorPin));
  }

void loop() {
  // integer array for the rgb values of the led
  unsigned int rgbColour[3];

  // check button state
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed
  if (buttonState == HIGH) {
    // if the lid is currenly open
    if (lidClosed == false) {
      // this is when the lid is closed, set the LED pins to the numbers generated from the last logged LDR sensor values
      rgbColour[0] = random(0, 255);
      rgbColour[1] = random(0, 255);
      rgbColour[2] = random(0, 255);  
      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      // set the lid to be closed, this is so this does not keep happening while the button is pressed and the led stays the same
      lidClosed = true;
      }
    }
  // check if the pushbutton is pressed
  if (buttonState == LOW) {
    // if the lid is currenly closed
    if (lidClosed == true) {
      // get the current value from the ldr - this will be affected by the led so should always be random
      randomSeed(analogRead(sensorPin));
      Serial.println(analogRead(sensorPin));
      // set the LED pins to the numbers generated from the last logged LDR sensor values
      rgbColour[0] = random(0, 255);
      rgbColour[1] = random(0, 255);
      rgbColour[2] = random(0, 255);
      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      // read LDR again to get another different seed for the next time the lid is closed
      randomSeed(analogRead(sensorPin));
      Serial.println(analogRead(sensorPin));
      // set the lid state to be open
      lidClosed = false;
      }
    }

  delay(1);
  }

// function for setting rgb led colour
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  }