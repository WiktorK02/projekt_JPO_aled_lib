#include "WS2812.h"
#include <Arduino.h>
#define LED_PIN 18
#define LED_COUNT 16
WS2812_Simple leds(LED_COUNT,LED_PIN, RMT_CHANNEL_0 );

// Function to convert hue to RGB values
void setColorFromHue(int ledIndex, int hue) {
    uint8_t r, g, b;

    // Map hue to RGB (0 - 360 degrees)
    if (hue < 120) {        // Red to Green
        r = (120 - hue) * 255 / 120;
        g = hue * 255 / 120;
        b = 0;
    } else if (hue < 240) { // Green to Blue
        r = 0;
        g = (240 - hue) * 255 / 120;
        b = (hue - 120) * 255 / 120;
    } else {                // Blue to Red
        r = (hue - 240) * 255 / 120;
        g = 0;
        b = (360 - hue) * 255 / 120;
    }

    leds.setPixelColor(ledIndex, r, g, b);
}

void setup() {
    leds.begin();
    leds.setBrightness(100);
}

void loop() {
    static int hueOffset = 0;
    
    // Set rainbow colors across LEDs
    for (int i = 0; i < LED_COUNT; i++) {
        int hue = (i * 36 + hueOffset) % 360; // Each LED is offset in hue
        setColorFromHue(i, hue);
    }
    
    leds.show();
    delay(50);  // Adjust delay for desired speed
    
    hueOffset = (hueOffset + 5) % 360;  // Increment hue offset to animate
}
