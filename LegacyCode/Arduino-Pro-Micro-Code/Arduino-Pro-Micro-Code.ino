#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick;

// Define pin assignments
const int joyXPin = A0;
const int joyYPin = A1;
const int buttonPins[] = {2, 3, 4, 5};

int mappedX = 0;
int mappedY = 0;

int unmappedX = 0;
int unmappedY = 0;

// const int numReadings = 5;
// int readings[numReadings];      // array to store sensor readings
// int index = 0;                  // current index in the array
// int total = 0;                  // running total of readings
// int average = 0;                // smoothed sensor value

void setup() {
  Joystick.begin();

  Serial.begin(9600);

  // Set up button pins with pull-up resistors
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  // Read joystick values
  unmappedX = analogRead(joyXPin);
  unmappedY = analogRead(joyYPin);

  if (unmappedX >= 514) {
    mappedX = map(unmappedX, 385, 514, 0, 510);
  } else if (unmappedX <= 525) {
    mappedX = map(unmappedX, 525, 850, 512, 1023);
  } else {
    mappedX = 511;
  }

  if (unmappedY >= 510) {
    mappedY = map(unmappedY, 200, 510, 0, 510);
  } else if (unmappedY <= 520) {
    mappedY = map(unmappedY, 520, 695, 512, 1023);
  } else {
    mappedY = 511;
  }
  

  // int xVal = analogRead(joyXpin);
  // int yVal = analogRead(joyYPin);

  // Read button states
  int buttonStates[4];
  for (int i = 0; i < 4; i++) {
    buttonStates[i] = !digitalRead(buttonPins[i]);
    Joystick.setButton(i, buttonStates[i]);
  }

  // Rest of the code handling joystick and button states
  Joystick.setXAxis(unmappedX);
  Joystick.setYAxis(mappedY);

  Serial.println(unmappedX);

  delay(100);
}

// int smoothXAxis(int axisValue) {
//   total = total - readings[index] + axisValue;  // update total with new reading
//   readings[index] = axisValue;                   // store the new reading
//   index = (index + 1) % numReadings;               // move to the next index
//   average = total / numReadings;                   // calculate the average
// }

// int smoothYAxis(int axisValue) {
//   total = total - readings[index] + axisValue;  // update total with new reading
//   readings[index] = axisValue;                   // store the new reading
//   index = (index + 1) % numReadings;               // move to the next index
//   average = total / numReadings;                   // calculate the average
// }
