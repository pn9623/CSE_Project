#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// PIR Sensor and Buzzer
#define PIR_SENSOR 2
#define BUZZER 3

const String PASSWORD = "6969";
String inputPassword = "";

void setup() {
  pinMode(PIR_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Security System");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {
  int motionDetected = digitalRead(PIR_SENSOR);
  if (motionDetected == HIGH) {
    digitalWrite(BUZZER, HIGH);
    activateAlarm();
    waitForPassword();
  } else {
    digitalWrite(BUZZER, LOW);
  }
}

void activateAlarm() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motion Detected!");
  lcd.setCursor(0, 1);
  lcd.print("Enter Password:");
  tone(BUZZER, 1000);
  Serial.println("Motion Detected");
}

void waitForPassword() {
  inputPassword = "";
  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {
        if (inputPassword == PASSWORD) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Access Granted");
          Serial.println("Access Granted");
          delay(1000);
          resetSystem();
          return;
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong Password!");
          Serial.println("Wrong Password");
          delay(1000);
          activateAlarm();
          inputPassword = "";
        }
      } else if (key == '*') {
        inputPassword = "";
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("Enter Password:");
      } else {
        inputPassword += key;
        lcd.setCursor(inputPassword.length() - 1, 1);
        lcd.print("*");
      }
    }
  }
}

void resetSystem() {
  noTone(BUZZER);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("!!!RUN!!!ASAP!!!");
  delay(2000);
  lcd.clear();
}