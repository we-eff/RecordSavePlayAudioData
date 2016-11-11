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
 * File:   main.cpp
 * Author: We Eff
 *
 */

#include "Headers/Display.h"
#include "Headers/Audio.h"
#include "Headers/Button.h"

int main()
{
    Button buttonRecord(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A); // initialization
    Button buttonPlay(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);

    Audio microphonecheck12whatisthis;
    Display LEDs;
    
    LEDs.displayReadySign(); // initialization finished

    while(1)
    {
        if(buttonRecord.isPressed()) // recording always stronger than playing
        {
            if(microphonecheck12whatisthis.isPlaying())
            {
                microphonecheck12whatisthis.stopPlaying();
                LEDs.displayReadySign();
            }
            if(!microphonecheck12whatisthis.isRecording())
            {
                microphonecheck12whatisthis.startRecording();
                LEDs.displayRecordSign();
            }
        }
        else if(buttonPlay.isPressed())
        {
            if(microphonecheck12whatisthis.isRecording())
            {
                microphonecheck12whatisthis.stopRecording();
                LEDs.displayReadySign();
            }
            if(!microphonecheck12whatisthis.isPlaying())
            {
                microphonecheck12whatisthis.startPlaying();
                LEDs.displayPlaySign();
            }
        }
        else // do this if no button is pressed --> as long as a button is pressed: record / play
        {
            if(microphonecheck12whatisthis.isRecording())
            {
                microphonecheck12whatisthis.stopRecording();
                LEDs.displayReadySign();
            }
            if(microphonecheck12whatisthis.isPlaying())
            {
                microphonecheck12whatisthis.stopPlaying();
                LEDs.displayReadySign();
            }
        }
    }
}