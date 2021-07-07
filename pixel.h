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
#ifndef _PIXEL_H_
#define _PIXEL_H_

#include <inttypes.h>

// (un)signed Pixel
typedef struct { uint8_t x, y; } upixel8_t;
typedef struct { int8_t  x, y; }  pixel8_t;

typedef struct { uint16_t x, y; } upixel16_t;
typedef struct { int16_t  x, y; }  pixel16_t;

#endif // _PIXEL_H_
