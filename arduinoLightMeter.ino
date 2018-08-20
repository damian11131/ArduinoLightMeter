#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <math.h>

#define led1 6
#define led2 5
#define led3 4
#define led4 3
#define led5 2

#define photoresistorPin A3

#define lcdAddr 0x38

float lastSensorValue = 0;
LiquidCrystal_PCF8574 lcd(lcdAddr);

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(photoresistorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Wire.begin();
  Wire.beginTransmission(lcdAddr);

  lcd.begin(16, 2);
  lcd.home();
  lcd.setBacklight(255);

  Serial.begin(9600);
}

void loop() {
  float sensorValue = analogRead(photoresistorPin) * (5.0 / 1023.0);
  float diff = fabs(sensorValue - lastSensorValue);

  if (diff >= 0.05) {
    Serial.println(sensorValue);
    updateVoltageOnLcd(sensorValue);
    turnLeds(sensorValue);
    lastSensorValue = sensorValue;
  }

}

void turnLeds(float voltage) {
  if (voltage <= 1) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  else if (voltage <= 2) {
    digitalWrite(led2, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  else if (voltage <= 3) {
    digitalWrite(led3, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  else if(voltage <= 4) {
    digitalWrite(led4, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led5, LOW);
  }
  else {
    digitalWrite(led5, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);  
  }
}

void updateVoltageOnLcd(float voltage) {
  String text = "Voltage:" + String(voltage) + "V";
  lcd.clear();
  lcd.print(text);
}
