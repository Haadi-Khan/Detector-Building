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
  
  tempKelvin = (beta * roomTemp) /
               (beta + (roomTemp * log(thermResistance / roomResistance))); //Use the formula. This is pretty garbage
               
  tempCelcius = tempKelvin - 273.15; //convert to celcius


  double values[] = {tempCelcius, thermVoltage}; //the values we are returning         //This is what you have to change, everything else is fine
  return values; //please help with returning this data
}

void lcdDisplay(double currentTemp, double currentVoltage) { //display the info DON'T CHANGE
  String mrPage = (String) currentTemp; 
  String mrBouklas = (String) currentVoltage;
  lcd.print(mrPage + " Ohms");
  lcd.setCursor(0, 1);
  lcd.print(mrBouklas + " Volts");
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
  double * oof = temperature(); //please fix this accordingly

  
  currentTemp = oof[0];
  currentVoltage = oof[1]; //get the temp and voltage, Mark don't change this unless you have to

  lcdDisplay(currentTemp, currentVoltage);
  //led(currentTemp);
}
