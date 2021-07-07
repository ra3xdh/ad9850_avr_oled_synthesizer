/* Copyright (c) 2002 - 2006  Marek Michalkiewicz
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

/*
   pgmread-inc.h

   Contributors:
     Created by Marek Michalkiewicz <marekm@linux.org.pl>
     Eric B. Weddington <eric@ecentral.com>
     Wolfgang Haidinger <wh@vmars.tuwien.ac.at> (pgm_read_dword())
     Georg-Johann Lay <georgjohann@web.de> (pgm_read_xxx_inc())
 */

#ifndef __PGMREAD_INC_H_
#define __PGMREAD_INC_H_

#include <avr/pgmspace.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __LPM_inc_classic__(addr)   \
(__extension__({                \
    uint8_t __result;           \
    __asm__                     \
    (                           \
        "lpm" "\n\t"            \
        "mov %0, r0"  "\n\t"    \
        "adiw r30, 1" "\n\t"    \
        : "=r" (__result), "=z" (addr) \
        : "1" (addr)            \
        : "r0"                  \
    );                          \
    __result;                   \
}))

#define __LPM_inc_enhanced__(addr)  \
(__extension__({                    \
    uint8_t __result;               \
    __asm__                         \
    (                               \
        "lpm %0, Z+"                \
        : "=r" (__result), "=z" (addr) \
        : "1" (addr)                \
    );                              \
    __result;                       \
}))

#define __LPM_word_inc_classic__(addr)      \
(__extension__({                            \
    uint16_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm"           "\n\t"              \
        "mov %A0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %B0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        : "=r" (__result), "=z" (addr)      \
        : "1" (addr)                        \
        : "r0"                              \
    );                                      \
    __result;                               \
}))

#define __LPM_word_inc_enhanced__(addr)     \
(__extension__({                            \
    uint16_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm %A0, Z+"   "\n\t"              \
        "lpm %B0, Z+"    "\n\t"             \
        : "=r" (__result), "=z" (addr)      \
        : "1" (addr)                        \
    );                                      \
    __result;                               \
}))

#define __LPM_dword_inc_classic__(addr)     \
(__extension__({                            \
    uint32_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm"           "\n\t"              \
        "mov %A0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %B0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %C0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        "lpm"           "\n\t"              \
        "mov %D0, r0"   "\n\t"              \
        "adiw r30, 1"   "\n\t"              \
        : "=r" (__result), "=z" (addr)      \
        : "1" (addr)                        \
        : "r0"                              \
    );                                      \
    __result;                               \
}))

#define __LPM_dword_inc_enhanced__(addr)    \
(__extension__({                            \
    uint32_t __result;                      \
    __asm__                                 \
    (                                       \
        "lpm %A0, Z+"   "\n\t"              \
        "lpm %B0, Z+"   "\n\t"              \
        "lpm %C0, Z+"   "\n\t"              \
        "lpm %D0, Z+"    "\n\t"             \
        : "=r" (__result), "=z" (addr)      \
        : "1" (addr)                        \
    );                                      \
    __result;                               \
}))

#if defined (__AVR_HAVE_LPMX__)
#   define pgm_read_byte_inc(addr)    __LPM_inc_enhanced__(addr)
#   define pgm_read_word_inc(addr)    __LPM_word_inc_enhanced__(addr)
#   define pgm_read_dword_inc(addr)   __LPM_dword_inc_enhanced__(addr)
#else
#   define pgm_read_byte_inc(addr)    __LPM_inc_classic__(addr)
#   define pgm_read_word_inc(addr)    __LPM_word_inc_classic__(addr)
#   define pgm_read_dword_inc(addr)   __LPM_dword_inc_classic__(addr)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __PGMREAD_INC_H_ */
