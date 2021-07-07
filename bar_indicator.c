#include <stdint.h>
#include <stdbool.h>

#include "lcd.h"
#include "bar_indicator.h"


void render_bar_indicator(uint8_t px, uint8_t py, uint8_t w,
        uint8_t h, uint8_t size, uint8_t value)
{
    lcd_drawRect(px,py,px+w,py+h,WHITE);
    uint8_t cnt_bar = (value*size)/0xFF;
    uint8_t step = (w-2)/size;
    uint8_t bar_w = step-2;
    uint8_t bar_h = h-4;

    uint8_t sx = px+2;
    uint8_t sy = py+2;
    for (uint8_t i = 0; i < cnt_bar; i++) {
        lcd_fillRect(sx, sy, sx+bar_w, sy+bar_h, WHITE);
        sx +=step;
    }
}

