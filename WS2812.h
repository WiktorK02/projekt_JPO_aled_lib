#ifndef WS2812_H
#define WS2812_H

#include <driver/rmt.h>

#define RMT_CHANNEL RMT_CHANNEL_0  // RMT channel to use
// Timing definitions for WS2812 (in 12.5ns ticks)
#define T0H 14   // "0" bit high time
#define T0L 34   // "0" bit low time
#define T1H 34   // "1" bit high time
#define T1L 14   // "1" bit low time

class WS2812_Simple {
public:
    WS2812_Simple(int ledCount, int ledPin, rmt_channel_t rmtChannel);
    void begin();
    void setPixelColor(int index, uint8_t red, uint8_t green, uint8_t blue);
    void setBrightness(uint8_t brightness);
    void show();

private:
    int LED_COUNT;
    int LED_PIN;
    rmt_channel_t RMT_CHANNEL;
    rmt_item32_t* led_data;  // Dynamically allocated for LED_COUNT * 24 bits
    uint8_t brightness = 255;
    void rgbToRmt(uint8_t red, uint8_t green, uint8_t blue, rmt_item32_t *data);
};

#endif
