//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformEnvironment.cpp
//    Purpose:    Contains SDL-specific interface for the main environment.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2014 Shane T. Mueller <smueller@obereed.net>
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
///////////////////////////////////////////////////////////////////////////
#include "PlatformEnvironment.h"

#include "../../objects/PEnvironment.h"
#include "PlatformWindow.h"
#include "../../base/PList.h"
#include "../../base/PComplexData.h"

#ifdef PEBL_OSX 
#include "SDL.h"
#include "SDL_ttf.h"
#elif defined(PEBL_EMSCRIPTEN)
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#endif

#include <fstream>
#include <iostream>

#include <list>
#include <stdio.h>

#include "../../utility/PError.h"

#if defined PEBL_WIN32
#include <windows.h>
//#include <ddraw.h>  This may be needed for compiling with VC++
#endif

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::list;
using std::ostream;


///Standard Constructor
PlatformEnvironment::PlatformEnvironment(PEBLVideoMode mode, PEBLVideoDepth depth,
                                         bool windowed,bool resizeable,bool unicode):
    PEBLObjectBase(CDT_ENVIRONMENT),
    mVideoMode(mode),
    mVideoDepth(depth),
    mWindowed(windowed),
    mUnicode(unicode),
    mResizeable(resizeable),
    mNumJoysticks(0)
{
    mIsInitialized = false;
}


///Standard Destructor
PlatformEnvironment::~PlatformEnvironment()
{
    mWindows.clear();

    //    SDL_Quit();  //this can cause a crash; SDL_Quit needs to be called at very end.
    // especially if there are global SDL objects like gWin remaining.
    //probably need to explicitly delete the globalvariable map;for now SDL_quit gets
    //called essentially in main().
}


// Inheritable function that is called by friend method << operator of PComplexData
ostream & PlatformEnvironment::SendToStream(ostream& out) const
{

    out << "<SDL PlatformEnvironment>" << flush;
    return out;
}



///This method initiates everything needed to display the main window
void PlatformEnvironment::Initialize()
{
//   std::ofstream cct("CON");
//   freopen( "CON", "w", stdout );
//   freopen( "CON", "w", stderr );

    mIsInitialized = true;

#ifdef PEBL_EMSCRIPTEN
#define SDLINIT_FLAGS SDL_INIT_VIDEO
#else
#define SDLINIT_FLAGS SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_INIT_NOPARACHUTE
#endif
    if ( SDL_Init(SDLINIT_FLAGS) < 0 )
        {

            cerr << "Unable to init SDL: " <<  SDL_GetError() << endl;;
            mIsInitialized = false;
        }
    else{
        
        std::cerr << "SDL INITIALIZED\n";

#ifdef PEBL_EMSCRIPTEN
        if (TTF_Init() < 0 )
#else
        if (!TTF_WasInit() && TTF_Init() < 0 )
#endif
            {
                /* Initialize the TTF library */
                cerr <<  "Couldn't initialize TTF: " << SDL_GetError() << endl;
                mIsInitialized = false;
            } else
            {
                // freopen( "CON", "w", stdout );
                // freopen( "CON", "w", stderr );
                cerr <<"Unicode: " << mUnicode << endl;
                SDL_EnableUNICODE(mUnicode);
                //SDL_EnableUNICODE(1);
                cerr << "Successfully UNICODED" << endl;
                cerr << "Successfully initialized SDL Graphics" << endl;
                char name[32];
                //I get a bad text here and essentially crash cerr???
                //cerr  << "Using audio driver: " <<  SDL_AudioDriverName(name, 32) << endl;
                
            }
        
        

    }
    //This shouldn't be neded, if platformenvironment gets cleaned up alright,
    //but let's do it anyway.
    //atexit(SDL_Quit);
    //    std::cerr << "SDL INITIALIZATION COMPLETE\n";
}



/// This method 'draws' the environment; it iterates through
/// each window in the environment and calls the draw method on each.
bool PlatformEnvironment::Draw()
{
    //Iterate through all child windows and draw them
    list<PWindow*>::iterator p;
    for(p=mWindows.begin(); p!= mWindows.end(); p++)
        {
            (*p)->Draw();
        }


    return true;
}


//overloaded generic PEBLObjectBase methods
bool PlatformEnvironment::SetProperty(std::string name, Variant v)
{
    //this class has no settable properties.
    return false;
}

Variant PlatformEnvironment::GetProperty(std::string name )const
{
    return PEBLObjectBase::GetProperty(name);
}

// ObjectValidationError PlatformEnvironment::ValidateProperty(std::string, Variant v)const
// ObjectValidationError PlatformEnvironment::ValidateProperty(std::string)const;

int PlatformEnvironment::ShowCursor(int val)
{

    if(val)
        {
            return SDL_ShowCursor(SDL_ENABLE);
        }
    else
        {
            return SDL_ShowCursor(SDL_DISABLE);
        }
}


int PlatformEnvironment::SetCursorPosition(int x, int y)
{
    SDL_WarpMouse(x,y);
    return 1;
}


Variant  PlatformEnvironment::GetCursorPosition()
{
    int x = 0;
    int y = 0;
    SDL_PumpEvents();
    SDL_GetMouseState(&x,&y);

    PList * newlist = new PList();
    newlist->PushBack(Variant(x));
    newlist->PushBack(Variant(y));
    counted_ptr<PEBLObjectBase> newlist2 = counted_ptr<PEBLObjectBase>(newlist);
    PComplexData *   pcd = new PComplexData(newlist2);
    return Variant(pcd);
}
void PlatformEnvironment::SetKeyRepeat(bool onoff)
{
    if(onoff)
        SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
    else
        SDL_EnableKeyRepeat(0,0);
}

Variant  PlatformEnvironment::GetMouseState()
{
    int x = 0;
    int y = 0;
    SDL_PumpEvents();
    int button = SDL_GetMouseState(&x,&y);
    int b1 = button & SDL_BUTTON(1);
    int b2 = button & SDL_BUTTON(2);
    int b3 = button & SDL_BUTTON(3);

    PList * newlist = new PList();
    newlist->PushBack(Variant(x));
    newlist->PushBack(Variant(y));
    newlist->PushBack(Variant(b1));
    newlist->PushBack(Variant(b2));
    newlist->PushBack(Variant(b3));

    counted_ptr<PEBLObjectBase> newlist2 = counted_ptr<PEBLObjectBase>(newlist);
    PComplexData *   pcd = new PComplexData(newlist2);
    return Variant(pcd);
}


// This will initialize the joystick subsystem
// and return the number of available joysticks.
int PlatformEnvironment::GetNumJoysticks()
{
    //Initialize joystick subsystem if has not yet been.
    if(SDL_InitSubSystem(SDL_INIT_JOYSTICK)<0)
        {
            PError::SignalWarning("No joysticks available");
        }
    int num   =  SDL_NumJoysticks();

    return num;
}




// This will initialize the joystick subsystem
// and return the number of available joysticks.
Variant PlatformEnvironment::GetJoystick(int index)
{

    if(index < 1 || index > SDL_NumJoysticks())
        {
            PError::SignalFatalError("Requesting an invalid joystick");
        }
    //    SDL_Joystick * joystick = SDL_JoystickOpen(int index);
    PlatformJoystick* joystick = new PlatformJoystick(index+1);



    counted_ptr<PEBLObjectBase> tmp = counted_ptr<PEBLObjectBase>(joystick);

    PComplexData *   pcd = new PComplexData(tmp);
    return Variant(pcd);

}

//
Variant PlatformEnvironment::GetScreenModes()
{

    const SDL_VideoInfo * current = SDL_GetVideoInfo();

    //Get a list of available resolutions and try these out.
    SDL_Rect** modes = SDL_ListModes(NULL, SDL_FULLSCREEN);


    PList * baselist = new PList();
    PComplexData * pcd=NULL;

    modes =SDL_ListModes(NULL,SDL_FULLSCREEN);
    for(int ii=0; modes[ii]; ++ii)
        {

             PList * newlist = new PList();
             newlist->PushBack(Variant(modes[ii]->w));
             newlist->PushBack(Variant(modes[ii]->h));
             counted_ptr<PEBLObjectBase> newlist2 = counted_ptr<PEBLObjectBase>(newlist);
             pcd = new PComplexData(newlist2);
             baselist->PushBack(Variant(pcd));
             //cerr << ii<< ". gVideoWidth <-"<< modes[ii]->w<<"; gVideoHeight<- " << modes[ii]->h <<"\n";
        }

    counted_ptr<PEBLObjectBase> baselist2 = counted_ptr<PEBLObjectBase>(baselist);
    pcd = new PComplexData(baselist2);
    return Variant(pcd);
}


