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
 * File:   Pin.h
 * Author: We Eff
 *
 * Created on November 7, 2016, 3:38 PM
 */

#ifndef PIN_H
#define PIN_H

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"

#define IO_STATUS_ANALOG_IN                 0x04        // Pin is Analog in
#define IO_STATUS_ANALOG_OUT                0x08        // Pin is Analog out

#define MICROBIT_PIN_P0                     P0_3        //P0 is the left most pad (ANALOG/DIGITAL) used to be P0_3 on green board
#define MICROBIT_PIN_P1                     P0_2        //P1 is the middle pad (ANALOG/DIGITAL)
#define MICROBIT_PIN_P2                     P0_1        //P2 is the right most pad (ANALOG/DIGITAL) used to be P0_1 on green board

#define PIN_MAX_OUTPUT                      255

/**
  * Class definition for Pin.
  *
  * Commonly represents an I/O pin on the edge connector.
  */
class Pin : public MicroBitComponent
{
    // The mbed object looking after this pin at any point in time (untyped due to dynamic behaviour).
    void *pin;

    /**
      * Disconnect any attached mBed IO from this pin.
      *
      * Used only when pin changes mode (i.e. Input/Output/Analog/Digital)
      */
    void disconnect();

    public:

    // mbed PinName of this pin.
    PinName name;

    /**
      * Constructor.
      * Create a MicroBitPin instance, generally used to represent a pin on the edge connector.
      *
      * @param id the unique EventModel id of this component.
      *
      * @param name the mbed PinName for this MicroBitPin instance.
      *
      * @param capability the capabilities this MicroBitPin instance should have.
      *                   (PIN_CAPABILITY_DIGITAL, PIN_CAPABILITY_ANALOG, PIN_CAPABILITY_AD, PIN_CAPABILITY_ALL)
      *
      * @code
      * MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);
      * @endcode
      */
    Pin(int id, PinName name);

    /**
      * Configures this IO pin as an analog/pwm output, and change the output value to the given level.
      *
      * @param value the level to set on the output pin, in the range 0 - 1024
      *
      * @return MICROBIT_OK on success, MICROBIT_INVALID_PARAMETER if value is out of range, or MICROBIT_NOT_SUPPORTED
      *         if the given pin does not have analog capability.
      */
    int setAnalogValue(uint8_t value);

    /**
      * Configures this IO pin as an analogue input (if necessary), and samples the Pin for its analog value.
      *
      * @return the current analogue level on the pin, in the range 0 - 1024, or
      *         MICROBIT_NOT_SUPPORTED if the given pin does not have analog capability.
      *
      * @code
      * MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_BOTH);
      * P0.getAnalogValue(); // P0 is a value in the range of 0 - 1024
      * @endcode
      */
    uint8_t getAnalogValue();

    /**
      * Determines if this IO pin is currently configured as an input.
      *
      * @return 1 if pin is an analog or digital input, 0 otherwise.
      */
    int isInput();

    /**
      * Determines if this IO pin is currently configured as an output.
      *
      * @return 1 if pin is an analog or digital output, 0 otherwise.
      */
    int isOutput();
    
    private:
        
    /**
      * Performs a check to ensure that the current Pin is in control of a
      * DynamicPwm instance, and if it's not, allocates a new DynamicPwm instance.
      */
    void obtainAnalogChannel();
};

#endif /* PIN_H */

