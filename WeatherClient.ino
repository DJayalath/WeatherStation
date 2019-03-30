#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

#define TOGGLE_PIN 4

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Initialize LCD Display at address 0x27

unsigned long time_last = 0;
const long interval = 10000;

typedef struct {
	float T = 0;
	float H = 0;
	float P = 0;
	int R = -1;
} r_message;

r_message message;
r_message old_message;

bool pressed = false;
bool lcd_on = true;

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

// the setup routine runs once when you press reset:
void setup() {

	Serial.begin(9600);

	lcd.begin(16, 2);
	lcd.setBacklight(HIGH); //Set Back light turn On
	lcd.clear();
	lcd.home();
	lcd.print("Weather Client");
	lcd.setCursor(0, 1);
	lcd.print("Starting...");
	delay(2000);
	lcd.clear();

	pinMode(TOGGLE_PIN, INPUT);
	digitalWrite(TOGGLE_PIN, HIGH);

	radio.begin(); // Start the NRF24L01
	radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive
	radio.startListening(); // Listen to see if information received
}

// the loop routine runs over and over again forever:
unsigned long time_current;
void loop() {
	time_current = millis();
	if (!pressed && digitalRead(TOGGLE_PIN) == LOW)
	{
		if (lcd_on)
		{
			lcd.setBacklight(LOW);
			lcd_on = false;
		}
		else
		{
			lcd.setBacklight(HIGH);
			lcd_on = true;
		}
		pressed = true;
	}
	if (pressed && digitalRead(TOGGLE_PIN) == HIGH)
	{
		pressed = false;
	}

	if (time_current - time_last >= interval) {
		// save the last time you blinked the LED
		time_last = time_current;
		if (radio.available())
		{
			old_message = message;
			radio.read(&message, sizeof(message)); // Read information from the NRF24L01
			if (message.T != old_message.T)
			{
				lcd.setCursor(0, 0); // Move cursor to 0
				lcd.print(String(message.T) + " C ");
			}
			if (message.H != old_message.H)
			{
				lcd.setCursor(8, 0);
				lcd.print(String(message.H) + " %");
			}
			if (message.P != old_message.P)
			{
				lcd.setCursor(0, 1);
				lcd.print(String(message.P) + " hPa ");
			}
			if (message.R != old_message.R)
			{
				lcd.setCursor(12, 1);
				lcd.print((message.R) ? "RAIN" : "DRY ");
			}
		}
		else
		{
			lcd.clear();
			lcd.home();
			lcd.print("Connection lost...");
			old_message = r_message();
		}
	}
}