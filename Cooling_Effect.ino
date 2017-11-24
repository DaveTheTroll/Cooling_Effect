#include "FastLED.h"

#define NUM_LEDS 24
#define DATA_PIN 11

const byte buttonPin = 13;

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
		heatIndex = 90;
	}

	sunrise();
	FastLED.show();
}

void sunrise()
{
	CRGB color = ColorFromPalette(HeatColors_p, heatIndex);
	fill_solid(leds, NUM_LEDS, color);

	static const uint8_t sunriseLength = 3;	// minutes
	static const uint8_t interval = (sunriseLength * 60) / 256;	// s
		// 256 gradient steps

	EVERY_N_SECONDS(interval)
	{
		if (heatIndex > 0)
		{
			heatIndex--;
		}
	}
}
