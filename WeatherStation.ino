#include <Wire.h>
#include <dht.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

// Sea Level Pressure (hPa) at home
#define SENSORS_PRESSURE_SEALEVELHPA 1017.52
#define DHT11_PIN 7

typedef struct {
	float T = 0;
	float H = 0;
	float P = 0;
	int R = 0;
} r_message;

r_message message;

// Rain sensor constants
const int RAIN_PIN = A1;
const int RAIN_DPIN = 2;

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
dht DHT;

// Rain sensor variables
bool is_raining = false;

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup(void)
{
	Serial.begin(9600);
	Serial.println("Testing BMP180...");

	/* Initialise the sensor */
	if (!bmp.begin())
	{
		/* There was a problem detecting the BMP180 */
		Serial.print("No BMP180 detected on I2C bus");
		while (1);
	}

	// Set pin for rain sensor
	Serial.println("Testing rain sensor..."); Serial.println("");
	pinMode(2, INPUT);

	radio.begin(); // Start the NRF24L01
	radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop(void)
{
	// ---------- BMP180 ----------
	/* Get a new sensor event */
	sensors_event_t event;
	bmp.getEvent(&event);

	/* Display the results (barometric pressure is measure in hPa) */
	if (event.pressure)
	{
		/* Display atmospheric pressue in hPa */
		message.P = event.pressure;

		// Redefine SENSORS_PRESSURE_SEALEVELHPA with local SLP
		float temperature;
		bmp.getTemperature(&temperature);
		message.T = temperature;
	}
	else
	{
		Serial.println("Sensor error");
	}

	// ---------- RAIN SENSOR ----------
	is_raining = !(digitalRead(RAIN_DPIN));
	message.R = (is_raining) ? 1 : 0;

	// ---------- DHT11 ----------
	int chk = DHT.read11(DHT11_PIN);
	message.H = DHT.humidity;

	// ---------- RADIO ----------
	radio.write(&message, sizeof(message)); // Send value through NRF24L01

	Serial.println("");
	delay(5000);
}