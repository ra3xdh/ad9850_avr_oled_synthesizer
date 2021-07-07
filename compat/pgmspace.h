#ifndef COMPAT_PGMSPACE_H
#define COMPAT_PGMSPACE_H

#if defined (__GNUC__) && defined (__AVR__)
#   include <avr/pgmspace.h>
#   include "pgmread-inc.h"
#   define  pgm_read_addr_inc(x)  pgm_read_word_inc(x)
#   define  pgm_read_addr(x)      pgm_read_word(x)
#else
#   include <string.h>
#   define memcpy_P memcpy
#   include <inttypes.h>
#   define PROGMEM
#   define PSTR(X)  (X)

/*
#   define pgm_read_byte(x)  (*((uint8_t*)  x))
#   define pgm_read_word(x)  (*((uint16_t*) x))
#   define pgm_read_dword(x) (*((uint32_t*) x))
*/
#   define pgm_read_byte_inc(x)  pgm_read_byte_inc_f(&(x))
#   define pgm_read_word_inc(x)  pgm_read_word_inc_f(&(x))
#   define pgm_read_dword_inc(x) pgm_read_dword_inc_f(&(x))
#   define pgm_read_addr_inc(x)  pgm_read_addr_inc_f(&(x))
//#   define pgm_read_addr(x)      pgm_read_addr_f(&(x))

static inline uint8_t  pgm_read_byte  (const uint8_t  * addr) { return *addr; }
static inline uint16_t pgm_read_word  (const uint16_t * addr) { return *addr; }
static inline uint32_t pgm_read_dword (const uint32_t * addr) { return *addr; }
static inline const void* pgm_read_addr (const void ** addr)  { return *addr; }

static inline uint8_t  pgm_read_byte_inc_f  (const uint8_t  ** addr) { return *(*addr)++; }
static inline uint16_t pgm_read_word_inc_f  (const uint16_t ** addr) { return *(*addr)++; }
static inline uint32_t pgm_read_dword_inc_f (const uint32_t ** addr) { return *(*addr)++; }
static inline const void* pgm_read_addr_inc_f (const void *** addr)  { return *(*addr)++; }

#endif

#endif // COMPAT_PGMSPACE_H
