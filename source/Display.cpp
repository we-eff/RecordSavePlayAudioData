/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

/* 
 * File:   Display.cpp
 * Author: We Eff
 *
 * Created on October 5, 2016, 1:15 PM
 */

#include "Headers/Display.h"

// already in Display.h, but just to be sure
#include "MicroBitMatrixMaps.h"
#include "PortOut.h"

  ////////////////////
 // public methods //
////////////////////
Display::Display(const MatrixMap &map) :
    LEDMatrixMap(map)
{
    for (int i = 0; i < LEDMatrixMap.rows; i++)
        RowMask |= 0x01 << i;

    for (int i = 0; i < LEDMatrixMap.columns; i++)
        ColMask |= 0x01 << i;
    
    LEDMatrix = new mbed::PortOut(Port0, (ColMask << LEDMatrixMap.columnStart) | (RowMask << LEDMatrixMap.rowStart)); // don't touch the reserved bits!
}

/*Display::Display(const Display& orig)
{
    // do nothing wrong
}*/

void Display::displayRecordSign()
{
    // according to MicroBitMatrixMaps.h - microBitDisplayMap (refering to a 9x3 display, called "SB2")
    uint16_t cols = 0x1FB; // show all columns, but not the third (center dot, 0x1FB ... 0b000111111011 - third bit unset)
    uint16_t rows = 0x02;  // show only the center row (0x02 ... 0b0010 - second bit set)
    
    // fitting all into the bit pattern: bits 0 ... 3, 16 ... 32: reserved, bits 4 ... 12: columns (inverted), bits 13 ... 15: rows
    uint32_t RecordSign = (((~cols) & ColMask) << LEDMatrixMap.columnStart) | ((rows & RowMask) << microbitMatrixMap.rowStart);

    // get leds alight
    *LEDMatrix = RecordSign; 
}

void Display::displayPlaySign()
{
    // according to MicroBitMatrixMaps.h - microBitDisplayMap (refering to a 9x3 display, called "SB2")
    uint16_t cols = 0x049; // show first, fourth and seventh column (0x049 ... 0b000001001001)
    uint16_t rows = 0x02;  // show only the center row (0x02 ... 0b0010 - second bit set)
    
    // fitting all into the bit pattern: bits 0 ... 3, 16 ... 32: reserved, bits 4 ... 12: columns (inverted), bits 13 ... 15: rows
    uint32_t PlaySign = (((~cols) & ColMask) << LEDMatrixMap.columnStart) | ((rows & RowMask) << microbitMatrixMap.rowStart);

    // get leds alight
    *LEDMatrix = PlaySign; 
}

void Display::displayReadySign()
{
    // according to MicroBitMatrixMaps.h - microBitDisplayMap (refering to a 9x3 display, called "SB2")
    uint16_t cols = 0x1F8; // show fourth to nineth column (0x1F8 ... 0b000111111000)
    uint16_t rows = 0x07;  // show all rows (0x07 ... 0b0111)
    
    // fitting all into the bit pattern: bits 0 ... 3, 16 ... 32: reserved, bits 4 ... 12: columns (inverted), bits 13 ... 15: rows
    uint32_t ReadySign = (((~cols) & ColMask) << LEDMatrixMap.columnStart) | ((rows & RowMask) << microbitMatrixMap.rowStart);

    // get leds alight
    *LEDMatrix = ReadySign; 
}

void Display::displayErrorSign()
{
    // according to MicroBitMatrixMaps.h - microBitDisplayMap (refering to a 9x3 display, called "SB2")
    uint16_t cols = 0x1FF; // show all columns (0x1FF ... 0b000111111111)
    uint16_t rows = 0x07;  // show all rows (0x07 ... 0b0111)
    
    // fitting all into the bit pattern: bits 0 ... 3, 16 ... 32: reserved, bits 4 ... 12: columns (inverted), bits 13 ... 15: rows
    uint32_t ErrorSign = (((~cols) & ColMask) << LEDMatrixMap.columnStart) | ((rows & RowMask) << microbitMatrixMap.rowStart);

    // get leds alight
    *LEDMatrix = ErrorSign; 
}

Display::~Display()
{
    delete LEDMatrix;
}