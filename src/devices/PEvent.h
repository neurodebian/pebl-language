//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PEven.h
//    Purpose:    Events processed by Event Loop.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2004-2014 Shane T. Mueller <smueller@obereed.net>
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
#ifndef __PEVENT_H__
#define __PEVENT_H__

#include "PKeyboard.h"
#include   "SDL/SDL.h"

//These are some super-lightweight structs for
//representing different events.

//Various useful symbolic enumerations.
enum
	{
        PEBL_UNKNOWN = 0,
		PEBL_UP,
		PEBL_DOWN,
		PEBL_LEFT,
		PEBL_RIGHT,
		PEBL_PRESSED,
		PEBL_RELEASED,
        PEBL_MOVEMENT,
        PEBL_TIMEOUT,
        PEBL_EQUALS,
        PEBL_DIFFERS,
        PEBL_WINDOWWIDTH,
        PEBL_WINDOWHEIGHT
	};



//Keyboard Events
typedef struct
{
	PEBLKey key;
	unsigned int state; //PEBL_PRESSED or PEBL_RELEASED
    int modkeys;   //or'ed set of mod keys.
    Uint16 unicode;
} PEBL_KeyboardEvent;


//Mouse movement events
typedef struct
{
	unsigned int x, y;
	int relx, rely;

} PEBL_MouseMovementEvent;

//Mouse Button event
typedef struct
{
    unsigned int x, y;
    unsigned button; //123 is left middle right
    unsigned state; //0 is up; 1 is down???

} PEBL_MouseButtonEvent;


//Mouse Button event
typedef struct
{
    unsigned state; //the bitstate of the port.

} PEBL_PortEvent;

typedef struct
{
    bool value;  //Not sure if event has anything in it.
} PEBL_MovieRefreshEvent;


typedef struct
{
    bool value;  //Not sure if event has anything in it.
} PEBL_MovieEndEvent;

typedef struct
{
    int w;
    int h;
    //We may need to keep track of which window.
} PEBL_WindowEvent;


typedef struct
{
    int value;

} PEBL_DummyEvent;


class PEvent
{
 public:
	PEvent(PEBL_DEVICE_TYPE type, long unsigned int time);
    PEvent(const PEvent & evt);

	~PEvent();

	PEBL_DEVICE_TYPE GetType() const {return mType;};

    void SetKeyboardEvent(const PEBL_KeyboardEvent & evt);
    void SetMouseMovementEvent(const PEBL_MouseMovementEvent & evt);
    void SetMouseButtonEvent(const PEBL_MouseButtonEvent & evt);
    void SetPortEvent(const PEBL_PortEvent & evt);
    void SetMovieRefreshEvent(const PEBL_MovieRefreshEvent & evt);
    void SetMovieEndEvent(const PEBL_MovieEndEvent & evt);
    void SetWindowEvent(const PEBL_WindowEvent & evt);
    void SetDummyEvent(const PEBL_DummyEvent & evt);

    int GetState(int iface) const;

    unsigned long int GetEventTime(){return mEventTime;};

    PEBL_KeyboardEvent GetKeyboardEvent() const;
    PEBL_MouseMovementEvent GetMouseMovementEvent() const;
    PEBL_MouseButtonEvent GetMouseButtonEvent() const;
    PEBL_MouseButtonEvent GetPortEvent() const;
    PEBL_MovieRefreshEvent GetMovieRefreshEvent() const;
    PEBL_MovieEndEvent GetMovieEndEvent() const;
    PEBL_DummyEvent GetDummyEvent() const;
    PEBL_WindowEvent GetWindowEvent()const;

 private:

	PEBL_DEVICE_TYPE mType;

    union
	{
		PEBL_KeyboardEvent      keyboardEvent;
		PEBL_MouseMovementEvent mouseMovementEvent;
        PEBL_MouseButtonEvent   mouseButtonEvent;
        PEBL_PortEvent          portEvent;
        PEBL_MovieRefreshEvent  movieRefreshEvent;
        PEBL_MovieEndEvent      movieEndEvent;
        PEBL_WindowEvent        windowEvent;
        PEBL_DummyEvent         dummyEvent;

	} mEvent;

    //This keeps track of the time the event was
    //first processed at.
    unsigned long int mEventTime;
};


#endif
