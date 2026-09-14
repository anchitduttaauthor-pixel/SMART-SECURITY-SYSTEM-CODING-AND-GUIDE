#include <Keypad.h>

// --- PIN DEFINITIONS ---
const int trigPin = A1; // HC-SR04 Trigger pin
const int echoPin = A2; // HC-SR04 Echo pin
const int buzzerPin = 10; // Passive Buzzer I/O pin

// --- KEYPAD CONFIGURATION (4x4) ---
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- PASSWORD & SECURITY CONFIGURATION ---
const String masterCode = "1234"; // Set your default master passcode here
String inputBuffer = "";

// --- STATE TRACKING VARIABLES ---
bool systemArmed = true;
bool physicalBreach = false;
bool wrongCodeAlarm = false;
bool doorOpenedWhileDisarmed = false;

unsigned long unlockTime = 0;
const unsigned long AUTO_RELOCK_TIMEOUT = 10000; // 10 seconds auto-rearm timeout

// --- BEEP-BEEP TIMING VARIABLES ---
unsigned long previousBuzzerMillis = 0;
bool buzzerState = false;
const long beepInterval = 150; // Speed of the beep (150ms ON, 150ms OFF)

// --- FUNCTION TO MEASURE DISTANCE ---
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) return 999.0; // No echo received
  return duration * 0.0343 / 2.0; // Convert time to cm
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);
}

void loop() {
  // 1. Read Distance and Determine Door Position
  float distance = getDistance();
  bool isDoorClosed = (distance >= 1.5 && distance <= 4.5);

  // 2. Read Keypad Input
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      if (inputBuffer == masterCode) {
        systemArmed = false;
        wrongCodeAlarm = false;
        physicalBreach = false;
        doorOpenedWhileDisarmed = false;
        unlockTime = millis(); // Start 10-second countdown
        noTone(buzzerPin);
      } else {
        wrongCodeAlarm = true; // Wrong password entered -> trigger alarm
      }
      inputBuffer = ""; // Reset input after evaluation
    }
    else if (key == '*') {
      inputBuffer = ""; // Clear buffer
    }
    else {
      if (inputBuffer.length() < 10) {
        inputBuffer += key;
      }
    }
  }

  // 3. Security Logic Execution
  if (systemArmed) {
    doorOpenedWhileDisarmed = false;

    // Breach detection: Door pried or pulled open without disarming
    if (!isDoorClosed) {
      physicalBreach = true;
    } else {
      physicalBreach = false; // Door pushed shut back into slot -> silences breach alarm
    }
  } 
  else {
    // SYSTEM DISARMED (Authorized Access)
    if (!isDoorClosed) {
      doorOpenedWhileDisarmed = true;
    }

    // Condition A: User opened door and then closed it -> Auto re-arm
    if (doorOpenedWhileDisarmed && isDoorClosed) {
      systemArmed = true;
      doorOpenedWhileDisarmed = false;
    }

    // Condition B: User unlocked but never touched the door within 10 seconds -> Auto re-arm
    if (!doorOpenedWhileDisarmed && (millis() - unlockTime >= AUTO_RELOCK_TIMEOUT)) {
      systemArmed = true;
    }
  }

  // 4. CENTRAL ALARM & BUZZER LOGIC (Pulsing Beep-Beep Effect)
  if (wrongCodeAlarm || (systemArmed && physicalBreach)) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousBuzzerMillis >= beepInterval) {
      previousBuzzerMillis = currentMillis;
      buzzerState = !buzzerState;
      if (buzzerState) {
        tone(buzzerPin, 1200); // 1200Hz is a piercing high pitch alert
      } else {
        noTone(buzzerPin); // Silent gap between beeps
      }
    }
  } 
  else {
    noTone(buzzerPin);
    buzzerState = false;
  }

  delay(50); // Small loop stabilization delay
}