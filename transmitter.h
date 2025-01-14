/*
    fm_transmitter - use Raspberry Pi as FM transmitter

    Copyright (c) 2019, Marcin Kondej
    All rights reserved.

    See https://github.com/markondej/fm_transmitter

    Redistribution and use in source and binary forms, with or without modification, are
    permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors may be
    used to endorse or promote products derived from this software without specific
    prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
    SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
    TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
    BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
    WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "wave_reader.h"

using std::string;

class Transmitter
{
    public:
        virtual ~Transmitter();
        static Transmitter &getInstance();
        void play(WaveReader &reader, double frequency, double bandwidth, unsigned char dmaChannel, bool preserveCarrierOnExit);
        void stop();
    private:
        Transmitter();
        Transmitter(const Transmitter &source);
        Transmitter &operator=(const Transmitter &source);
        bool allocateMemory(unsigned size);
        void freeMemory();
        float getSrcClkFreq();
        unsigned getPeripheralVirtAddress();
        unsigned getPeripheralSize();		
        unsigned getMemoryAddress(volatile void *object);
        unsigned getPeripheralAddress(volatile void *object);
        static void *getPeripheral(unsigned offset);
        static void *transmit(void *params);

        static void *peripherals;
        static bool transmitting, clockInitialized, preserveCarrier;
        unsigned memSize, memAddress, memHandle;
        void *memAllocated;
        int mBoxFd;
};

#endif // TRANSMITTER_H
