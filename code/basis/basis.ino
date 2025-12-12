#include <EEPROM.h>

// ---------- PIN DEFINITIES ----------
int MotorLeftForward = 3;
int MotorLeftBackward = 2;
int MotorLeftPWM = 5;

int MotorRightForward = 4;
int MotorRightBackward = 7;
int MotorRightPWM = 6;

int STBY = 8;

const int buttonPin = 9;
const int ledPin = 10;

// ---------- SENSOR PINNEN ----------
const int sensor[] = { A0, A1, A2, A3, A4, A5, A6, A7 };
int normalised[8];
const float sensorSpacing = 9.525; // afstand tussen sensoren in mm

// ---------- PARAMETERS ----------
int basePower = 25;      // basissnelheid motoren
float kp = 1.2;           // proportionele factor
float ki = 0;          // integrerende factor
float kd = 0;           // differentiële factor

int black[8];             // zwarte referentiewaarden
int white[8];             // witte referentiewaarden

bool run = true;         // of de robot mag rijden

// PID variabelen
float iTerm = 0;
float lastError = 0;

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);

  // Motor pins
  pinMode(MotorLeftForward, OUTPUT);
  pinMode(MotorLeftBackward, OUTPUT);
  pinMode(MotorLeftPWM, OUTPUT);
  pinMode(MotorRightForward, OUTPUT);
  pinMode(MotorRightBackward, OUTPUT);
  pinMode(MotorRightPWM, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // Sensoren
  for(int i=0; i<8; i++) pinMode(sensor[i], INPUT);

  // EEPROM uitlezen
  EEPROM.get(0, black);
  EEPROM.get(sizeof(black), white);

  Serial.println("Linefollowing PID start. Gebruik 'calibrate black', 'calibrate white', 'run' of 'stop'.");
}

// ---------- LOOP ----------
void loop() {
  // ----- Seriële commando's uitlezen -----
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if(command == "calibrate black") {
      Serial.println("Calibrating black...");
      for(int i=0; i<8; i++){
        black[i] = analogRead(sensor[i]);
      }
      EEPROM.put(0, black);
      Serial.println("Black calibration done.");
    }
    else if(command == "calibrate white") {
      Serial.println("Calibrating white...");
      for(int i=0; i<8; i++){
        white[i] = analogRead(sensor[i]);
      }
      EEPROM.put(sizeof(black), white);
      Serial.println("White calibration done.");
    }
    else if(command == "run") {
      run = true;
      digitalWrite(ledPin, HIGH);
      Serial.println("Robot is running!");
    }
    else if(command == "stop") {
      run = false;
      digitalWrite(ledPin, LOW);
      Serial.println("Robot stopped!");
      // Zet motoren direct uit
      analogWrite(MotorLeftPWM, 0);
      analogWrite(MotorRightPWM, 0);
      digitalWrite(MotorLeftForward, LOW);
      digitalWrite(MotorLeftBackward, LOW);
      digitalWrite(MotorRightForward, LOW);
      digitalWrite(MotorRightBackward, LOW);
      iTerm = 0; // reset integratie
      lastError = 0;
    }
  }

if(digitalRead(buttonPin) == LOW) {
      run = true;
      digitalWrite(ledPin, HIGH);
      Serial.println("Robot is running!");
    }
    else if(digitalRead(buttonPin) == HIGH) {
      run = false;
      digitalWrite(ledPin, LOW);
      Serial.println("Robot stopped!");
      // Zet motoren direct uit
      analogWrite(MotorLeftPWM, 0);
      analogWrite(MotorRightPWM, 0);
      digitalWrite(MotorLeftForward, LOW);
      digitalWrite(MotorLeftBackward, LOW);
      digitalWrite(MotorRightForward, LOW);
      digitalWrite(MotorRightBackward, LOW);
      iTerm = 0; // reset integratie
      lastError = 0;
    }


  if(!run) return; // stop als run = false

  // ----- Sensoren normaliseren -----
  for(int i=0; i<8; i++){
    normalised[i] = map(analogRead(sensor[i]), black[i], white[i], 0, 1000);
  }

  // ----- Positie berekenen in mm -----
  float weightedPosition = 0;
  int sum = 0;
  for(int i=0; i<8; i++){
    int value = 1000 - normalised[i]; // zwart = hoog
    weightedPosition += i * value;
    sum += value;
  }

  float position_mm = 0;
  if(sum > 0) {
    float centerIndex = weightedPosition / sum;
    position_mm = (centerIndex - 3.2) * sensorSpacing; // gecentreerd rond 0 mm
  }

  float error = -position_mm;

  // ----- PID berekening -----
  iTerm += ki * error;
  iTerm = constrain(iTerm, -200, 200); // voorkom integrale windup
  float dTerm = kd * (error - lastError);
  lastError = error;

  float correction = kp * error + iTerm + dTerm;

  int powerLeft = basePower + correction;
  int powerRight = basePower - correction;

  // Limiteer motorvermogen
  powerLeft = constrain(powerLeft, 0, 200);
  powerRight = constrain(powerRight, 0, 200);

  // ----- Motoren aansturen -----
  if(powerLeft >= 0){
    digitalWrite(MotorLeftForward, HIGH);
    digitalWrite(MotorLeftBackward, LOW);
  } else {
    digitalWrite(MotorLeftForward, LOW);
    digitalWrite(MotorLeftBackward, HIGH);
    powerLeft = -powerLeft;
  }
  analogWrite(MotorLeftPWM, powerLeft);

  if(powerRight >= 0){
    digitalWrite(MotorRightForward, HIGH);
    digitalWrite(MotorRightBackward, LOW);
  } else {
    digitalWrite(MotorRightForward, LOW);
    digitalWrite(MotorRightBackward, HIGH);
    powerRight = -powerRight;
  }
  analogWrite(MotorRightPWM, powerRight);

  delay(10);
}
