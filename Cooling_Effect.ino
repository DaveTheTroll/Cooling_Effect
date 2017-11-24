#include "FastLED.h"

#define NUM_LEDS 24
#define DATA_PIN 11

const byte buttonPin = 13;
const uint8_t maxHeatIndex = 90;

CRGB leds[NUM_LEDS];
static uint8_t heatIndex = 0;

void setup()
{
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
	if (digitalRead(buttonPin) == LOW && heatIndex == 0)
	{
		heatIndex = maxHeatIndex;
	}

	sunrise();
	FastLED.show();
}

void sunrise()
{
	CRGB color = ColorFromPalette(HeatColors_p, heatIndex);
	fill_solid(leds, NUM_LEDS, color);

	static const uint8_t sunrise_minutes = 3;
	static const uint8_t interval_ms = (sunrise_minutes * 60 * 1000) / maxHeatIndex;

	EVERY_N_MILLISECONDS(interval_ms)
	{
		if (heatIndex > 0)
		{
			heatIndex--;
		}
	}
}
