//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformAudioIn.h
//    Purpose:    Contains platform-specific sound recording routines
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2011 Shane T. Mueller <smueller@obereed.net>
//    License:    GPL 2
//
//
//
//     This file is part of the PEBL project.
//
//    PEBL is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    PEBL is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with PEBL; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////
#ifndef __PLATFORMAUDIOIN_H__
#define __PLATFORMAUDIOIN_H__
#ifdef PEBL_AUDIOIN
//#include "../../devices/PAudioIn.h"
#include "../../base/Variant.h"
#include "../../base/PEBLObject.h"
#ifdef PEBL_OSX

#else
#include "SDL/SDL.h"
#include "SDL/SDL_audioin.h"
#endif

//#include "SDL/SDL_audio.h"
  
#include "PlatformAudioOut.h"

#include <string>

//struct SoundInfo{
//  SDL_AudioSpec spec;
//	Uint8 *audio;            //A pointer to the buffer.
//	Uint32 audiolen;       //length of the buffer (in bytes, not samples!!!)
//  Uint32 audiopos;
//  Uint8 bytesPerSample;  //size of a sample
//	Uint32 recordpos;      //current index in the buffer (in samples, not bytes)
//  Uint32 counter;        //A counter to use that keeps track of samples
//                       //since the beginning of recording.
//
//    const char*name;
//};

// struct AudioInfo{
//     SDL_AudioSpec spec;
//     Uint8   *audio;			/* Pointer to wave data */
//     Uint32   audiolen;		/* Length of wave data */
//     int      audiopos;		/* Current play position */
//     int      volume;           /* Relative volume. 0-100*/
//     const char*    name;
// };
  
class PlatformAudioIn: public PEBLObjectBase
{
 public:
    PlatformAudioIn();
    ~PlatformAudioIn();
    AudioInfo * GetAudioOutBuffer()    ;
    AudioInfo * ReleaseAudioOutBuffer();
    bool UseBuffer(AudioInfo* buffer);
    bool CreateBuffer(int size);
    bool RecordToBuffer();
    bool Record();
    bool Stop();
    

    Variant VoiceKey(double thresh, unsigned int sustain);
    void SaveBufferToWave(Variant filename)    ;
    bool Initialize(int);

    double Power(Sint16 * data, int length);


    void ComputeStats(Sint16 * data, int length,
               double&,double&,
               int&,int&,double &    );

private:
    unsigned int mSampleRate;
    Uint16 mAudioFormat;
    unsigned int mBytesPerSample;
    unsigned int mSamples;

    AudioInfo *mWave;
};


#endif
#endif
