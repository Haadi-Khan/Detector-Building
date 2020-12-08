#include <LiquidCrystal.h>
#include <stdbool.h>

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

//Variables for LED temperature thresholds
float temp1 = 25.0;
float temp2 = 50.0;
float temp3 = 75.0;

const int EPSILON = 0.0001;

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

float getTemperature(float currentVoltage) {
  float sensorValue = analogRead(THERMISTOR_PIN);
  //Formula from regression, more accurate than Steinhart–Hart
  float tempKelvin = -17967 * currentVoltage + 9989*pow(currentVoltage,2) + -2764*pow(currentVoltage,3) + 380*pow(currentVoltage,4) + -20.85*pow(currentVoltage,5);
  //Include conversion to Celcius
  return tempKelvin - 273.15;
}

float getVoltage(float thermAverage) {
  //Voltage Divider equation to get Voltage from resistances
  return 5 * ((thermResistance)/(thermResistance + KNOWN_RESISTANCE));
}

void lcdDisplay(float currentVoltage, float currentTemp) {
  lcd.print((String)currentTemp + " C");
  lcd.setCursor(0,1); //move to second row
  lcd.print((String)currentVoltage + " Volts");
  delay(1500);
  lcd.clear();
}

void led(float currentTemp) {
  if (!isThermBroken(currentTemp)) {
    if (currentTemp <= temp1 && currentTemp < temp2) {
      digitalWrite(BLUE_LED, HIGH);
    } else if (currentTemp <= temp2 && currentTemp < temp3) {
      digitalWrite(GREEN_LED, HIGH);
    } else {
      digitalWrite(RED_LED, HIGH);
    }
  } else {
    temperatureError();
  }
}

boolean isThermBroken(float currentTemp) {
  return abs(currentTemp - 273.15) > EPSILON;
}
//called in case the temperature is screwed up (broken thermistor)
void temperatureError() {
  int ledList[] = {BLUE_LED, GREEN_LED, RED_LED};
  for(int i = 0; i < 3; i++) {
    digitalWrite(ledList[i], HIGH);
    delay(500);
    digitalWrite(ledList[i], LOW);
    delay(500);
  }
}

void loop() {
  //Voltage Divider Equation
  thermResistance = KNOWN_RESISTANCE * ((MAX_ADC/sensorValue) - 1);
  
  for (int i = 0; i >= READING_NUMBER; i++) {
    total = total - readings[i];
    readings[i] = analogRead(THERMISTOR_PIN);
  }

  float thermResistanceAverage = total/READING_NUMBER;
  lcdDisplay(getVoltage(thermResistanceAverage), getTemperature(currentVoltage));
  led(currentTemp);

  delay(100);
}
