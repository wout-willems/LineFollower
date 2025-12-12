// Pin definities
int AIN1 = 3;
int AIN2 = 2;
int PWMA = 5;

int BIN1 = 4;
int BIN2 = 7;
int PWMB = 6;

int STBY = 8;

// Maximale PWM zodat motoren effectief ~6V krijgen op 7.4V voeding
// Je kan hiermee "power reduceren"
int MAX_PWM = 100;  // 0–255

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);  // driver activeren
}

void loop() {


  for (int i = 0; i <= 150; i++) {

    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, i);

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, i);
    delay(10);
  }

  delay(1000);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

  delay(3000);







  for (int i = 0; i <= 150; i++) {

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, i);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, i);
    delay(10);
  }

    delay(1000);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

  delay(3000);







  for (int i = 0; i <= 70; i++) {

    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, i);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, i);
    delay(10);
  }

    delay(1000);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

  delay(3000);








  for (int i = 0; i <= 70; i++) {

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, i);

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, i);
    delay(10);
  }

    delay(1000);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

  delay(3000);
}
