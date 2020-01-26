/** 
 *  Written by Haadi Khan and Mark Shapiro
 *  Half Hollow Hills High School East C
 *  Team #
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 6, 7, 4, 5); //The  LCD display

const int sensorPin = A0;    // select the input pin for thermistor
const int redPin = 9;      // selects the pins for the LEDs
const int greenPin = 10;
const int bluePin = 11;

double sensorValue;  // Variable to store the value coming from the sensor
double knownResistance = 1002; //The resistor used for the voltage divider
double roomTemp = 293.15; //Room Temp in Kelvin
double roomResistance = 10780.14; // Resistance at room temp
double beta = 3950.0; //Taken from amazon description

int max_ADC = 1023; //use this for the ADC 
double currentTemp;
double currentVoltage;

void setup() { //DON'T CHANGE
  lcd.begin(16, 2);
  pinMode(sensorPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}


double * temperature() { //how can I return an array?
  double tempKelvin;
  double tempCelcius;

  sensorValue = analogRead(sensorPin);

  //ADC time
  double thermResistance = knownResistance * ((max_ADC / sensorValue) - 1); //now we have the thermistor resistance, yay
  double thermVoltage = 5 * ((thermResistance)/(thermResistance + knownResistance));
  return thermVoltage; //please help with returning this data
}

void lcdDisplay(double currentVoltage) { //display the info DON'T CHANGE
  String mrBouklas = (String) currentVoltage;
  lcd.print(mrBouklas + " Volts");
  delay(1500);
  lcd.clear();
}

void loop() {
  double oof = temperature(); //please fix this accordingly
  currentVoltage = oof;

  lcdDisplay(currentVoltage);
}
