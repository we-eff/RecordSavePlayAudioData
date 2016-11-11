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

#include "Headers/Pin.h"

// already in Pin.h, but just to be sure
#include "MicroBitConfig.h"
#include "MicroBitComponent.h"

// not in Pin.h, still needed
//#include "MicroBitSystemTimer.h" // appears not to be needed
//#include "TimedInterruptIn.h"    // appears not to be needed
#include "DynamicPwm.h" // driver, though harmless (no deep connections)
#include "ErrorNo.h"    // return the right error numbers

  ////////////////////
 // public methods //
////////////////////
Pin::Pin(int id, PinName name)
{
    //set mandatory attributes
    this->id = id;
    this->name = name;

    // Power up in a disconnected, low power state.
    // If we're unused, this is how it will stay...
    this->status = 0x00;
    this->pin = NULL;
}

void * Pin::getPin()
{
    return pin;
}

/**
  * Disconnect any attached mBed IO from this pin.
  *
  * Used only when pin changes mode (i.e. Input/Output/Analog/Digital)
  */
void Pin::disconnect()
{
    // This is a bit ugly, but rarely used code.
    // It would be much better to use some polymorphism here, but the mBed I/O classes aren't arranged in an inheritance hierarchy... yet. :-)
    if (status & IO_STATUS_ANALOG_IN){
        NRF_ADC->ENABLE = ADC_ENABLE_ENABLE_Disabled; // forcibly disable the ADC - BUG in mbed....
        delete ((AnalogIn *)pin);
    }

    if (status & IO_STATUS_ANALOG_OUT)
    {
        if(((DynamicPwm *)pin)->getPinName() == name)
            ((DynamicPwm *)pin)->release();
    }

    this->pin = NULL;
    this->status = 0;
}

/**
  * Configures this IO pin as an analog/pwm output, and change the output value to the given level.
  *
  * @param value the level to set on the output pin, in the range 0 - 255
  *
  * @return MICROBIT_OK on success, MICROBIT_INVALID_PARAMETER if value is out of range, or MICROBIT_NOT_SUPPORTED
  *         if the given pin does not have analog capability.
  */
int Pin::setAnalogValue(uint8_t value)
{
    float level = (float)value / float(PIN_MAX_OUTPUT);

    //obtain use of the DynamicPwm instance, if it has changed / configure if we do not have one
    obtainAnalogChannel();

    return ((DynamicPwm *)pin)->write(level);
}

/**
  * Configures this IO pin as an analogue input (if necessary), and samples the Pin for its analog value.
  *
  * @return the current analogue level on the pin, in the range 0 - 255, or
  *
  * @code
  * Pin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0);
  * P0.getAnalogValue(); // P0 is a value in the range of 0 - 255
  * @endcode
  */
uint8_t Pin::getAnalogValue()
{
    // Move into an analogue input state if necessary.
    if (!(status & IO_STATUS_ANALOG_IN)){
        disconnect();
        pin = new AnalogIn(name);
        status |= IO_STATUS_ANALOG_IN;
    }

    //perform a read!
    return ((AnalogIn *)pin)->read_u8();
}

/**
  * Determines if this IO pin is currently configured as an input.
  *
  * @return 1 if pin is an analog input, 0 otherwise.
  */
int Pin::isInput()
{
    return (status & IO_STATUS_ANALOG_IN) == 0 ? 0 : 1;
}

/**
  * Determines if this IO pin is currently configured as an output.
  *
  * @return 1 if pin is an analog output, 0 otherwise.
  */
int Pin::isOutput()
{
    return (status & IO_STATUS_ANALOG_OUT) == 0 ? 0 : 1;
}

  /////////////////////
 // private methods //
/////////////////////
void Pin::obtainAnalogChannel()
{
    // Move into an analogue input state if necessary, if we are no longer the focus of a DynamicPWM instance, allocate ourselves again!
    if (!(status & IO_STATUS_ANALOG_OUT) || !(((DynamicPwm *)pin)->getPinName() == name)){
        disconnect();
        pin = (void *)DynamicPwm::allocate(name);
        status |= IO_STATUS_ANALOG_OUT;
    }
}