#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick;

// Button pins collection
const int buttonPins[] = { 15, 9, 10, 14, 16 };
const int buttonPinsSize = 5;

// Button state and previous state collections
bool buttonStates[] = { LOW, LOW, LOW, LOW, LOW};
const int buttonStatesSize = 5;

bool lastButtonStates[] = { HIGH, HIGH, HIGH, HIGH, HIGH};
const int lastButtonStatesSize = 5;

// Set the smoothness of the readings (Higher = smoother but less responsive)
const int smoothness = 8;

// Main program setup
void setup() {
  Joystick.begin();

  // Serial.begin(9600);

  // Set up button pins as pullup inputs
  for (int i = 0; i < buttonPinsSize; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

// Main program loop
void loop() {
  int smoothXData = smoothAnalogReadX(A0);
  int smoothYData = smoothAnalogReadY(A1);
  int smoothZData = smoothAnalogReadZ(A3);
  int smoothThrottleData = smoothAnalogReadThrottle(A2);

  for (int i = 0; i < buttonStatesSize; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]);
  }

  for (int i = 0; i < buttonPinsSize; i++) {
    buttonChecker(i);
  }


  int refreshRate = 200; // Change this number to whatever 'fps' or refresh rate (times per second) you want the joystick to update
  delay(1000 / refreshRate);

  //Send the X axis through the joystick interface
  if (smoothXData < 560) {
    Joystick.setXAxis(map(smoothXData, 270, 560, 0, 510));
  } else if (smoothXData > 610) {
    Joystick.setXAxis(map(smoothXData, 610, 842, 512, 1023));
  } else {
    Joystick.setXAxis(511);
  }

  //Send the Y axis through the joystick interface
  if (smoothYData < 542) {
    Joystick.setYAxis(map(smoothYData, 310, 542, 1023, 512));
  } else if (smoothYData > 600) {
    Joystick.setYAxis(map(smoothYData, 600, 770, 510, 0));
  } else {
    Joystick.setYAxis(511);
  }

  //Send the Z axis through the joystick interface
  if (smoothZData < 509) {
    Joystick.setZAxis(map(smoothZData, 0, 509, 0, 510));
  } else if (smoothZData > 513) {
    Joystick.setZAxis(map(smoothZData, 513, 1023, 510, 1023));
  } else {
    Joystick.setZAxis(511);
  }

  //Send the Throttle axis through the joystick interface
  if (smoothThrottleData < 495) {
    Joystick.setThrottle(map(smoothThrottleData, 0, 495, 1023, 512));
  } else if (smoothThrottleData > 499) {
    Joystick.setThrottle(map(smoothThrottleData, 499, 1023, 510, 0));
  } else {
    Joystick.setThrottle(511);
  }
}

// Buttonchecker checks for the inputted button's state
void buttonChecker(int button) {
  if (buttonStates[button] == LOW && lastButtonStates[button] == HIGH) {
    lastButtonStates[button] = LOW;
    Joystick.pressButton(button);
  }
  if (buttonStates[button] == HIGH && lastButtonStates[button] == LOW) {
    lastButtonStates[button] = HIGH;
    Joystick.releaseButton(button);
  }
}

// Read values smoothly
float smoothAnalogReadX(int pin) {
  const int numReadings = smoothness; // More = smoother but less responsive
  static int readings[numReadings];   // Array to store readings
  static int index = 0;               // Index for the readings array
  static int total = 0;               // Running total of readings

  total = total - readings[index];    // Subtract the oldest reading
  readings[index] = analogRead(pin);  // Read from the sensor
  total = total + readings[index];    // Add the new reading
  index = (index + 1) % numReadings;  // Move to the next index

  return total / numReadings;         // Return the average
}

float smoothAnalogReadY(int pin) {
  const int numReadings = smoothness; // More = smoother but less responsive
  static int readings[numReadings];   // Array to store readings
  static int index = 0;               // Index for the readings array
  static int total = 0;               // Running total of readings

  total = total - readings[index];    // Subtract the oldest reading
  readings[index] = analogRead(pin);  // Read from the sensor
  total = total + readings[index];    // Add the new reading
  index = (index + 1) % numReadings;  // Move to the next index

  return total / numReadings;         // Return the average
}

float smoothAnalogReadZ(int pin) {
  const int numReadings = smoothness; // More = smoother but less responsive
  static int readings[numReadings];   // Array to store readings
  static int index = 0;               // Index for the readings array
  static int total = 0;               // Running total of readings

  total = total - readings[index];    // Subtract the oldest reading
  readings[index] = analogRead(pin);  // Read from the sensor
  total = total + readings[index];    // Add the new reading
  index = (index + 1) % numReadings;  // Move to the next index

  return total / numReadings;         // Return the average
}

float smoothAnalogReadThrottle(int pin) {
  const int numReadings = smoothness; // More = smoother but less responsive
  static int readings[numReadings];   // Array to store readings
  static int index = 0;               // Index for the readings array
  static int total = 0;               // Running total of readings

  total = total - readings[index];    // Subtract the oldest reading
  readings[index] = analogRead(pin);  // Read from the sensor
  total = total + readings[index];    // Add the new reading
  index = (index + 1) % numReadings;  // Move to the next index

  return total / numReadings;         // Return the average
}
