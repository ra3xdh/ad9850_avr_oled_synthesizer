#ifndef MAIN_H
#define MAIN_H

#define BOARD_ID 0x55AB

typedef struct struc_options_t {
    uint16_t board_id;
    uint32_t rf_freq;
    uint8_t band_code;
    uint32_t bfo_freq_usb;
    uint32_t bfo_freq_lsb;
    uint32_t cw_offset;
    bool ext_bfo;
    bool invert_sb;
} options_t;

#endif

