#include <stdbool.h>

#include "lcd.h"
#include "sevenseg_digit.h"


static const int digit_array[11][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 0, 0, 1, 1},  // 9
  {0, 0, 0, 0, 0, 0, 0}   // off
};

void render_digit(uint8_t px, uint8_t py,
                  uint8_t digit, uint8_t h, uint8_t t)
{
  // loop through 7 segments
  h = h - t;
  px += t/2;
  py += t/2;
  uint8_t w = h/2;
  for (uint8_t i = 0; i < 7; i++) {
    bool seg_on = digit_array[digit][i];
    // if seg_on is true draw segment
    if (seg_on) {
      switch (i) {
        case 0:
          lcd_fillRect(px+t, py+0, px+w-t, py+t, WHITE); // SEG a
          break;
        case 1:
          lcd_fillRect(px+w-t, py+t, px+w, py+h/2-t/2, WHITE); // SEG b
          break;
        case 2:
          lcd_fillRect(px+w-t, py+h/2+t/2, px+w, py+h-t, WHITE); // SEG c
          break;
        case 3:
          lcd_fillRect(px+t, py+h-t, px+w-t, py+h, WHITE); // SEG d
          break;
        case 4:
          lcd_fillRect(px, py+h/2+t/2, px+t, py+h-t, WHITE); // SEG e
          break;
        case 5:
          lcd_fillRect(px, py+t, px+t, py+h/2-t/2, WHITE); // SEG f
          break;
        case 6:
          lcd_fillRect(px+t,  py+h/2-t/2, px+w-t, py+h/2+t/2, WHITE); // SEG g
          break;
      }
      seg_on = false;
    }
  }
}


