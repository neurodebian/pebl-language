//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PTextBox.cpp
//    Purpose:    Contains generic specification for a read-only text box.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2013 Shane T. Mueller <smueller@obereed.net>
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

#include "PTextBox.h"
#include "PFont.h"
#include "../utility/rc_ptrs.h"
#include "../utility/PEBLUtility.h"
#include "../devices/PKeyboard.h"
#include "../libs/PEBLEnvironment.h"

#include "SDL/SDL.h"   //For Uint16 only
#include <iostream>

using std::cout;
using std::endl;

PTextBox::PTextBox():
    PTextObject(""),
    mEditable(false),
    mCursorPos(0),
    mCursorChanged(true),
    mLineWrap(true)
{
    InitializeProperty("TEXT",Variant(""));
    InitializeProperty("WIDTH",Variant(0));
    InitializeProperty("HEIGHT",Variant(0));
    InitializeProperty("EDITABLE",Variant(false));
    InitializeProperty("CURSORPOS",Variant(0));
    InitializeProperty("NAME",Variant("<TEXTBOX>"));
    InitializeProperty("LINEWRAP",Variant(1));
    InitializeProperty("LINEHEIGHT",Variant(0));
}



PTextBox::PTextBox(std::string text, int width, int height):
    PTextObject(text),
    mEditable(false),
    mCursorPos(0),
    mCursorChanged(true),
    mLineWrap(true)
{
    InitializeProperty("TEXT",Variant(text));
    InitializeProperty("WIDTH",Variant(width));
    InitializeProperty("HEIGHT",Variant(height));
    InitializeProperty("EDITABLE",Variant(false));
    InitializeProperty("CURSORPOS",Variant(0));
    InitializeProperty("NAME",Variant("<TEXTBOX>"));
    InitializeProperty("LINEWRAP",Variant(1));
    InitializeProperty("LINEHEIGHT",Variant(0));
}


PTextBox::PTextBox( PTextBox & text)

{
    mTextChanged = true;
    mText = text.GetText();
    mEditable = false;
    mCursorPos = 0;
    mLineWrap = true;
    InitializeProperty("NAME",Variant("<TEXTBOX>"));
    InitializeProperty("LINEWRAP",Variant(1));
    InitializeProperty("LINEHEIGHT",Variant(0));
}

PTextBox::~PTextBox()
{
}




bool PTextBox::SetProperty(std::string name, Variant v)
{



    if(PTextObject::SetProperty(name,v))
    {
        // If we set it at higher level, don't worry.
    }
    else if (name =="WIDTH") SetWidth(v);
    else if(name == "HEIGHT") SetHeight(v);
    else if(name == "TEXT"){
        SetText(v.GetString());
        mCursorChanged=true;
        mTextChanged=true;}
    else if(name == "EDITABLE")SetEditable(v);
    else if(name == "CURSORPOS") SetCursorPosition(v);
    else if(name == "LINEWRAP") SetLineWrap(v);
    else return false;
    return true;
}


Variant PTextBox::GetProperty(std::string name)const
{
    return PTextObject::GetProperty(name);
}


ObjectValidationError PTextBox::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PTextBox::ValidateProperty(std::string name)const
{
    if(name == "CURSORPOS"| name=="LINEWRAP")
        return OVE_VALID;
    else
        return PTextObject::ValidateProperty(name);
}




//Inserts text at cursor
void PTextBox::InsertText(std::string text)
{

    if(mCursorPos>mText.length())
        mCursorPos=mText.length();

    mText.insert(mCursorPos, text);
    mCursorPos += text.length();
    mTextChanged= true;
    mCursorChanged = true;
    SetProperty("TEXT",mText);
}

void PTextBox::InsertText(const char character)
{

    std::string tmp= " ";
    tmp[0] = character;


    mText.insert(mCursorPos, tmp);
    mCursorPos += 1;
    mTextChanged = true;
    SetProperty("TEXT",mText);

}

//Deletes text at cursor.  negative numbers indicate
//before the cursor
void PTextBox::DeleteText(int length)
{
    if(length > 0)
        {
            mText.erase(mCursorPos, length);
            mTextChanged= true;

        }
    else if (length < 0)
        {

            if(mCursorPos + length < 0)
                {
                    mText.erase(0, mCursorPos);
                    mTextChanged= true;
                    mCursorPos = 0;

                }
            else
                {
                    mText.erase(mCursorPos+length, -length);
                    mTextChanged= true;
                    mCursorPos += length;

                }
        }
    SetProperty("TEXT",mText);
}

int PTextBox::IncrementCursor()
{
    if(AtPrintableCharacter(mCursorPos))
        {
            mCursorPos ++;
        }
    else
        {
            mCursorPos += 1;
        }

            if(mCursorPos > (int)(mText.length()))
                mCursorPos = mText.length();

            mCursorChanged = true;


   return mCursorPos;
}

int PTextBox::DecrementCursor()
{
    if(AtPrintableCharacter(mCursorPos -1))
        mCursorPos --;
    else
        mCursorPos -= 1;

    if(mCursorPos < 0)
        mCursorPos = 0;
    mCursorChanged = true;
    return mCursorPos;
}

//These shadow higher accessors in widget, because
//they need to set the textchanged flag
void PTextBox::SetHeight(int h)
{
    mHeight = h;
    mTextChanged = true;
}

void PTextBox::SetWidth(int w)
{
    mWidth = w;
    mTextChanged = true;
}


void PTextBox::SetLineWrap(bool state)
{
    mLineWrap = state;
}

void PTextBox::HandleKeyPress(int keycode, int modkeys, Uint16 unicode)
{

    //    cout << "handlekeypressing "<< keycode << "|" << modkeys << "|" << unicode << endl;
    //First, handle special keys
    switch(keycode)
        {
        case PEBLKEY_RETURN:
        case PEBLKEY_KP_ENTER:

            InsertText(char(10));
            //mCursorPos++;
            if(mCursorPos > (int) (mText.length()))
                mCursorPos = mText.length();

            break;
        case PEBLKEY_DELETE:
            DeleteText(1);
            break;
        case PEBLKEY_BACKSPACE:
            DeleteText(-1);
            break;case PEBLKEY_UP:
            //Do nothing.  This must be handled by platform.
            break;
        case PEBLKEY_DOWN:
            //Do nothing.  This must be handled by platform.
            break;
        case PEBLKEY_LEFT:
            DecrementCursor();
            break;
        case PEBLKEY_RIGHT:
            IncrementCursor();
            break;

        case PEBLKEY_BACKSLASH:
            //InsertText("\\");
            InsertText(PEBLUtility::TranslateKeyCode(PEBLKey(keycode), modkeys));
          break;

        case PEBLKEY_SPACE:
        case PEBLKEY_EXCLAIM:
        case PEBLKEY_QUOTEDBL:
        case PEBLKEY_HASH:
        case PEBLKEY_DOLLAR:
        case PEBLKEY_AMPERSAND:
        case PEBLKEY_QUOTE:
        case PEBLKEY_LEFTPAREN:
        case PEBLKEY_RIGHTPAREN:
        case PEBLKEY_ASTERISK:
        case PEBLKEY_PLUS:
        case PEBLKEY_COMMA:
        case PEBLKEY_MINUS:
        case PEBLKEY_PERIOD:
        case PEBLKEY_SLASH:
        case PEBLKEY_0:
        case PEBLKEY_1:
        case PEBLKEY_2:
        case PEBLKEY_3:
        case PEBLKEY_4:
        case PEBLKEY_5:
        case PEBLKEY_6:
        case PEBLKEY_7:
        case PEBLKEY_8:
        case PEBLKEY_9:
        case PEBLKEY_COLON:
        case PEBLKEY_SEMICOLON:
        case PEBLKEY_LESS:
        case PEBLKEY_EQUALS:
        case PEBLKEY_GREATER:
        case PEBLKEY_QUESTION:
        case PEBLKEY_AT:
        /*
           Skip uppercase letters
        */
        case PEBLKEY_LEFTBRACKET:

        case PEBLKEY_RIGHTBRACKET:
        case PEBLKEY_CARET:
        case PEBLKEY_UNDERSCORE:
        case PEBLKEY_BACKQUOTE:
        case PEBLKEY_a:
        case PEBLKEY_b:
        case PEBLKEY_c:
        case PEBLKEY_d:
        case PEBLKEY_e:
        case PEBLKEY_f:
        case PEBLKEY_g:
        case PEBLKEY_h:
        case PEBLKEY_i:
        case PEBLKEY_j:
        case PEBLKEY_k:
        case PEBLKEY_l:
        case PEBLKEY_m:
        case PEBLKEY_n:
        case PEBLKEY_o:
        case PEBLKEY_p:
        case PEBLKEY_q:
        case PEBLKEY_r:
        case PEBLKEY_s:
        case PEBLKEY_t:
        case PEBLKEY_u:
        case PEBLKEY_v:
        case PEBLKEY_w:
        case PEBLKEY_x:
        case PEBLKEY_y:
        case PEBLKEY_z:
        /* Numeric keypad */
        case PEBLKEY_KP0:
        case PEBLKEY_KP1:
        case PEBLKEY_KP2:
        case PEBLKEY_KP3:
        case PEBLKEY_KP4:
        case PEBLKEY_KP5:
        case PEBLKEY_KP6:
        case PEBLKEY_KP7:
        case PEBLKEY_KP8:
        case PEBLKEY_KP9:
        case PEBLKEY_KP_PERIOD:
        case PEBLKEY_KP_DIVIDE:
        case PEBLKEY_KP_MULTIPLY:
        case PEBLKEY_KP_MINUS:
        case PEBLKEY_KP_PLUS:
        case PEBLKEY_KP_EQUALS:



            if(1){
                InsertText(PEBLUtility::TranslateKeyCode(PEBLKey(keycode), modkeys));

                
            }


            //This is some internationalization code that doesn't seem to work.
 // else {
                
 //                wchar_t wc = unicode;
                
 //                char buf[4] = {0};
 //                if (wc < 0x80)
 //                    {
 //                        buf[0] = wc;
 //                    }
 //                else if (wc < 0x800)
 //                    {
 //                        buf[0] = (0xC0 | wc>>6);
 //                        buf[1] = (0x80 | wc & 0x3F);
 //                    }
 //                else
 //                    {
 //                        buf[0] = (0xE0 | wc>>12);
 //                        buf[1] = (0x80 | wc>>6 & 0x3F);
 //                        buf[2] = (0x80 | wc & 0x3F);
 //                    }
 //                cout << "[" << buf[0] << "][" << buf[1] << "]" << endl;
 //                InsertText(std::string(buf));
 //                cout << "((International ))))"<< buf<< endl;
 //            }

            break;
            /* Key state modifier keys */
        case PEBLKEY_NUMLOCK:
        case PEBLKEY_CAPSLOCK:
        case PEBLKEY_SCROLLOCK:
        case PEBLKEY_RSHIFT:
        case PEBLKEY_LSHIFT:
        case PEBLKEY_RCTRL:
        case PEBLKEY_LCTRL:
        case PEBLKEY_RALT:
        case PEBLKEY_LALT:
        case PEBLKEY_RMETA:
        case PEBLKEY_LMETA:
        case PEBLKEY_LSUPER:
        case PEBLKEY_RSUPER:
        case PEBLKEY_MODE:
        case PEBLKEY_COMPOSE:
            break;
        default:
            cout << "----------------------\n" << keycode << endl;
            cout << "["<< (PEBLUtility::TranslateKeyCode(PEBLKey(keycode), modkeys))<<"]"<<endl;
            cout << "----------------------\n";

            InsertText(PEBLUtility::TranslateKeyCode(PEBLKey(keycode), modkeys));

            break;
        }
    mCursorChanged=true;
}


bool PTextBox::AtPrintableCharacter(unsigned int x)
{
    unsigned int pos=x;

    if(x> mText.length())
        pos = mText.length();

    if (mText[pos] == 10
        || mText[pos] == 13
        || mText[pos] == 18
        )
        return false;
    else
        return true;
}


std::string PTextBox::ObjectName()const
{
    return "TextBox";
}
