#include "WS2812.h"
#define RMT_CLK_DIV 2

WS2812_Simple::WS2812_Simple(int ledCount, int ledPin, rmt_channel_t rmtChannel)
    : LED_COUNT(ledCount), LED_PIN(ledPin), RMT_CHANNEL(rmtChannel) {
    led_data = new rmt_item32_t[LED_COUNT * 24];
    for (int i = 0; i < LED_COUNT * 24; i++) {
        led_data[i].level0 = 1;
        led_data[i].level1 = 0;
        led_data[i].duration0 = T0L;
        led_data[i].duration1 = T0H;
    }
}

void WS2812_Simple::begin() {
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX((gpio_num_t)LED_PIN, RMT_CHANNEL);
    config.clk_div = RMT_CLK_DIV;
    rmt_config(&config);
    rmt_driver_install(RMT_CHANNEL, 0, 0);
}

void WS2812_Simple::setBrightness(uint8_t b) {
    brightness = b;
}

void WS2812_Simple::setPixelColor(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index < 0 || index >= LED_COUNT) return;

    // Scale RGB values by brightness level
    red = (red * brightness) / 255;
    green = (green * brightness) / 255;
    blue = (blue * brightness) / 255;

    rgbToRmt(red, green, blue, &led_data[index * 24]);
}

void WS2812_Simple::show() {
    rmt_write_items(RMT_CHANNEL, led_data, LED_COUNT * 24, true);
    rmt_wait_tx_done(RMT_CHANNEL, portMAX_DELAY);
}

void WS2812_Simple::rgbToRmt(uint8_t red, uint8_t green, uint8_t blue, rmt_item32_t *data) {
    uint32_t rgb = (green << 16) | (red << 8) | blue;
    for (int i = 0; i < 24; i++) {
        data[i].duration0 = (rgb & (1 << (23 - i))) ? T1H : T0H;
        data[i].duration1 = (rgb & (1 << (23 - i))) ? T1L : T0L;
    }
}
