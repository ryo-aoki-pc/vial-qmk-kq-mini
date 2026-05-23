
#include "ws2812.h"
#include "apidef.h"
#include "color.h"

_Static_assert(sizeof(ws2812_led_t) == sizeof(bmp_api_led_t), "Invalid size");

static ws2812_led_t ws2812_leds[WS2812_LED_COUNT];

void ws2812_init(void) {}

void ws2812_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= WS2812_LED_COUNT) return;
    ws2812_leds[index].r = red;
    ws2812_leds[index].g = green;
    ws2812_leds[index].b = blue;
#ifdef WS2812_RGBW
    ws2812_rgb_to_rgbw(&ws2812_leds[index]);
#endif
}

void ws2812_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < WS2812_LED_COUNT; i++) {
        ws2812_set_color(i, red, green, blue);
    }
}

void ws2812_flush(void) {
    BMPAPI->ws2812.setleds_pin((bmp_api_led_t *)ws2812_leds, WS2812_LED_COUNT, BMPAPI->app.get_config()->led.pin);
}
