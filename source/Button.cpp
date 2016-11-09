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
 * File:   Button.cpp
 * Author: We Eff
 *
 * Created on November 7, 2016, 1:21 PM
 */

#include "Headers/Button.h"

// already in Button.h, but just to be sure
#include "MicroBitComponent.h"

// not in Button.h, still needed
#include "MicroBitSystemTimer.h"
  ////////////////////
 // public methods //
///////////////////
Button::Button(PinName name, uint16_t id, PinMode mode) : pin(name, mode)
{
    this->id = id;
    this->name = name;
    this->sigma = 0;
    system_timer_add_component(this);
}

/**
  * periodic callback from MicroBit system timer.
  *
  * Check for state change for this button, and fires various events on a state change.
  */
void Button::systemTick()
{
    //
    // If the pin is pulled low (touched), increment our cumulative counter.
    // otherwise, decrement it. We're essentially building a lazy follower here.
    // This makes the output debounced for buttons, and desensitizes touch sensors
    // (particularly in environments where there is mains noise!)
    //
    if(!pin)
    {
        if (sigma < MICROBIT_BUTTON_SIGMA_MAX)
            sigma++;
    }
    else
    {
        if (sigma > MICROBIT_BUTTON_SIGMA_MIN)
            sigma--;
    }

    // Check to see if we have off->on state change.
    if(sigma > MICROBIT_BUTTON_SIGMA_THRESH_HI && !(status & MICROBIT_BUTTON_STATE))
    {
        // Record we have a state change, and raise an event.
        status |= MICROBIT_BUTTON_STATE;
    }

    // Check to see if we have on->off state change.
    if(sigma < MICROBIT_BUTTON_SIGMA_THRESH_LO && (status & MICROBIT_BUTTON_STATE))
    {
        status = 0;
    }
}

/**
  * Tests if this Button is currently pressed.
  *
  * @code
  * if(buttonA.isPressed())
  *     display.scroll("Pressed!");
  * @endcode
  *
  * @return 1 if this button is pressed, 0 otherwise.
  */
int Button::isPressed()
{
    return status & MICROBIT_BUTTON_STATE ? 1 : 0;
}

/**
  * Destructor for MicroBitButton, where we deregister this instance from the array of fiber components.
  */
Button::~Button()
{
    system_timer_remove_component(this);
}