#include <LiquidCrystal.h>

#define EPSILON 0.0001;

#define DHT_PIN A0
const int LED_PINS[3] = {11, 12, 13};
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// using a 150Ω resistor as the known
#define READING_NUMBER 10
const float MAX_ADC = 1023.0;
volatile int sensorValue;

// ppm values for leds
float ppm1 = 200;
float ppm2 = 800;

void lcdDisplay(int ppm, float voltage);
void led(int ppm);


void setup() {
	Serial.begin(9600);
	for(int i = 0; i < 3; i++) pinMode(LED_PINS[i],  OUTPUT);
	lcd.begin(16, 2);
}

void loop() {
    float total = 0;
    for(int i = 0; i < READING_NUMBER; i++) total += 5 * analogRead(DHT_PIN) / MAX_ADC;
    float voltage = total/READING_NUMBER;
	int ppm = (int)1; // will have a formula for conversion eventually
    lcdDisplay(ppm, voltage);
	led(ppm);
    delay(500);
}

void lcdDisplay(int ppm, float voltage) {
	lcd.print((String)ppm + " ppm");
	lcd.setCursor(0,1); 
	lcd.print((String)voltage + " Volts");
	lcd.clear();
}

void led(int ppm) {
	if (ppm >= ppm2) {
		digitalWrite(LED_PINS[2], HIGH);
	} else if (ppm < ppm2 && ppm > ppm1) {
		digitalWrite(LED_PINS[1], HIGH);
	} else if (ppm <= ppm1) {
		digitalWrite(LED_PINS[0], HIGH);
	} else {
		digitalWrite(LED_PINS[0], HIGH);
	}
}
