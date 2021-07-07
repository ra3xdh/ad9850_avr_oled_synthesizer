#ifndef BAR_INDICATOR_H
#define BAR_INDICATOR_H

// px,py - position; w,h - width height; size - number of divisions
// value - input from 0 to 0xFF
void render_bar_indicator(uint8_t px, uint8_t py, uint8_t w,
        uint8_t h, uint8_t size, uint8_t value);


#endif

