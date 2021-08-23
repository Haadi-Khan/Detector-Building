#include <LiquidCrystal.h>

//pins and LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
const int LED_PINS[3] = {11, 12, 13};
#define DHT_PIN A0

//Variables for Voltage Divider
#define READING_NUMBER 10
const int KNOWN_RESISTANCE = 150;
const float MAX_ADC = 1023.0;
volatile int sensorValue;

void lcdDisplay(float dhtResistance);

void setup() {
	Serial.begin(9600);
	for(int i = 0; i < 3; i++) pinMode(LED_PINS[i],  OUTPUT);
	lcd.begin(16, 2);
}

void loop() {
    float total = 0;
    for(int i = 0; i < READING_NUMBER; i++) total += 5 * analogRead(DHT_PIN) / MAX_ADC;
    float voltage = total/READING_NUMBER;
    lcdDisplay(voltage);
    delay(500);
}

void lcdDisplay(float voltage) {
    lcd.print((String)voltage + " Volts");
    lcd.clear();
}
