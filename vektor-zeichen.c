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

/* VECFONT_BEAM_XY kann per Kommandozeile definiert werden,
 * mit GCC etwa via -DVECFONT_BEAM_XY=... oder -include file.h.
 * Das ist dann angesagt, wenn es um zeitkritische Anwendungen 
 * geht, die nicht teure, indirekte Aufrufe wie vf->beam (X,Y)
 * tätgen wollen, sondern lieber VECFONT_BEAM_XY als Makro oder
 * Inline-Funktion umsetzen wollen. */

#ifndef VECFONT_BEAM_XY
#   define VECFONT_BEAM_XY(X,Y)     vf->beam_xy (X,Y)
#endif // VECFONT_BEAM_XY

#ifndef VECFONT_BEAM_SKIP
#   define VECFONT_BEAM_SKIP()     vf->beam_skip ()
#endif // VECFONT_BEAM_SKIP

/* Versionen und Erweiterungen der 
 * avr/pgmspace.h-Makros, die auch für
 * i836 Host-Rechner funktionieren */
#include "compat/pgmspace.h"

// Masken für einige Flags
#define RIGHT1  (1 << 5)
#define LEFT1   (1 << 6)
#define SHRINKY (1 << 7)

// Falls vecfont_draw_letters() nicht bis zum Ende aufgerufen
// wird, müssen die internen Daten von Hand rückgesetzt werden
// vor einem erneuten Aufruf!
void vecfont_reset (vecfont_t * vf)
{
    vf->iPixel = 0;
    vf->iLine  = 0;
    vf->itext  = 0;
    vf->inject_char = 0;
}

// Gibt den Text in vf->text ab der Startposition vf->start aus,
// indem die Callback-Funktionen vf->beam(x,y) bzw vf->beam->skip()
// aufgerufen werden.
//
// !!! Falls VECFONT_BEAM_XY bzw. VECFONT_BEAM_XY nicht definiert sind,
// !!! dann müssen die Funktions-Zeiger vf->beam(x,y) bzw. vf->beam->skip()
// !!! initialisiert worden sein.
// !!! Ansonsten landet das Programm im Nirvana.

// Wie in zeitkritischen Anwendungen indirekte Funktionsaufrufe
// vermieden werden können, ist oben bei den Makros
// VECFONT_BEAM_XY und VECFONT_BEAM_XY beschrieben.
// Falls die Makros definiert sind, dann muss die entsprechende
// Callback-Function nicht initialisiert werden, weil der jeweilige
// Callback dann nicht aufgerufen wird.
// (Indirekte) Funktionsaufrufe zu vermeiden kann auch sinnvoll
// sein, um kleineren Code zu erhalten. Die Skip-Routine wird statisch
// 2x aufgerufen, die xy-Routine nur 1x.

// return-Wert
// 1: Es wurde kein Pixel ausgegeben, die Textausgabe ist fertig
// 0: Es wurde genau 1 Pixel via vf->beam_xy(x,y) ausgegeben.
//    Evtl. wurde vor der Pixelausgabe via vf->beam_skip()
//    über einen Sprung der Ausgabe-Position informiert.
//    Falls vf->beam_skip() nicht aufgerufen wurde, dann ist
//    der Abstand zum vorhergehenden Pixel (Maximums-Norm)
//    höchstens Eins, in der Euklid'schen Norm maximal \sqrt{2}.


#ifdef VEKFONT_ZOOM
#   define VF_ZOOM     (VEKFONT_ZOOM)
#else
#   define VF_ZOOM     vf->zoom
#endif // VEKFONT_ZOOM   

uint8_t vecfont_draw_letters (vecfont_t * vf)
{
    while (0==0)
    {
        // Die Nummer der gerade gezeichneten Linie
        uint8_t iLine = vf->iLine;

        if (vf->iPixel == 0)
        {
            // Neue Linie fängt an
            if (iLine == 0)
            {
                // Neues Zeichen fängt an
                // Wird ein Zeichen eingefügt?
                // Passiert, wenn Umlaute expandiert werden (Ä -> Ae)
                uint8_t zeichen = vf->inject_char;

                if (!zeichen)
                {
                    // Index des nächstes Zeichen im String
                    vf_uint_t itext = vf->itext;
                    if (itext == 0)
                    {
                        // Erstes Zeichen: Startposition
                        vf->p.x = vf->start.x;
                        vf->p.y = vf->start.y;
                    }
                    
                    // Die Adresse des Zeichens.
                    // Auf AVR müssen wir unterscheiden, ob es sich um 
                    // eine RAM- oder eine Flash-Adresse handelt
                    const char * pzeichen = &vf->text[itext];

                    zeichen = (uint8_t) *pzeichen;
#if defined (__GNUC__) && defined (__AVR__)
                    if (vf->text_in_flash)
                        zeichen = pgm_read_byte (pzeichen);
#endif // avr-gcc
                    vf->itext = itext+1;
                }

#ifdef VF_NOTIFY_CHAR
                {
                    // Informiert über Anfang eines neuen Zeichens,
                    // wird nur auf dem Host für SVG-Ausgabe benutzt.
                    extern void VF_NOTIFY_CHAR (vecfont_t *, char);
                    VF_NOTIFY_CHAR (vf, (char) zeichen);
                }
#endif // NOTIFY_CHAR

                uint8_t zoom = VF_ZOOM;
                
                // Einige Sonderzeichen behandeln: \0, \r, \n, \b, SPACE
                if (zeichen <= ' ')
                {
                    if (zeichen == '\0')
                    {
                        // Stringende: fertig
                        vf->itext = 0;
                        return 1;
                    }
                    
                    if (zeichen == '\r')
                        continue;
                        
                    // Leerzeichen
                    if (zeichen == ' ')
                    {
                        vf->p.x += VF_SPACE_X(zoom);
                        continue;
                    }
                    
                    // Zeilenumbruch
                    if (zeichen == '\n')
                    {
                        vf->p.y -= (vf_uint_t) VF_SPACE_Y(zoom);
                        vf->p.x = vf->start.x;
                        continue;
                    }
                    
                    // Ein Zeichen zurück
                    if (zeichen == '\b')
                    {
                        vf->p.x -= (vf_uint_t) VF_SPACE_X(zoom);
                        continue;
                    }
                
                } // zeichen <= ' '

#if ((VEKFONT) & VF_MAP_UMLAUTS) && !((VEKFONT) & VF_UMLAUTS)
                // Umlaute umwandeln: Ä -> Ae etc.
                uint8_t inject = 0;
                char c = zeichen;
                if (c == 'Ä')    zeichen = 'A', inject = 'e';
                if (c == 'Ö')    zeichen = 'O', inject = 'e';
                if (c == 'Ü')    zeichen = 'U', inject = 'e';
                if (c == 'ä')    zeichen = 'a', inject = 'e';
                if (c == 'ö')    zeichen = 'o', inject = 'e';
                if (c == 'ü')    zeichen = 'u', inject = 'e';
                if (c == 'ß')    zeichen = 's', inject = 's';
                vf->inject_char = inject;
#endif // MAP_UMLAUTS

#if ((VEKFONT) & VF_MAP_LOWERCASE) && !((VEKFONT) & VF_LOWERCASE)
                // Kleinbuchstaben in Großbuchstaben umwandeln
                if (zeichen >= 'a' && zeichen <= 'z')
                    zeichen += 'A'-'a';
#endif // MAP_LOWERCASE

                vf->pix.y = vf->p.y;
                vf->pix.x = vf->p.x;

                // Zeichendaten in Tabelle suchen
                const uint8_t * addr = vecfont_data;

#if VF_LOOKUP_END > VF_LOOKUP_START
                // In lookup-Tabelle die Startadresse der Zeichendaten
                // nachschauen
                static const uint8_t * lookup[(uint8_t) (VF_LOOKUP_END - VF_LOOKUP_START +1)];

                const uint8_t ** lookup_addr = 0;
                
                if (zeichen >= VF_LOOKUP_START 
                    && zeichen <= (uint16_t) VF_LOOKUP_START + VF_LOOKUP_END)
                {
                    lookup_addr = & lookup[zeichen - VF_LOOKUP_START];
                
                    if (*lookup_addr)
                        addr = *lookup_addr;
                }
#endif // LOOKUP

                uint8_t nLines;
                uint8_t nLinesRightLeft;
                uint8_t id;

                // Zeichen im Zeichensatz suchen. Falls das Zeichen in der
                // lookup-Tabelle eingetragen ist, wird es direkt gefunden
                while (1)
                {
                    id = pgm_read_byte_inc (addr);
                    nLinesRightLeft = pgm_read_byte_inc (addr);

                    nLines = nLinesRightLeft & 0x1f;
                    
                    if (id == zeichen)
                        // Daten gefunden
                        break;
                        
                    if (id == VF_UNKNOWN)
                    // Ende der Tabelle ist erreicht: das Zeichen ist also
#ifdef VF_EXTRA_GLYPHS
                    // Doch Halt! Die ANwendung definierte eigene Zeichen zur
                    // Erweiterung des Zeichensatzes. Wir haken uns dazwischen
                    // und ersetzen die Tabellen-Adresse mit der von der 
                    // Anwendun angegebenen und suchen weiter.
                    {
                        extern const uint8_t VF_EXTRA_GLYPHS[];
                        addr = (const uint8_t*) VF_EXTRA_GLYPHS;
                        continue;
                    }
                    // Erst wenn auch die Anwendung das Zeichen nicht definiert,
                    // ist es wirklich unbekannt.
                    if (id == VF_UNKNOWN_EXTRA)
#endif // VF_EXTRA_GLYPHS
                        break;
                        
                    // Überspringe die Daten dieses diesen Buchstaben,
                    // er ist nicht der gesuchte.
                    addr += nLines;
                } // while: suche Zeichen-Daten in lookup-Tabelle

                // Zeichen gefunden
                vf->zeichen = id;
                vf->addr    = addr;
                vf->nLines  = nLines;

#if VF_LOOKUP_END > VF_LOOKUP_START
                // Oben wurde 2x per post-increment gelesen, 
                // daher -2 um die Original-Adresse zu speichern
                if (lookup_addr)
                    *lookup_addr = addr - 2;
#endif // LOOKUP

                uint8_t proportional = 0;

#if (VEKFONT) & VF_ALWAYS_PROPORTIONAL
                proportional = 1;
#elif (VEKFONT) & VF_PROPORTIONAL
                proportional = vf->proportional;
#endif // PROPORTIONAL

#if (VEKFONT) & VF_LOWERCASE
                if (proportional)
                {
                    // T und F unterschneiden
                    if (id == 'T' || id == 'F')
                        nLinesRightLeft += LEFT1;
                }
#endif // LOWERCASE

                vf->left  = nLinesRightLeft;
                vf->right = 0;

                if ((nLinesRightLeft & RIGHT1) && !proportional)
                    vf->right = zoom;

#if (VEKFONT) & VF_SHRINKY
                vf->shrinky = 0;
                vf->shrink.x = 0;
                // Plausiblen Wert für y weil wir u.U. in y-Richtung scrollen
                vf->shrink.y = vf->pix.y;
#endif // SHRINKY

            } // iLine == 0

            const uint8_t * addr = vf->addr;

            // Lese Daten, Lesezeiger eins weiter
            uint8_t data = pgm_read_byte_inc (addr);

            // Dekodiere LINE-Daten
            vf_uint_t nPixels = data >> 5;

            vf_int_t dx, dy;
            uint8_t zoom = VF_ZOOM;

            if (nPixels == 0)
            {
                // 0 Pixel codieren für GOTO: Setzt neue x-y-Position
                dx = data;
                dy = pgm_read_byte_inc (addr);

                vf->addr = addr;

#if (VEKFONT) & VF_SHRINKY
                if (zoom > 1)
                    vf->shrinky = dy & SHRINKY;
                dy &= ~SHRINKY;
#endif // SHRINKY
                if (dy >= 20)
                    dy -= 32;

                dx = (vf_uint_t) dx * zoom;
                dy = (vf_uint_t) dy * zoom;

                dx += vf->right;

                vf->pix.x = vf->p.x + dx;
                vf->pix.y = vf->p.y + dy;

                VECFONT_BEAM_SKIP();
                vf->iLine += 2;

                continue;
            }

            vf->addr = addr;

            if (vf->iPixel == 0)
            {
                if (iLine == 0)
                {
                    // Neues Zeichen, das an 0,0 beginnt --> skip
                    vf->pix.x += vf->right;
                    VECFONT_BEAM_SKIP ();
                }
            }

            //  LINE

            nPixels *= zoom;
#if VF_PLOTTER == 2
            if (data != DOTS_L && data != DOTS_R)
            {
                nPixels++;
                vf->noskip = 1;
            }
            else
#endif // PLOTTER
            {
                nPixels--;

                uint8_t d;

                // Ende zeichnen
                if ((d = data & 1, d))  nPixels++;

                // Start zeichnen
                if ((d = data & 2, d))  nPixels++, vf->noskip = 1;

                if (!nPixels)
                {
                    vf->noskip = 0;
                    goto next_pixel;
                }
            }

#if (VEKFONT) & (VF_UMLAUTS | VF_PUNKT | VF_DOTS)
            uint8_t dots = 0;

            if (data == DOTS_L)         vf->pix.x --, dots = 1;
            if (data == DOTS_R)         vf->pix.x ++, dots = 1;
            if (data == DOTS_B)         dy = -1,      dots = 2;
            if (data == DOTS_T)         dy =  1,      dots = 3;

            if (dots == 1)
            {
                vf->nPixels = zoom;
                dx = 0;
                dy = 1;
                vf->noskip = 0;
            }
            else if (dots >= 2)
            {
                if (dots == 2 && zoom == 1)
                    goto next_pixel;

                dx = 0;
                vf->nPixels = (uint8_t) (zoom+1)/2;
                vf->noskip = 0;
            }
            else
#endif // UMLAUTS | PUNKT
            {
                vf->nPixels = nPixels;

                // dx, dy aus dxy extrahieren
                uint8_t dxy = (data >> 2) & 3;

                dy = dxy;
                if (dy)            dy = -1;
                if (dxy == 3)      dxy = 4;
                dx = dxy >> 1;
                dx -= 1;

                if (data & (1 << 4))
                    dx = -dx, dy = -dy;
            }

            vf->d.x = dx;
            vf->d.y = dy;
        } // vf->iPixel == 0

        vf_uint_t pixx = vf->pix.x;
        vf_uint_t pixy = vf->pix.y;

        if (!vf->noskip)
        {
#ifndef VECFONT_ADD
            pixx += vf->d.x;
            pixy += vf->d.y;
#else            
            VECFONT_ADD (pixx, vf->d.x);
            VECFONT_ADD (pixy, vf->d.y);
#endif // VECFONT_ADD
        }
        vf->noskip = 0;

        // Pixel zeichnen
        vf->pix.x = pixx;
        vf->pix.y = pixy;

        uint8_t doplot = 1;

#if (VEKFONT) & VF_SHRINKY
        if (vf->shrinky)
        {
            uint8_t y = pixy - vf->p.y;
            y *= 3; y /= 4;
            pixy = vf->p.y+y;

            if (vf->shrink.y != pixy || vf->shrink.x != pixx)
            {
#ifdef VECFONT_ADD
                // delta ist die Änderung in der y-Koordinate, die
                // nur zur Überlauferkennung addiert wird.
                // Der gleiche Zirkus wird beim Scrollen in x-Richtung
                // notwendig.
                y = vf->shrink.y;
                int8_t delta = pixy-y;
                VECFONT_ADD (y, delta);
#endif // VECFONT_ADD
                vf->shrink.y = pixy;
                vf->shrink.x = pixx;
            }
            else
                doplot = 0;
        }
#endif // SHRINKY

        if (doplot)
#if VF_PLOTTER
            if (vf->iPixel == 0 || vf->iPixel == vf->nPixels-1)
#endif // PLOTTER
                VECFONT_BEAM_XY (pixx, pixy);

        // nächstes Pixel
        if (++vf->iPixel == vf->nPixels)
        {
            uint8_t go_redraw = 0;

            if (0)
            {
                next_pixel:
                    go_redraw = 1;
            }

            vf->iPixel = 0;

            // Linien-Index eins weiter
            if (++iLine == vf->nLines)
            {
                iLine = 0;

                vf_uint_t px = vf->p.x;
                uint8_t zoom = VF_ZOOM;
                px += VF_SPACE_X(zoom);

#if ((VEKFONT) & VF_PROPORTIONAL) && !((VEKFONT) & VF_ALWAYS_PROPORTIONAL)
                if (vf->proportional)
#endif // PROPORTIONAL  && !ALWAYS_PROPORTIONAL
#if ((VEKFONT) & VF_PROPORTIONAL) || ((VEKFONT) & VF_ALWAYS_PROPORTIONAL)
                {
                    uint8_t left = vf->left & 0xc0;
                    if (left)
                    {
                        left >>= 6;
                        left = (vf_uint_t) (left * zoom);
                        if (vf->zeichen == 'c')
                            left++;
                        px -= left;
                        vf->left = 0;
                    }
                }
#endif // PROPORTIONAL | ALWAYS_PROPORTIONAL

                vf->right = 0;
                vf->p.x = px;
            }
            vf->iLine = iLine;

            if (go_redraw)
                continue;
        } // ++vf->iPixel == vf->nPixels

        break;
    } // Mit der Endlosschleife eliminieren wir ein paar gotos.

    // Der String ist noch nicht fertig, wir haben die Pixel-Daten
    // für einen weiteren Pixel gesetzt.
    return 0;
}
