//#define F_CPU 1000000UL

#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "main.h"
#include "utils.h"
#include "adc.h"
#include "eeprom.h"
#include "lcd.h"
#include "ad9850.h"

#include "sevenseg_digit.h"
#include "bar_indicator.h"

#include "vektor-zeichen.h"

#define MAX_STEP 10000
#define MIN_STEP 10
#define MAX_FREQ 40000000
#define MIN_FREQ 1000000

#define UPD_TMR 50000

#define LED_PIN PORTB4

#define ENC_PORT PORTD
#define ENC_DDR  DDRD
#define ENC_PIN  PIND
#define ENC_B    PIND1
#define ENC_A    PIND3
#define ENC_SW   PIND2
#define DDR_ENC_B  DDD1
#define DDR_ENC_A  DDD3
#define DDR_ENC_SW DDD2

#define BUTTON_BAND_PORT PORTD
#define BUTTON_BAND_PIN  PIND
#define BUTTON_BAND_DDR  DDRD
#define BUTTON_BAND      0

#define BANDS 6

#define SETUP_BFO_LSB 0
#define SETUP_BFO_USB 1
#define SETUP_EXIT    2
#define NO_SETUP      3

#define BAND_ID_80M 0
#define BAND_ID_40M 1
#define BAND_ID_30M 2
#define BAND_ID_20M 3
#define BAND_ID_15M 4
#define BAND_ID_10M 5

#define BAND_PORT PORTC
#define BAND_DDR  DDRC
#define USB_OUT   6
#define PTT_IN    7

char band_names[BANDS][4] = { "80m", "40m", "30m", "20m", "15m", "10m" };
const uint32_t band_freq[BANDS] = { 3500000, 7000000, 10000000, 14000000, 21000000, 28000000 };
char step_names[4][6] = { "10kHz", "1kHz", "100Hz", "10Hz"};


static bool update_freq = true;
static bool flag_update_lcd = false;
static bool hl_digit = false;
static bool setup_mode = false;
uint8_t setup_lvl = NO_SETUP;

static uint16_t step = 100;
static uint8_t step_idx = 2;
static char freq_str[13] = { 0 };
static char s_bar[15] = { 0 };
static char s_swr[15] = { 0 };

static uint32_t *enc_var = 0;

static options_t options;

static vecfont_t font;

void init_gpio();
void init_interrupt();
void init_timer();
void update_lcd();
void load_options();
void save_options();
void update_dds();
void update_band();

void load_options()
{
    EEPROM_read_block(0x00, (uint8_t *) &options, sizeof(options_t));

    if (options.board_id != BOARD_ID) {
        options.board_id = BOARD_ID;
        options.rf_freq = 7040550;
        options.bfo_freq_usb = 8866600;
        options.bfo_freq_lsb = 8864500;
        options.cw_offset = 800;
        options.band_code = BAND_ID_40M;
    }
}

void save_options()
{
    EEPROM_write_block(0x00, (uint8_t *) &options, sizeof(options_t));
}

void init_gpio()
{
    DDRB |= (1<<DDB4);
    ENC_DDR &= ~(1<<DDR_ENC_A);
    ENC_DDR &= ~(1<<DDR_ENC_B);
    ENC_DDR &= ~(1<<DDR_ENC_SW);
    ENC_PORT |= (1<<ENC_A);
    ENC_PORT |= (1<<ENC_B);
    ENC_PORT |= (1<<ENC_SW);

    BUTTON_BAND_DDR &= ~(1<<BUTTON_BAND);
    BUTTON_BAND_PORT |= (1<<BUTTON_BAND);

    BAND_DDR = 0x7F;
    BAND_PORT = 0x80;

}

void init_interrupt()
{
    cli();
    EICRA |= (1 << ISC10); // rising edge
    EICRA |= (1 << ISC11);
    EIMSK |= (1 << INT1); // INT1 enable
    EIFR &= ~(1 << INTF1);
    SREG |= (1 << 7);
    sei();
}

void init_timer()
{
    cli();
    TCNT1 = 62286; // ~ 10 ms @ 1MHz
    TCCR1A = 0x00;
    TCCR1B = (1<<CS11);
    TIMSK1 = (1<< TOIE1);
    sei();

}

void update_lcd()
{

    uint16_t rx_lvl = read_adc(2);
    uint16_t fwd = read_adc(1);
    uint16_t ref = read_adc(0);

    lcd_clear_buffer();

    if (!setup_mode) {

        lcd_gotoxy(7,0);
        lcd_puts("LSB");
        lcd_gotoxy(12,0);
        lcd_puts(step_names[step_idx]);

        lcd_gotoxy(18,0);
        if (fwd > 0x20) {
            lcd_puts("TX");
        } else {
            lcd_puts("RX");
        }

        render_bar_indicator(4,40,122,8,30,rx_lvl);

        swr2str(fwd, ref, s_swr);
        lcd_gotoxy(3,7);
        if (fwd > 0x20) {
            lcd_puts(s_swr);
        } else {
            lcd_puts_p("                  ");
        }


        lcd_gotoxy(0,0);
        lcd_puts(band_names[options.band_code]);


        //render_digit(64,32,8,30,1);
        //render_digit(25,32,6,30,1);
        //lcd_fillRect(64,32,66,48,WHITE);
        //lcd_fillRect(64,32,78,34,WHITE);

    } else {
        switch (setup_lvl) {
            case SETUP_BFO_LSB:
                lcd_gotoxy(0,0);
                lcd_puts("Set BFO LSB freq.");
                break;
            case SETUP_BFO_USB:
                lcd_gotoxy(0,0);
                lcd_puts("Set BFO USB freq.");
                break;
            default: break;
        }


    }

    if (update_freq) {
        update_freq = false;
    }

    freq2str(*enc_var, freq_str);
    font.zoom = 2;
    font.text = freq_str;
    font.start.x = 4;
    font.start.y = 32;
    while (!vecfont_draw_letters(&font));
    font.start.x = 106;
    font.start.y = 32;
    font.zoom = 1;
    font.text = "MHz";
    while (!vecfont_draw_letters(&font));

    lcd_display();

}

void update_band()
{
    options.rf_freq = band_freq[options.band_code];
    update_dds();

    BAND_PORT = 0x80;
    BAND_PORT |= (1 << options.band_code);

    update_freq = true;

    save_options();

}

void update_dds()
{
    uint32_t vfo_freq = options.rf_freq;
    uint32_t bfo_freq = options.bfo_freq_lsb;
    if (options.band_code > BAND_ID_30M) {
        vfo_freq -= bfo_freq;
    } else {
        vfo_freq += bfo_freq;
    }
    float freq1 = (float) vfo_freq;
    dds_update_freq(freq1);

}

ISR (INT1_vect)
{
    cli();
    static uint8_t n = 0;
    n++;
    if (n%2) return;

    if (ENC_PIN & (1 << ENC_B)) {
        if (*enc_var < MAX_FREQ)
            *enc_var += step;
    } else {
        if (*enc_var > MIN_FREQ)
            *enc_var -= step;
    }
    update_dds();
    update_freq = true;
    sei();

}

ISR(TIMER1_OVF_vect)
{
    static uint8_t save_cnt = 0;
    static uint32_t old_rf_freq = 0;

    /*uint16_t rx_lvl = read_adc(2);
    uint16_t fwd = read_adc(1);
    uint16_t rev = read_adc(0);
    update_lcd(rx_lvl, fwd, rev);*/
    flag_update_lcd = true;

    save_cnt++;
    if (save_cnt > 200) {
        PORTB ^= (1 << LED_PIN);
        if (old_rf_freq != options.rf_freq) {
            old_rf_freq = options.rf_freq;
            save_options();
        }
        save_cnt = 0;
    }

    TCNT1 = UPD_TMR;

}

void next_setup()
{
    cli();
    switch (setup_lvl) {
        case SETUP_BFO_LSB:
            enc_var = &options.bfo_freq_lsb;
            break;
        case SETUP_BFO_USB:
            enc_var = &options.bfo_freq_usb;
            break;
        case SETUP_EXIT:
            enc_var = &options.rf_freq;
            setup_mode = false;
            save_options();
            lcd_clear_buffer();
            break;
        default: break;
    }

    update_freq = true;
    update_lcd();
    sei();
}

static void beam_skip(void)
{

}

static void beam_xy (vf_uint_t x, vf_uint_t y)
{
    lcd_drawPixel(x,64-y,WHITE);
}

int main(void)
{
    _delay_ms(500);

    enc_var = &options.rf_freq;

    load_options();
    init_gpio();

    font.zoom = 2;
    font.start.x = 64;
    font.start.y = 32;
    font.text = "";
    font.beam_skip = beam_skip;
    font.beam_xy = beam_xy;

    if ((ENC_PIN & (1<<ENC_SW))==0) {
        cli();
        _delay_ms(1000);
        if ((ENC_PIN & (1<<ENC_SW))==0) {
            setup_mode = true;
            setup_lvl = SETUP_BFO_LSB;
        }
        sei();
    }


    init_interrupt();
    init_timer();
    init_adc();

    dds_setup();
    dds_reset();
    update_dds();

    lcd_init(LCD_DISP_ON);
    lcd_set_contrast(0xFF);
    //lcdClear();


    BAND_PORT = 0x00;
    BAND_PORT |= (1 << options.band_code);

    bool enc_sw_pressed = false;
    bool btn_band_pressed = false;
    hl_digit = false;

    if (setup_mode) next_setup();

    for(;;) {

        if (flag_update_lcd) {
            update_lcd();
            flag_update_lcd = false;
        }

        if ((ENC_PIN & (1<<ENC_SW))==0) {
            if (!enc_sw_pressed) {
                step *= 10;
                step_idx--;
                if (step > MAX_STEP) {
                    step = MIN_STEP;
                    step_idx = 3;
                }
                hl_digit = true;
            }
            enc_sw_pressed = true;
        } else {
            if (enc_sw_pressed) {
                enc_sw_pressed = false;
                hl_digit = false;
            }
        }

        if ((BUTTON_BAND_PIN & (1<<BUTTON_BAND))==0) {
            if (!btn_band_pressed) {
                if (setup_mode) {
                    setup_lvl++;
                    next_setup();
                } else {
                    options.band_code++;
                    if (options.band_code >= BANDS)
                        options.band_code = 0;
                    update_band();

                }
            }
            btn_band_pressed = true;
        } else {
            btn_band_pressed = false;
        }

    }
}
