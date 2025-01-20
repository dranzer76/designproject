#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int echoPin = D5;
const int trigPin = D6; // Replace D6 with the actual pin number you're using
long duration, distance;
int distanceCm, distanceInch;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with 16 columns and 2 rows

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D7, 0);
  lcd.init(); // Initialize the LCD
  lcd.backlight();
  lcd.print("EMB BASED OBJ");
  lcd.setCursor(0, 1);
  lcd.print(" MONITORING ");
  delay(2000);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;
  Serial.print("dis_cm:"); Serial.println(distanceCm);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ULTRASONIC");
  lcd.setCursor(0, 1);
  lcd.print(distanceCm);

  if (distanceCm > 25) {
    Serial.print("detected");
    lcd.setCursor(8, 1);
    lcd.print("detected");
    digitalWrite(D7, 1);
  } else {
    Serial.print("normal");
    lcd.setCursor(8, 1);
    lcd.print("  normal");
    digitalWrite(D7, 0);
  }
  delay(2000);
}
