#define F_CPU 1000000UL

#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "main.h"
#include "utils.h"
#include "lcd_library.h"
#include "ad9850.h"

#define MAX_STEP 10000
#define MIN_STEP 10

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

char band_names[BANDS][3] = { "80", "40", "30", "20", "15", "10" };
const uint32_t band_freq[BANDS] = { 3500000, 7000000, 10000000, 14000000, 21000000, 28000000 };


static bool update_freq = true;

static uint16_t step = 100;
static char freq_str[13] = { 0 };

static options_t options;

void init_gpio();
void init_interrupt();
void init_timer();
void update_lcd();
void load_options();
void update_dds();
void update_band();

void load_options()
{
    options.rf_freq = 7040550;
    options.bfo_freq_usb = 8866600;
    options.bfo_freq_lsb = 8864500;
    options.cw_offset = 800;
    options.band_code = BAND_ID_40M;
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
    TCNT1 = 64286; // ~ 10 ms @ 1MHz
    TCCR1A = 0x00;
    TCCR1B = (1<<CS11);
    TIMSK1 = (1<< TOIE1);
    sei();

}

void update_lcd()
{
    if (update_freq) {
        lcdGotoXY(1,0);
        lcdPuts(band_names[options.band_code]);
        lcdGotoXY(0,8);
        freq2str(options.rf_freq, freq_str);
        lcdPuts(freq_str);
        update_freq = false;
    }

}

void update_band()
{
    options.rf_freq = band_freq[options.band_code];
    update_dds();

    BAND_PORT = 0x80;
    BAND_PORT |= (1 << options.band_code);

    update_freq = true;

}

void update_dds()
{
    uint32_t vfo_freq = options.rf_freq;
    uint32_t bfo_freq = options.bfo_freq_lsb;
    if (options.band_code >= BAND_ID_30M) {
        vfo_freq -= bfo_freq;
    } else {
        vfo_freq += bfo_freq;
    }
    float freq1 = (float) vfo_freq;
    dds_update_freq(freq1);

}

ISR (INT1_vect)
{
    if ((ENC_PIN & (1 << ENC_B)) == 0) {
        options.rf_freq += step;
        PORTB |= (1 << LED_PIN);
    } else {
        options.rf_freq -= step;
        PORTB &= ~(1 << LED_PIN);
    }
    update_dds();
    update_freq = true;
}

ISR(TIMER1_OVF_vect)
{
    update_lcd();
    TCNT1 = 64286;
}

int main(void)
{
    _delay_ms(500);


    load_options();
    init_gpio();
    init_interrupt();
    init_timer();

    dds_setup();
    dds_reset();
    update_dds();

    lcdInit();
    lcdClear();
    lcdGotoXY(0,0);
    lcdPuts("RX");
    lcdGotoXY(0,4);
    lcdPuts("LSB");

    BAND_PORT = 0x00;
    BAND_PORT |= (1 << options.band_code);

    bool enc_sw_pressed = false;
    bool btn_band_pressed = false;

    for(;;) {

        //_delay_ms(10);

        if ((ENC_PIN & (1<<ENC_SW))==0) {
            if (!enc_sw_pressed) {
                step *= 10;
                if (step > MAX_STEP) step = MIN_STEP;
            }
            enc_sw_pressed = true;
        } else {
            enc_sw_pressed = false;
        }

        if ((BUTTON_BAND_PIN & (1<<BUTTON_BAND))==0) {
            if (!btn_band_pressed) {
                options.band_code++;
                if (options.band_code >= BANDS)
                    options.band_code = 0;
                update_band();
            }
            btn_band_pressed = true;
        } else {
            btn_band_pressed = false;
        }


        /*PORTB |= (1 << LED_PIN);
        _delay_ms(1000);
        PORTB &= ~(1 << LED_PIN);
        _delay_ms(1000);*/
    }
}
