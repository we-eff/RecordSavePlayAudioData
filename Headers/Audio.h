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
 * File:   Audio.h
 * Author: We Eff
 *
 * Created on October 13, 2016, 11:10 AM
 */

#ifndef AUDIO_H
#define AUDIO_H

#include "Headers/Pin.h"
#include "Ticker.h"
#include <vector>

#define DEBUG

#ifdef DEBUG
#include "RawSerial.h"
#define MICROBIT_SERIAL_DEFAULT_BAUD_RATE   115200
#endif

#define DEFAULT_SAMPLING_FQ 2 //40000000 // 40 kHz
#define US_PER_S 1000000 // 10^6

typedef std::vector<uint8_t> TCont; // ADC has a resolution of 12 bits and a tolerance of about 2 bits --> 8 bits sufficient (and memory-efficient!)

class Audio
{
    Pin Microphone;
    Pin Loudspeaker;
    TCont AudioData;
    Ticker RecordInterrupt;
    Ticker PlayInterrupt;
    timestamp_t SamplingPeriod; // in us
    bool IsRecording;
    bool IsPlaying;
    TCont::iterator CurrentPositionPlay;
#ifdef DEBUG
    RawSerial Computer;
#endif
public:
    Audio();
    //Audio(const Audio& orig);
    bool isRecording()
    {
        return IsRecording;
    }
    bool isPlaying()
    {
        return IsPlaying;
    }
    void startRecording();
    void stopRecording();
    void startPlaying();
    void stopPlaying();
    void setSamplingPeriod(uint32_t fq = DEFAULT_SAMPLING_FQ)
    {
        SamplingPeriod = US_PER_S / fq;
    }
    virtual ~Audio();
private:
    void getAnalogValues();
    void setAnalogValues();
};

#endif /* AUDIO_H */