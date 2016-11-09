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
 * File:   Audio.cpp
 * Author: We Eff
 *
 * Created on October 13, 2016, 11:10 AM
 */

#include "Headers/Audio.h"

// already in Audio.h, but just to be sure
#include "Headers/Pin.h"
#include "Ticker.h"
#include <vector>
#include "MicroBitPin.h"

  ////////////////////
 // public methods //
////////////////////
Audio::Audio() :
    Microphone (MICROBIT_ID_IO_P0, MICROBIT_PIN_P0), // P0 is the left most pad (ANALOG/DIGITAL/TOUCH)
    Loudspeaker(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1)  // P1 is the middle    pad (ANALOG/DIGITAL/TOUCH)
#ifdef DEBUG
    , Computer(USBTX, USBRX)
#endif
{
    this->setSamplingPeriod();
    IsRecording = false;
    IsPlaying = false;
}

/*Audio::Audio(const Audio& orig)
{
    // do nothing wrong
}*/

void Audio::startRecording()
{
    if(!IsRecording)
    {
        AudioData.clear(); // start a new recording
        RecordInterrupt.attach_us(this, &Audio::getAnalogValues, SamplingPeriod);
        IsRecording = true;
    }
        else
    {
#ifdef DEBUG
        Computer.puts("already started recording\n\r");
#endif
    }
}

void Audio::stopRecording()
{
    if(IsRecording)
    {
        RecordInterrupt.detach(); // detach whatever function is attached
        IsRecording = false;
    }
        else
    {
#ifdef DEBUG
        Computer.puts("not recording, though nothing to stop\n\r");
#endif
    }
}

void Audio::startPlaying()
{
    if(!IsPlaying)
    {
        CurrentPositionPlay = AudioData.begin();
        PlayInterrupt.attach_us(this, &Audio::setAnalogValues, SamplingPeriod);
        IsPlaying = true;
    }
    else
    {
#ifdef DEBUG
        Computer.puts("already started playing\n\r");
#endif
    }
}

void Audio::stopPlaying()
{
    if(IsPlaying)
    {
        PlayInterrupt.detach(); // detach whatever function is attached
        IsPlaying = false;
    }
        else
    {
#ifdef DEBUG
        Computer.puts("not playing, though nothing to stop\n\r");
#endif
    }
}

Audio::~Audio()
{
}

  /////////////////////
 // private methods //
/////////////////////
void Audio::getAnalogValues()
{
    uint8_t val = Microphone.getAnalogValue();
    AudioData.push_back(val); // can't catch exceptions... it's microcontroller, stupid!
#ifdef DEBUG
    Computer.printf("r: %u\n\r", val);
#endif
}

void Audio::setAnalogValues()
{
    if(CurrentPositionPlay != AudioData.end())
    {
        Loudspeaker.setAnalogValue(*CurrentPositionPlay);
#ifdef DEBUG
        Computer.printf("p: %u\n\r", *CurrentPositionPlay);
#endif
        CurrentPositionPlay++;
    }
    else
    {
        this->stopPlaying(); // stop calling me!
    }
}