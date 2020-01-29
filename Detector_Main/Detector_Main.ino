#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 6, 7, 4, 5);

const int sensorPin = A0;    // select the input pin for thermistor
const int redPin = 9;      // selects the pins for the LEDs
const int greenPin = 10;
const int bluePin = 11;

double knownResistance = 1002; //The resistor used for the voltage divider
double sensorValue;  // Variable to store the value coming from the sensor
double roomTemp = 23.0; //Room Temp
double roomResistance = 10780.14; // Resistance at room temp
double beta = 3950;

int max_ADC = 1023;
double currentTemp;
double currentVoltage;
double thermResistance;

void setup() {
  lcd.begin(16, 2);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

double temperature(double currentVoltage) {
  // read the value from the sensor:
  double tempKelvin;
  double tempCelcius;

  sensorValue = analogRead(sensorPin);

  tempKelvin = (beta * roomTemp) /
               (beta + (roomTemp * log(thermResistance / roomResistance)));
  tempCelcius = tempKelvin - 273.15; //convert to celcius

  return tempCelcius; //return it, yay
}
double voltage(double thermResistance) {
  double thermVoltage = 5 * ((thermResistance)/(thermResistance + knownResistance));
  return thermVoltage;
}

void lcdDisplay(double currentTemp, double currentVoltage) {
  lcd.print((String)currentTemp + " C");
  lcd.setCursor(0, 1);
  lcd.print((String)currentVoltage + " Volts");
  delay(1500);
  lcd.clear();
}

void led(double currentTemp) { //configure the temperature ranges for the leds  DON'T CHANGE
  if (currentTemp <= 25) {
    digitalWrite(bluePin, HIGH);
    }
  if (currentTemp <= 50) {
    digitalWrite(greenPin, HIGH);
    }
  if (currentTemp <= 75) {
    digitalWrite(redPin, HIGH);
    }
}

void loop() {
  thermResistance = knownResistance * ((max_ADC / sensorValue) - 1);
  
  currentVoltage = voltage(thermResistance);
  currentTemp = temperature(currentVoltage);
  
  lcdDisplay(currentTemp, currentVoltage);
  led(currentTemp);

}
