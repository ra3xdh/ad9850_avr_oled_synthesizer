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

    (C) by Georg-Johann Lay <georgjohann@web.de>
*/

#ifndef VEKTOR_ZEICHEN_H
#define VEKTOR_ZEICHEN_H

#include <stdint.h>

#include "pixel.h"

// Über dieses Makro kann die Breite der verwendeten Variablen
// eingestellt werden. Für minimalen Codeverbrauch etwa auf AVR
// und bei einer Anzeige, deren x- und y-Koordinaten 8 Bit breit
// sind, genügen 8 Bits. Für größere Anzeigen oder Host-Darstellung
// kann es erforderlich sein, mit mehr als 8 Bit zu rechnen.
#ifndef VF_INT_BITS
#define VF_INT_BITS 8
#endif

//////////////////////////////////////////////////////////////////////
// VEKFONT enthält mehrere, im folgenden beschriebene Konfigurations-
// Bits, mit denen die Eigenschaften des Zeichensatzes eingestellt
// werden können. Den geringsten Speicherplatzbedarf hat
// VEKFONT=0:  Nur Großbuchstaben, keine Abbildung von Umlauten/Klein-
//             buchstaben, etc.
// VEKFONT=-1: Bietet die beste Unterstützung bei größerem Code
#ifndef VEKFONT
#define VEKFONT (0)
//#define VEKFONT (-1)
#endif

// Bit von VEKFONT
// Enthält der Zeichensatz deutsche Umlaute Ä, Ö, Ü, ä, ö, ü und
// die Ligatur ß?
#define VF_UMLAUTS       (1 << 0)

// Bit von VEKFONT
// Enthält der Zeichensatz Kleinbuchstaben?
#define VF_LOWERCASE     (1 << 1)

// Bit von VEKFONT
// Enthält der Zeichensatz Pfeil-Symbole (ansprechbar via <, >, _, ^)
#define VF_ARROWS        (1 << 2)

// Bit von VEKFONT
// Enthält der Zeichensatz Punktuation wie (+, -, *, ?, ...)
#define VF_PUNKT         (1 << 3)

// Bit von VEKFONT
// Falls der Zeichensatz keine Umlaute enthält: Sollen Umlaute wie
// Ä als AE dargestellt werden?
#define VF_MAP_UMLAUTS   (1 << 4)

// Bit von VEKFONT
// Falls der Zeichensatz keine Kleinbuchstaben enthält:
// Sollen Kleinbuchstaben als Großbuchstaben dargestellt werden?
#define VF_MAP_LOWERCASE (1 << 5)

// Bit von VEKFONT
// Kleinbuchstaben 'e' und 's' ragen 1 Pixel über die Mittellinie
// und werden daher zu groß. Wird dieses Flag gesetzt, dann
// werden diese Buchstaben bei .zoom > 1 etwas geschrumpft,
// damit sie die Höhe der anderen Kleinbuchstaben erhalten.
#define VF_SHRINKY       (1 << 6)

// Bit von VEKFONT
// Wenn dieses Bit gesetzt ist, dann kann zur Laufzeit zwischen
// Fixed-Font und Proportionalschrift umgestellt werden.
// Auf den Platzbedarf des Zeichensatzes hat das keinen Einfluß,
// das Programm wird aber etwas langsamer und größer.
#define VF_PROPORTIONAL (1 << 7)

// Bit von VEKFONT
// Wenn dieses Bit gesetzt ist, wird die Schrift immer als
// Proportionalschrift angezeigt.
// Das Bit ist stärker als VF_PROPORTIONAL
#define VF_ALWAYS_PROPORTIONAL (1 << 8)

// Bit von VEKFONT
// Wenn dieses Bit gesetzt ist, dann können über die LINE-Sondercodes
// DOTS_L, DOTS_R, DOTS_B, DOTS_T bestimmte Pünktchen für Umlaute und
// Zeichen wie ? oder ! erzeugt werden, deren Länge nur 1/2 Einheit ist.
// Es können dann aber keine Linien der Länge 7 in die Richtung (-1,-1)
// mehr gezeichnet werden. 
// (Was eh praktisch nie gebraucht wird. Ansonsten zeichnet man eben 
//  in Richtung (1,1).)
#define VF_DOTS (1 << 9)

//////////////////////////////////////////////////////////////////////
// Falls LOOKUP_END > LOOKUP_START ist, dann wird zum schnellen
// Auffinden der Zeicheninformation eine Lookup-Tabelle im RAM
// aufgebaut. Die Tabelle enthält dann Indizes der Zeichen mit
// ASCII-Code von VF_LOOKUP_START bis VF_LOOKUP_END.
// Der RAM-Bedarf in Bytes ist
//   sizeof(void*) * (VF_LOOKUP_END - VF_LOOKUP_START + 1)
#ifndef VF_LOOKUP_START
#define VF_LOOKUP_START '*'
#endif // LOOKUP_START

#ifndef VF_LOOKUP_END
#define VF_LOOKUP_END 0
#endif // LOOKUP_END

//////////////////////////////////////////////////////////////////////
// VF_EXTRA_GLYPHS. Es können eigene Zeichen definiert werden.
// Dazu muss das Makro VF_EXTRA_GLYPHS die (Flash-)Adresse der
// Zeicheninformationen liefern. Falls ein Zeichen in der 
// mitgelieferten Tabelle nicht gefunden wird, dann wird ab Adresse
// VF_EXTRA_GLYPHS nach dem Zeichen gesucht.
// Diese Daten müssen mit dem Zeichen VF_UNKNOWN_EXTRA abgeschlossen sein.
// Siehe dazu den Aufbau der Zeichentabelle in vektor-zeichen-data.c
#define VF_UNKNOWN_EXTRA ((uint8_t) '\002')

//////////////////////////////////////////////////////////////////////
// Wird ausgegeben, wenn ein Zeichen nicht gefunden wird.
// Kennzeichnet außerdem das Tabellenende bzw. den Übergang zu
// VF_EXTRA_GLYPHS, sofern vorhanden.
#define VF_UNKNOWN ((uint8_t) '\001')

//////////////////////////////////////////////////////////////////////
// Für Sonderanwendung, wird normal nicht gebraucht
// Beim Aufruf wird u.U. kein Pixel ausgegeben
#ifndef VF_PLOTTER
#define VF_PLOTTER 0
#endif

#if VF_INT_BITS == 8
typedef uint8_t vf_uint_t;
typedef int8_t  vf_int_t;
typedef upixel8_t vf_upixel_t;
typedef pixel8_t  vf_spixel_t;
#elif VF_INT_BITS == 16
typedef uint16_t vf_uint_t;
typedef int16_t  vf_int_t;
typedef upixel16_t vf_upixel_t;
typedef pixel16_t  vf_spixel_t;
#else
#error VF_INT_BITS must be 8 or 16
#endif

// Feld mit der Zeichensatz-Information
extern const uint8_t vecfont_data[];

// Struktur mit der Zeichen-Information
typedef struct
{
    // RAM-Adresse des auszugebenden Textes
    const char * text;

    // Wird zur Ausgabe eines Pixels aufgerufen
    void (*beam_xy)(vf_uint_t x, vf_uint_t y);
    
    // Wird Aufgerufen zwischen zwei nicht-nebeneinander liegenden
    // Pixeln, also wenn der Strahl/Stift einen Sprung machen muss.
    void (*beam_skip)(void);

    // Startpunkt des auszugebenden Textes:
    // die untere linke Ecke des ersten Zeichens
    vf_upixel_t start;

    // Zoom-Faktor
    uint8_t zoom;

    // Proportional-Schrift oder Fixed-Font?
    // Nur wirksam zusammen mit VF_PROPORTIONAL
    uint8_t proportional;

    // Nur wirksam für avr-gcc: Steht text im Flash?
    uint8_t text_in_flash;
    ///////////////////////////////////////////////////////////////////
    // Interne Verwendung
    ///////////////////////////////////////////////////////////////////
    const uint8_t * addr;   // Adresse ins vektor_zeichen_data[] Feld
    vf_spixel_t  d;         // Abstand zum nächsten Pixel
    vf_uint_t nPixels;      // n Pixel in dieser Linie
    vf_uint_t iPixel;       // Index des Pixels in dieser Linie
    vf_uint_t itext;        // Index des momentanen Zeichens in text[]
    vf_upixel_t p;          // Zeichen-Position
    vf_upixel_t pix;        // Pixel-Position
    uint8_t   nLines;       // Linien in diesem Zeichen
    uint8_t   iLine;        // Index der momentanen Linie
    uint8_t   noskip;       // ersten Pixel zeichnen
    uint8_t   right;        // nach rechts gehen bei Fixed
    uint8_t   left;         // nach links  gehen bei Proportional
    uint8_t   inject_char;  // Extra-Zeichen bei Konvertierung ä->ae etc.
    uint8_t   zeichen;      // Das aktuelle Zeichen
    uint8_t   shrinky;      // y-Ausdehnung auf 3/4 schrumpfen
    vf_upixel_t shrink;     // Pixel-Position
} vecfont_t;

extern uint8_t vecfont_draw_letters (vecfont_t * vf);
extern void vecfont_reset (vecfont_t * vf);

// Zeichenabstand horizontal/vertikal
#define VF_SPACE_X(ZOOM) (2+5*(ZOOM))
#define VF_SPACE_Y(ZOOM) (3+8*(ZOOM))

// len dxy start end
// 765 432 11111 000
#define VF_LINE(len,dx,dy,start,end)  \
    ((len << 5)                    \
    | (start ? 2 : 0)              \
    | (end   ? 1 : 0)              \
    | ((                           \
    (dx ==  1 && dy ==  0) ? 4 :   \
    (dx ==  1 && dy == -1) ? 3 :   \
    (dx ==  0 && dy == -1) ? 2 :   \
    (dx == -1 && dy == -1) ? 1 :   \
    (dx == -1 && dy ==  0) ? 0 :   \
    (dx == -1 && dy ==  1) ? 7 :   \
    (dx ==  0 && dy ==  1) ? 6 : 5 \
    ) << 2))

#if VEKFONT & (VF_UMLAUTS | VF_PUNKT | VF_DOTS)
#   define DOTS_L   VF_LINE(7,-1,-1,0,0)
#   define DOTS_R   VF_LINE(7,-1,-1,1,0)
#   define DOTS_B   VF_LINE(7,-1,-1,0,1)
#   define DOTS_T   VF_LINE(7,-1,-1,1,1)
#endif // VF_UMLAUTS || VF_PUNKT || VF_DOTS

#endif // VEKTOR_ZEICHEN_H
