//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/Keyboard.cpp
//    Purpose:    Contains SDL-specific interface for the keyboard handler
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2005 Shane T. Mueller <smueller@obereed.net>
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
#include "PlatformKeyboard.h"
#include "../../devices/PKeyboard.h"
#include "../../devices/DeviceState.h"

#include "SDL/SDL.h"
#include "PlatformTimer.h"


#include <stdio.h>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::list;
using std::ostream;



/// This is the SDL-specific binding for the keyboard handler.
/// SDL key events can be accessed in multiple ways. First, they can
/// be handled through the standard SDL event queue. Key-Up and Key-Down 
/// events are signalled through this loop. Also, the entire state of the 
/// keyboard can be polled at a given point in time, and this state 
/// can be examined.


/// For optimal performance, we should select a subset of keys to examine
/// and poll them until one flips.

///Standard Constructor
PlatformKeyboard::PlatformKeyboard()
    //    mCDT(CDT_KEYBOARD)
{
 
    //EMSCRIPTEN uses sdl 2, which replaces getkeystat with getkeyboardstate
#if defined PEBL_EMSCRIPTEN
    mKeyboardState = SDL_GetKeyboardState(NULL);  
    SDL_PumpEvents();
#else
    mKeyboardState = SDL_GetKeyState(NULL);  
    SDL_PumpEvents();
#endif
}


///Standard Destructor
PlatformKeyboard::~PlatformKeyboard()
{
 
}


///Primitive key event poller.
PEBLKey PlatformKeyboard::IsKeyDown(PEBLKey key) const
{
    if(key == PEBLKEY_ANYKEY)
        {
            return IsAnyKeyDown();
        }
    else
        {
            SDL_PumpEvents();   
            if( mKeyboardState[key] == 1)
                return key;
            else
                return PEBLKEY_NOTHING;

        }
}



///Primitive key event poller for 'up' state.  If
/// the key argument is the 'anykey' it will return true
/// if every key is unpressed.   we want to bo able to return the value of 
///the key pressed, thus determining which key was pressed when anykey is being tested.

bool PlatformKeyboard::IsKeyUp(PEBLKey key) const
{

    //If the key is 'anykey', what you are really asking is if there
    //are any keys that are not up. This is a semantic distortion, because
    //logically, you should be asking whether ALL keys are pressed, which
    //is pretty ridiculous.
    //
    if(key == PEBLKEY_ANYKEY)
        {
            PEBLKey key = IsAnyKeyDown();
            return key;
        }
    else
        {
            SDL_PumpEvents();   
            if(mKeyboardState[key])
                return key;
            else
                return PEBLKEY_NOTHING; //==0==false
        }
}

   
///This will wait for ANY key event and return it.
PEBLKey PlatformKeyboard::IsAnyKeyDown() const
{

    //Update the keyboard state from SDL function.
    SDL_PumpEvents();  
        
    //Skip uppercase letters: do standard letters
    for(int i = 91; i<=127; i++)
        {
            if(mKeyboardState[i]) return PEBLKey(i);
        }
    
    //Go through first 64
    for(int i = 0; i<=64; i++)
        {
            if(mKeyboardState[i]) return PEBLKey(i);
        }
    
    
    //Keypad, function keys, etc.
    for(int i = 256; i<=296; i++)
        {
            if(mKeyboardState[i]) return PEBLKey(i);
        }
    
    
    
    //Modkeys/misc
    for(int i = 300; i<=322; i++)
        {
            if(mKeyboardState[i]) return PEBLKey(i);
        }
 
  
   //International letters (out of order, but of lower priority)
    for(int i = 160; i<=255; i++)
        {
            if(mKeyboardState[i]) return PEBLKey(i);
        }
    
    return PEBLKEY_NOTHING; //This indicates that nothing was pressed.  
}
 

int PlatformKeyboard::GetState(int iface) const
{
    PEBLKey key = (PEBLKey)iface;
    return (int)IsKeyUp(key);
}


// Inheritable function that is called by friend method << operator of PComplexData
ostream & PlatformKeyboard::SendToStream(ostream& out) const
{
    
    out << "<SDL PlatformKeyboard>" << flush;
    return out;
}


