/*
    This file is part of VEKFONT.

    VEKFONT is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License (LGPL)
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    VEKFONT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License at <http://www.gnu.org/licenses/>
    for more details.

    (C) Georg-Johann Lay <georgjohann@web.de>
*/

#include "vektor-zeichen.h"

#if !defined (__GNUC__) || !defined (__AVR__)
#define PROGMEM
#else // avr-gcc
#include <avr/pgmspace.h>
#endif // avr-gcc

#define LEFT0
#define LEFT1  | (1 << 6)
#define LEFT2  | (2 << 6)

#define RIGHT0
#define RIGHT1 | (1 << 5)

#if (VEKFONT) & VF_SHRINKY
#define SHRINKY | (1 << 7)
#else
#define SHRINKY
#endif // SHRINKY

const uint8_t vecfont_data[] PROGMEM =
{
    // Umlaute haben Codes > 0x80 und liegen damit nicht in
    // der lookup-Tabelle (oder die Lookup-Tabelle wird rund
    // doppelt so groß und enthält viele ungenutzte Plätze).
    // Daher stehen Umlaute und Ligaturen zu Beginn der
    // Tabelle um die Suche nicht unnötig zu verlangsamen.
#if (VEKFONT) & VF_UMLAUTS
#if (VEKFONT) & VF_LOWERCASE
    'ä', 18  LEFT1
    , 3, 3
    , VF_LINE (3,  0, -1, 1, 1)
    , 3, 2
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    , 1, 4
    , DOTS_L
    , 2, 4
    , DOTS_R
    ,
    'ö', 16  LEFT1
    , 3, 2
    , VF_LINE (1, -1,  1, 1, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 0)
    , 1, 4
    , DOTS_L
    , 2, 4
    , DOTS_R
    ,
    'ü', 15  LEFT1
    , 3, 3
    , VF_LINE (3,  0, -1, 1, 1)
    , 0, 3
    , VF_LINE (2,  0, -1, 1, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    , 1, 4
    , DOTS_L
    , 2, 4
    , DOTS_R
    ,
    'ß', 12  LEFT1
    , 1, 0
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (7,  0, -1, 0, 1)
    ,
#endif // LOWERCASE in UMLAUTS

    'Ä', 13
    , VF_LINE (4,  0,  1, 1, 1)
    , VF_LINE (2,  1,  1, 0, 1)
    , VF_LINE (2,  1, -1, 0, 1)
    , VF_LINE (4,  0, -1, 0, 1)
    , 0, 3
    , VF_LINE (4, 1, 0, 0, 0)
    , 1, 6
    , DOTS_L
    , 3, 6
    , DOTS_R
    ,
    'Ö', 16
    , 0, 1
    , VF_LINE (3,  0,  1, 1, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (3,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 0)
    , 1, 6
    , DOTS_L
    , 3, 6
    , DOTS_R
    ,
    'Ü', 13
    , 0, 5
    , VF_LINE (4,  0, -1, 1, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (4,  0,  1, 0, 1)
    , 1, 6
    , DOTS_L
    , 3, 6
    , DOTS_R
    ,
#endif // UMLAUTS

    '0', 11
    , 0, 1
    , VF_LINE (4,  0,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (4, -1, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (4,  0,  1, 0, 0)
    ,
    '1', 7  RIGHT0  LEFT1
    , 1, 0
    , VF_LINE (2,  1,  0, 1, 1)
    , 0, 4
    , VF_LINE (2,  1,  1, 1, 1)
    , VF_LINE (6,  0, -1, 0, 0)
    ,
    '2', 8
    , 0, 5
    , VF_LINE (1,  1,  1, 1, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (4, -1, -1, 0, 1)
    , VF_LINE (4,  1,  0, 0, 1)
    ,
    '3', 15
    , 3, 3
    , VF_LINE (1, -1,  0, 0, 1)
    , 0, 1
    , VF_LINE (1,  1, -1, 1, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    ,
    '4', 6
    , 3, 0
    , VF_LINE (6,  0,  1, 1, 1)
    , VF_LINE (3, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (4,  1,  0, 0, 1)
    ,
    '5', 11
    , 4, 6
    , VF_LINE (4, -1,  0, 1, 1)
    , VF_LINE (3,  0, -1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (2,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    ,
    '6', 13
    , 0, 2
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (4,  0,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    ,
    '7', 7
    , 0, 5
    , VF_LINE (1,  0,  1, 1, 1)
    , VF_LINE (4,  1,  0, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (3, -1, -1, 0, 1)
    , VF_LINE (2,  0, -1, 0, 1)
    ,
    '8', 17
    , 1, 3
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 0)
    ,
    '9', 13
    , 4, 4
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (4,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    ,
    'A', 8
    , VF_LINE (5,  0,  1, 1, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (5,  0, -1, 0, 1)
    , 0, 3
    , VF_LINE (4,  1,  0, 0, 0)
    ,
    'B', 12
    , VF_LINE (6,  0,  1, 1, 1)
    , VF_LINE (3,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (3, -1,  0, 0, 0)
    , 0, 3
    , VF_LINE (3,  1,  0, 0, 0)
    ,
    'C', 9
    , 4, 1
    , VF_LINE (1, -1, -1, 1, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (4,  0,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    ,
    'D', 6
    , VF_LINE (6,  0,  1, 1, 1)
    , VF_LINE (3,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (4,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (3, -1,  0, 0, 0)
    ,
    'E', 8
    , 4, 0
    , VF_LINE (4, -1,  0, 1, 1)
    , VF_LINE (6,  0,  1, 0, 1)
    , VF_LINE (4,  1,  0, 0, 1)
    , 0, 3
    , VF_LINE (3,  1,  0, 0, 1)
    ,
    'F', 5
    , VF_LINE (6,  0,  1, 1, 1)
    , VF_LINE (4,  1,  0, 0, 1)
    , 0, 3
    , VF_LINE (2,  1,  0, 0, 1)
    ,
    'G', 13
    , 4, 1
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (4,  0,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , 2, 3
    , VF_LINE (2,  1,  0, 1, 1)
    , VF_LINE (3,  0, -1, 0, 1)
    ,
    'H', 7
    , VF_LINE (6,  0,  1, 1, 1)
    , 4, 0
    , VF_LINE (6,  0,  1, 1, 1)
    , 0, 3
    , VF_LINE (4,  1,  0, 0, 0)
    ,
    'I', 7  RIGHT1  LEFT2
    , VF_LINE (2,  1,  0, 1, 1)
    , 1, 0
    , VF_LINE (6,  0,  1, 0, 0)
    , 0, 6
    , VF_LINE (2,  1,  0, 1, 1)
    ,
    'J', 5
    , VF_LINE (1,  1, -1, 1, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (6,  0,  1, 0, 1)
    , VF_LINE (4, -1,  0, 0, 1)
    ,
    'K', 8
    , VF_LINE (6,  0,  1, 1, 1)
    , 0, 3
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (3,  1,  1, 0, 1)
    , 1, 3
    , VF_LINE (3,  1, -1, 0, 1)
    ,
    'L', 4
    , 4, 0
    , VF_LINE (4, -1,  0, 1, 1)
    , VF_LINE (6,  0,  1, 0, 1)
    ,
    'M', 4
    , VF_LINE (6,  0,  1, 1, 1)
    , VF_LINE (2,  1, -1, 0, 1)
    , VF_LINE (2,  1,  1, 0, 1)
    , VF_LINE (6,  0, -1, 0, 1)
    ,
    'N', 7
    , VF_LINE (6,  0,  1, 1, 1)
    , 4, 0
    , VF_LINE (6,  0,  1, 1, 1)
    , 0, 5
    , VF_LINE (4,  1, -1, 0, 0)
    ,
    'O', 10
    , 0, 1
    , VF_LINE (4,  0,  1, 1, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (4,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 0)
    ,
    'P', 6
    , VF_LINE (6,  0,  1, 1, 1)
    , VF_LINE (3,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (3, -1,  0, 0, 0)
    ,
    'Q', 13
    , 2, 2
    , VF_LINE (1,  1, -1, 1, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (4,  0,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (3,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    ,
    'R', 9
    , VF_LINE (6,  0,  1, 1, 1)
    , VF_LINE (3,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (3, -1,  0, 0, 0)
    , 1, 3
    , VF_LINE (3,  1, -1, 0, 1)
    ,
    'S', 13
    , 0, 1
    , VF_LINE (1,  1, -1,  1,  1)
    , VF_LINE (2,  1,  0,  0,  1)
    , VF_LINE (1,  1,  1,  0,  1)
    , VF_LINE (1,  0,  1,  0,  1)
    , VF_LINE (1, -1,  1,  0,  1)
    , VF_LINE (2, -1,  0,  0,  1)
    , VF_LINE (1, -1,  1,  0,  1)
    , VF_LINE (1,  0,  1,  0,  1)
    , VF_LINE (1,  1,  1,  0,  1)
    , VF_LINE (2,  1,  0,  0,  1)
    , VF_LINE (1,  1, -1,  0,  1)
    ,
    'T', 6
    , 2, 6
    , VF_LINE (6,  0, -1,  0,  1)
    , 0, 6
    , VF_LINE (4,  1,  0,  1,  1)
    ,
    'U', 7
    , 0, 6
    , VF_LINE (5,  0, -1,  1,  1)
    , VF_LINE (1,  1, -1,  0,  1)
    , VF_LINE (2,  1,  0,  0,  1)
    , VF_LINE (1,  1,  1,  0,  1)
    , VF_LINE (5,  0,  1,  0,  1)
    ,
    'V', 6
    , 0, 6
    , VF_LINE (4,  0, -1,  1,  1)
    , VF_LINE (2,  1, -1,  0,  1)
    , VF_LINE (2,  1,  1,  0,  1)
    , VF_LINE (4,  0,  1,  0,  1)
    ,
    'W', 6
    , 0, 6
    , VF_LINE (6,  0, -1,  1,  1)
    , VF_LINE (2,  1,  1,  0,  1)
    , VF_LINE (2,  1, -1,  0,  1)
    , VF_LINE (6,  0,  1,  0,  1)
    ,
    'X', 8
    , VF_LINE (1,  0,  1,  1,  1)
    , VF_LINE (4,  1,  1,  0,  1)
    , VF_LINE (1,  0,  1,  0,  1)
    , 0, 6
    , VF_LINE (1,  0, -1,  1,  1)
    , VF_LINE (4,  1, -1,  0,  1)
    , VF_LINE (1,  0, -1,  0,  1)
    ,
    'Y', 9
    , 2, 3
    , VF_LINE (3,  0, -1,  0,  1)
    , 0, 6
    , VF_LINE (1,  0, -1,  1,  1)
    , VF_LINE (2,  1, -1,  0,  1)
    , VF_LINE (2,  1,  1,  0,  1)
    , VF_LINE (1,  0,  1,  0,  1)
    ,
    'Z', 7
    , 4, 0
    , VF_LINE (4, -1,  0,  1,  1)
    , VF_LINE (1,  0,  1,  0,  1)
    , VF_LINE (4,  1,  1,  0,  1)
    , VF_LINE (1,  0,  1,  0,  1)
    , VF_LINE (4, -1,  0,  0,  1)
    ,
    ':', 12  LEFT1
    , 1, 2
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , 1, 5
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    ,
    '.', 4  RIGHT1  LEFT2
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    ,
#if (VEKFONT) & VF_LOWERCASE
    'a', 12  LEFT1
    , 3, 3
    , VF_LINE (3,  0, -1, 1, 1)
    , 3, 2
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    ,
    'b', 10  LEFT1
    , VF_LINE (5,  0,  1, 1, 1)
    , 0, 1
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 0)
    ,
    'c', 9  LEFT1
    , 3, 2
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    ,
    'd', 12  LEFT1
    , 3, 2
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    , 3, 0
    , VF_LINE (5,  0,  1, 1, 1)
    ,
    'e', 10  LEFT1
    , 0, 2  SHRINKY
    , VF_LINE (3,  1,  0, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    ,
    'f', 11  LEFT2
    , 3, 4
    , VF_LINE (1, -1,  1, 1, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (6,  0, -1, 0, 1)
    , 1, 2
    , VF_LINE (1,  1,  0, 0, 1)
    , 1, 2
    , VF_LINE (1, -1,  0, 0, 1)
    ,
    'g', 15  LEFT1
    , 3, 3
    , VF_LINE (4,  0, -1, 1, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , 3, 2
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    ,
    'h', 7  LEFT1
    , VF_LINE (5,  0,  1, 1, 1)
    , 0, 2
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (2,  0, -1, 0, 1)
    ,
    'i', 8  RIGHT1  LEFT2
    , VF_LINE (2,  1,  0, 1, 1)
    , 1, 5
    , VF_LINE (1,  0, -1, 1, 0)
    , 0, 3
    , VF_LINE (1,  1,  0, 1, 1)
    , VF_LINE (3,  0, -1, 0, 0)
    ,
    'j', 9  RIGHT1  LEFT2
    , 1, 3
    , VF_LINE (1,  1,  0, 1, 1)
    , VF_LINE (4,  0, -1, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , 2, 5
    , VF_LINE (1,  0, -1, 1, 0)
    ,
    'k', 8  LEFT1
    , VF_LINE (5,  0,  1, 1, 1)
    , 0, 2
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (2,  1,  1, 0, 1)
    , 1, 2
    , VF_LINE (2,  1, -1, 0, 1)
    ,
    'l', 5  RIGHT1  LEFT2
    , VF_LINE (2,  1,  0, 1, 1)
    , 0, 5
    , VF_LINE (1,  1,  0, 1, 1)
    , VF_LINE (5,  0, -1, 0, 0)
    ,
    'm', 11
    , VF_LINE (3,  0,  1, 1, 1)
    , 0, 2
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (3,  0, -1, 0, 1)
    , 2, 2
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (3,  0, -1, 0, 1)
    ,
    'n', 7  LEFT1
    , VF_LINE (3,  0,  1, 1, 1)
    , 0, 2
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (2,  0, -1, 0, 1)
    ,
    'o', 10  LEFT1
    , 3, 2
    , VF_LINE (1, -1,  1, 1, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 0)
    ,
    'p', 12  LEFT1
    , 0, 3
    , VF_LINE (5,  0, -1, 1, 1)
    , 0, 1
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 0)
    ,
    'q', 12  LEFT1
    , 3, 3
    , VF_LINE (5,  0, -1, 1, 1)
    , 3, 2
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    ,
    'r', 5  RIGHT1  LEFT2
    , VF_LINE (3,  0,  1, 1, 1)
    , 0, 2
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    ,
#if (VEKFONT) & VF_SHRINKY
    's', 9  LEFT1
    , 0, 0  SHRINKY
#else
    's', 7  LEFT1
#endif // SHRINKY
    , VF_LINE (2,  1,  0, 1, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    ,
    't', 10  RIGHT1 LEFT2
    , 1, 4
    , VF_LINE (1,  1,  0, 0, 1)
    , 1, 4
    , VF_LINE (1, -1,  0, 0, 1)
    , 1, 5
    , VF_LINE (5,  0, -1, 1, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    ,
    'u', 9  LEFT1
    , 3, 3
    , VF_LINE (3,  0, -1, 1, 1)
    , 0, 3
    , VF_LINE (2,  0, -1, 1, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    ,
    'v', 6  RIGHT1  LEFT2
    , 0, 3
    , VF_LINE (2,  0, -1, 1, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  0,  1, 0, 1)
    ,
    'w', 11
    , 0, 3
    , VF_LINE (2,  0, -1, 1, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (1,  0,  1, 0, 1)
    , 2, 1
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  1, 0, 1)
    , VF_LINE (2,  0,  1, 0, 1)
    ,
    'x', 4  LEFT1
    , VF_LINE (3,  1,  1, 1, 1)
    , 0, 3
    , VF_LINE (3,  1, -1, 1, 1)
    ,
    'y', 12  LEFT1
    , 3, 3
    , VF_LINE (4,  0, -1, 1, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1, -1,  1, 0, 1)
    , 0, 3
    , VF_LINE (2,  0, -1, 1, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1,  1, 0, 0)
    ,
    'z', 5  LEFT1
    , 0, 3
    , VF_LINE (3,  1,  0, 1, 1)
    , VF_LINE (3, -1, -1, 0, 1)
    , VF_LINE (3,  1,  0, 0, 1)
    ,
#endif // LOWERCASE

#if (VEKFONT) & VF_PUNKT
    '?', 11
    , 1, 0
    , DOTS_T
    , 0, 5
    , VF_LINE (1,  1,  1, 1, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (2, -1, -1, 0, 1)
    , DOTS_B
    ,
    '!', 7 RIGHT1  LEFT2
    , 1, 0
    , DOTS_T
    , 1, 6
    , VF_LINE (4,  0, -1, 1, 0)
    , DOTS_B
    ,
    '*', 6  RIGHT1  LEFT2
    , 0, 2
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1,  1,  0, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    ,
    ',', 4  RIGHT1  LEFT2
    , 0, 1
    , VF_LINE (1,  0, -1, 1, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    ,
    ';', 7  RIGHT1  LEFT2
    , 0, 3
    , VF_LINE (1,  0, -1, 1, 0)
    , 0, 1
    , VF_LINE (1,  0, -1, 1, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    ,
    '=', 6  LEFT1
    , 0, 2
    , VF_LINE (3,  1,  0, 1, 1)
    , 0, 4
    , VF_LINE (3,  1,  0, 1, 1)
    ,
    '-', 3  LEFT2 RIGHT1
    , 0, 3
    , VF_LINE (3,  1,  0, 1, 0)
    ,
    '+', 6  RIGHT1  LEFT2
    , 0, 3
    , VF_LINE (2,  1,  0, 1, 1)
    , 1, 2
    , VF_LINE (2,  0,  1, 1, 1)
    ,
    '@', 13  LEFT0
    , 3, 1
    , VF_LINE (1,  0,  1, 0, 1)
    , VF_LINE (1, -1,  0, 0, 1)
    , VF_LINE (1,  0, -1, 0, 1)
    , VF_LINE (2,  1,  0, 0, 1)
    , VF_LINE (2,  0,  1, 0, 1)

    , VF_LINE (1, -1,  1, 0, 1)
    , VF_LINE (2, -1,  0, 0, 1)
    , VF_LINE (1, -1, -1, 0, 1)
    , VF_LINE (2,  0, -1, 0, 1)
    , VF_LINE (1,  1, -1, 0, 1)
    , VF_LINE (3,  1,  0, 0, 0)
    ,
    // Unterstrich
    '_', 3
    , 0, 32-2
    , VF_LINE (5,  1,  0, 1, 1)
    ,
    // Unterstrich (von einer Zeile tiefer)
    '#', 6
    , 5, 7
    , VF_LINE (5,  -1,  0, 1, 1)
    , 5, 6
    , VF_LINE (5,  -1,  0, 1, 1)
    ,
#endif // VF_PUNKT

#if (VEKFONT) & VF_ARROWS
    // ->
    '>', 7
    , 0, 3
    , VF_LINE (4,  1,  0, 1, 0)
    , 2, 1
    , VF_LINE (2,  1,  1, 1, 1)
    , VF_LINE (2, -1,  1, 0, 1)
    ,
    // <-
    '<', 7
    , 0, 3
    , VF_LINE (4,  1,  0, 0, 1)
    , 2, 1
    , VF_LINE (2, -1,  1, 1, 1)
    , VF_LINE (2,  1,  1, 0, 1)
    ,
    // ^
    // |
    '^', 7
    , 2, 1
    , VF_LINE (4,  0,  1, 1, 0)
    , 0, 3
    , VF_LINE (2,  1,  1, 1, 1)
    , VF_LINE (2,  1, -1, 0, 1)
    ,
    // |
    // v
    '\\', 7
    , 2, 1
    , VF_LINE (4,  0,  1, 0, 1)
    , 0, 3
    , VF_LINE (2,  1, -1, 1, 1)
    , VF_LINE (2,  1,  1, 0, 1)
    ,
#endif // ARROWS
    VF_UNKNOWN, 3
    , 2, 3
    , VF_LINE (1,  1,  0, 1, 0)
};
