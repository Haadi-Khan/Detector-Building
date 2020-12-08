#include <LiquidCrystal.h>

//pins and LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#define THERMISTOR_PIN A0
#define RED_LED 11
#define GREEN_LED 12
#define BLUE_LED 13

//Variables for Voltage Divider
const int KNOWN_RESISTANCE = 1002;
const int MAX_ADC = 1023;
float sensorValue;

//variables for thermistor volts, resistance, and temps
float currentTemp, currentVoltage, thermResistance, thermAverage;

//Variables for smoothing the readings
#define READING_NUMBER 10
float readings[READING_NUMBER];
int total;

void setup() {
  Serial.begin(9600);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  lcd.begin(16, 2);

  for(int thisReading = 0; thisReading < READING_NUMBER; thisReading++) {
    readings[thisReading] = 0;
  }
}

void lcdDisplay(double thermResistance, double currentVoltage) {
  lcd.print((String)thermResistance + " Ohms");
  lcd.setCursor(0, 1); //move to second row
  lcd.print((String)currentVoltage + " Volts");
  delay(1000);
  lcd.clear();
}

void loop() {
  //Voltage Divider Equation
  thermResistance = KNOWN_RESISTANCE * ((MAX_ADC/sensorValue) - 1);

  for (int i = 0; i >= READING_NUMBER; i++) {
    total = total - readings[i];
    readings[i] = analogRead(THERMISTOR_PIN);
  }

  float thermResistanceAverage = total/READING_NUMBER;
  lcdDisplay(thermResistanceAverage, currentVoltage);

  delay(100);
}
