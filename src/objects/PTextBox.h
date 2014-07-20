//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PTextBox.h
//    Purpose:    Contains generic specs for non-editable a text box
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
#ifndef __PTEXTBOX_H__
#define __PTEXTBOX_H__

#include "SDL/SDL.h"  //For Uint16 definition
#include "PTextObject.h"
#include "PFont.h"
#include "../utility/rc_ptrs.h"
#include <string>

///
/// This class is the basic generic text box.

class PTextBox: virtual public PTextObject
{
public:
    PTextBox();
    PTextBox(std::string text, int width, int height);
    PTextBox(PTextBox & textbox);
    virtual ~PTextBox();


    //overloaded generic PObject methods
    virtual bool SetProperty(std::string, Variant v);
    virtual Variant GetProperty(std::string)const;
    virtual ObjectValidationError ValidateProperty(std::string, Variant v)const;
    virtual ObjectValidationError ValidateProperty(std::string)const;


    virtual void SetHeight(int h);
    virtual void SetWidth(int w);

    virtual void InsertText(std::string character);
    virtual void InsertText(char character);

    virtual void DeleteText(int length);

    virtual void SetEditable(bool val){mEditable = val; mCursorChanged=true;};
    virtual bool GetEditable(){return mEditable;};

    virtual void SetCursorPosition(int pos){mCursorChanged = true; mCursorPos = pos;};
    virtual int GetCursorPosition(){return mCursorPos;};

    virtual int IncrementCursor();
    virtual int DecrementCursor();

    virtual void SetLineWrap(bool state);

    virtual void HandleKeyPress(int keycode, int modkeys,Uint16 unicode);


    virtual bool AtPrintableCharacter(unsigned int x);

    virtual std::string ObjectName() const;

private:


protected:


    virtual std::ostream & SendToStream(std::ostream& out) const{return out;};


    bool mEditable;       //Whether the box is editable.
    int  mCursorPos;      //The character position of the cursor.
    bool mCursorChanged;  //True if cursor has moved.
    bool mLineWrap;       //Should lines get wrapped, or just truncated?

};


#endif

