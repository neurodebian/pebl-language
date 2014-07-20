//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformTextBox.cpp
//    Purpose:    Contains SDL-specific interface for the text boxes.
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

#include "PlatformTextBox.h"
#include "../../objects/PTextBox.h"
#include "PlatformFont.h"
#include "SDLUtility.h"


#include "../../base/PComplexData.h"
#include "../../devices/PKeyboard.h"

#include "../../utility/rc_ptrs.h"
#include "../../utility/PError.h"
#include "../../utility/PEBLUtility.h"

#ifdef PEBL_OSX
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#endif



#include <stdio.h>
#include <string>
#include <algorithm>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::list;
using std::ostream;
using std::string;


PlatformTextBox::PlatformTextBox(string text, counted_ptr<PEBLObjectBase> font, int width, int height):
    PlatformWidget(),
    PTextBox(text, width, height)


{
    mCDT = CDT_TEXTBOX;
    mWidth = width;
    mHeight = height;
    SetFont(font);
    SetText(text);



    Draw();
    //    if(!RenderText()) cerr << "Unable to render text.\n";
}


PlatformTextBox::PlatformTextBox(const PlatformTextBox & text):
    PlatformWidget(),
    PTextBox(text.GetText(), text.GetWidth(), text.GetHeight())


{
    mCDT = CDT_TEXTBOX;
    mWidth = text.GetWidth();
    mHeight = text.GetHeight();

    SetFont(text.GetFont());
    Draw();
    //    if(!RenderText()) cerr << "Unable to render text.\n";
}


///Standard Destructor
PlatformTextBox::~PlatformTextBox()
{

    // PlatformWidget frees mSurface,
}

// Inheritable function that is called by friend method << operator of PComplexData
ostream & PlatformTextBox::SendToStream(ostream& out) const
{
    out << "<SDL PlatformTextBox: [" << mText << "] in " << *mFont << ">" <<flush;
    return out;
}




/// This method should be called when the font is initialized or the text is changed.
/// It will make the mSurface pointer hold the appropriate image.
bool  PlatformTextBox::RenderText()
{
    //free the memory if it is currently pointing at something.
    if(mSurface)  SDL_FreeSurface(mSurface);

    //create a new surface on which to render the text.

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x00000000;

#else

    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0x00000000;

#endif


    //Make a surface of the prescribed size.
    mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, mWidth, mHeight, 32,
                                    rmask, gmask, bmask, amask);
    if(!mSurface)  PError::SignalFatalError("Surface not created in TextBox::RenderText.");


    //Fill the box with the background color of the font.
    SDL_FillRect(mSurface, NULL, SDL_MapRGBA(mSurface->format,
                                             mBackgroundColor.GetRed(),
                                             mBackgroundColor.GetGreen(),
                                             mBackgroundColor.GetBlue(),
                                             mBackgroundColor.GetAlpha()));



    //First, find the height of the text when rendered with the font.
    int height = mFont->GetTextHeight(mText);

    //Now, go through the text letter by letter and word by word until it won't fit on a line any longer.
    unsigned int linestart = 0;
    unsigned int linelength = 0;
    unsigned int totalheight = 0;

    SDL_Surface * tmpSurface;
    std::vector<int>::iterator i = mBreaks.begin();
    linestart  = 0;


    while(i != mBreaks.end() && totalheight < (unsigned int) mHeight)
        {


            //mBreaks holds the 'starting' positions of each line.
            linelength = *i - linestart;
            if(linelength>0)
                {


                    //cout << "direction in ptb: " << mDirection << endl;
                    SDL_Rect to;
                    if(mDirection == 1)
                        {
                            tmpSurface = mFont->RenderText(mText.substr(linestart, linelength).c_str());
                            SDL_Rect tmprect = {0,totalheight,tmpSurface->w, tmpSurface->h};
                            to = tmprect;
                        }
                    else
                        {



                            std::string tmp = mText.substr(linestart,linelength);

                            //
                            std::string rtext = PEBLUtility::strrev_utf8(tmp);



                            //Re-render the text using the associated font.
                            tmpSurface = mFont->RenderText(rtext.c_str());
                            // don't forget to free the string after finished using it

                            //delete[] rtext;
                            //rtext = NULL;
                            SDL_Rect tmprect = {(mSurface->w-tmpSurface->w),totalheight,tmpSurface->w, tmpSurface->h};
                            to = tmprect;

                        }


                    SDL_BlitSurface(tmpSurface, NULL, mSurface,&to);
                    SDL_FreeSurface(tmpSurface);
                }

            totalheight += height;
            linestart = *i;
            i++;

        }


    if(mEditable)
        {
            DrawCursor();
        }

    //If mSurface is null, then rendering failed.
    if(mSurface)
        return true;
    else
        return false;
}


bool PlatformTextBox::SetProperty(std::string name, Variant v)
{

    if(name == "TEXT")
        {
            SetText(v);
        }
    else if(PTextBox::SetProperty(name,v))
    {
        // If we set it at higher level, don't worry.
    }
    else if (name == "FONT")
        {
            SetFont(v.GetComplexData()->GetObject());
        }
    else return false;

    return true;
}



void PlatformTextBox::SetFont(counted_ptr<PEBLObjectBase> font)
{

    mFontObject = font;
    mFont = dynamic_cast<PlatformFont*>(mFontObject.get());
    PWidget::SetBackgroundColor(mFont->GetBackgroundColor());
    mTextChanged = true;
    //Re-render the text onto mSurface
    if(!RenderText()) cerr << "Unable to render text.\n";

}


void PlatformTextBox::SetText(string text)
{
    //Chain up to parent method.
    PTextObject::SetText(text);
    //mCursorPos = 0;
    mCursorChanged = true;
    mTextChanged = true;
    Draw();
    //Re-render the text onto mSurface
    //    if(!RenderText()) cerr << "Unable to render text.\n";

}



void PlatformTextBox::FindBreaks()
{

    //First, find the height and width of the text when rendered with the font.
    int height = mFont->GetTextHeight(mText);

    //Set this directly as a property; no need to check with PTextBox, which doesn't do anything with it.
    PEBLObjectBase::SetProperty("LINEHEIGHT",Variant(height));
    //Now, go through the text letter by letter and word by word until
    //it won't fit on a line any longer.

    unsigned int linestart = 0;     //The start of the current line
    unsigned int newlinestart = 0;  //The start of the NEXT line
    unsigned int linelength = 0;
    unsigned int totalheight = 0;

    mBreaks.clear();


    //Now, let's reserve space in mBreaks, roughly twice the amount we
    //think we need. This will make adding elements take less time.

    int width = mFont->GetTextWidth(mText);
    mBreaks.reserve(width / mWidth * 2);


    while( (totalheight < (unsigned int) mHeight  &&
            newlinestart < mText.size()))
        {

            linelength   = FindNextLineBreak(linestart);

            //Increment the placekeepers:
            //This is where the next line will start.

            newlinestart = linestart+ linelength;
            totalheight += height;

            mBreaks.push_back(newlinestart);
            linestart=newlinestart;

        }




}


/// This returns the number of characters after curposition
/// that the next line should break at.
///

int PlatformTextBox::FindNextLineBreak(unsigned int curposition)
{
    unsigned int sublength = 0;
    unsigned int lastsep  = 0;
    unsigned int sep      = 0;
    std::string tmpstring;

    //loop through the entire text from curposition on.
    while (curposition + sublength < mText.size()+1)
        {

            //Test to see if curposition is a '10' or a '0' (a hard/explicit line break).  If so, this is a line break.
            if(mText[curposition + sublength] == 10
               || mText[curposition+sublength]==0)
                //|| curposition + sublength == mText.size())
                {

                    tmpstring = mText.substr(curposition,sublength);
                    //If the width of the current line is too big, break at the last separator.
                    if(mFont->GetTextWidth(tmpstring) > (unsigned int)mWidth)
                        {

                            //if we are now too long, we should back up to the previous
                            //break; unless that break was the beginning of the line.  If
                            //that is the case, back up one character, and crudely break
                            //within a text line.

                            //we need to return the best linebreak here.
                            if(sep >0)
                                {

                                    return sep+1;
                                }
                            if(lastsep>0)
                                {

                                    return lastsep+1;
                                }
                            else
                                {


                                    if(mLineWrap)
                                        {
                                            //We have no natural break 'sep' on this line,
                                            //and the current line is too long.
                                            while(mFont->GetTextWidth(tmpstring) >(unsigned int)mWidth)
                                                {

                                                    sublength--;
                                                    tmpstring = mText.substr(curposition,sublength);

                                                }

                                            return sublength;
                                        }
                                    else
                                        {
                                            return sublength+1;
                                        }
                                }
                        }
                    else
                        {

                            return sublength+1;
                        }
                }


            //if we allow line wrapping, allow lines to wrap at other places too.
            if(mLineWrap)
                {

                    if(mText[curposition + sublength] == ' '
                       || mText[curposition + sublength] == '-'
                       || curposition + sublength == mText.size())
                        {
                            //either of these are word breaks; potential line breaks.
                            //Increment word separator holders
                            lastsep = sep;
                            sep = sublength ;

                            tmpstring = mText.substr(curposition, sublength);

                            //Check the size of the line.
                            if(mFont->GetTextWidth(tmpstring) > (unsigned int)mWidth)
                                {
                                    //the text is too big for a single line, so return the last word break, but only
                                    //if the size is greater than 0. In that case, return the current separator, which
                                    //will not fit on the line, but it will get chopped off.

                                    if(lastsep != 0)
                                        {

                                            return lastsep+1;
                                        }
                                    else
                                        {

                                            return sep+1;
                                        }
                                }
                        }


                }
            sublength++;
        }
    //The rest of the text must fit in the space allotted; return that number.


    return sublength-1;
}




/// Given an x,y position, this will return an integer specifying
/// the character in mText before which the cursor should be drawn.
int PlatformTextBox::FindCursorPosition(int x, int y)
{

    if(mText.length()==0)
        {
            return 0;
        }

    //Find the height of a line.
    int height = mFont->GetTextHeight(mText);

    if(y > mHeight) y = mHeight;
    if(y < 0) y = 0;

    //The line will just be y / height, rounded down
    unsigned int linenum = y / height;


    //Change the line number to the last one if it is too large.
    //The last element of mBreaks is the 'end' of the text; not really a break for
    //our purposes.

    if(linenum >= mBreaks.size())
        linenum = mBreaks.size()-1;

    int startchar;
    if(linenum==0)
        startchar = 0;
    else
        startchar = mBreaks[linenum-1];


    int length = mBreaks[linenum] - startchar;
    int charnum = mFont->GetPosition(mText.substr(startchar, length), x);

    //finally, if the current cursor position is a non-printing character (i.e. a carriage return)
    //back up one

    if(!AtPrintableCharacter(charnum + startchar -1))
    {
        if(charnum + startchar > 0)
            charnum--;
    }
    return charnum + startchar;
}


//This will draw a 'cursor' at a specified character.
void PlatformTextBox::DrawCursor()
{
    //Find x and y of position.
    int x = 0;
    int y = 0;

    int height = mFont->GetTextHeight(mText);
    int width =  GetWidth();
    unsigned int i = 0;
    int linestart = 0;


    x = width-1;    //Initialize x with the biggest value it can have.
    if(mCursorPos==0)
        {
            x=0;

        } else {
        //The cursor is not at the beginning.
        //mBreaks has found the line breaks already.
            while(i < mBreaks.size())
                {
                    //increment x,y while we go, so that if we get orphaned text,
                    //we still get a decent cursor position.
                    y = i * height;

                    //mBreaks is the position of the first character on each line
                    if(mBreaks[i] >= mCursorPos)
                        {

                            x =  mFont->GetTextWidth(mText.substr(linestart, mCursorPos - linestart));
                            x = ( x >= width ) ? width-1: x;
                            break;
                        }

                    linestart = mBreaks[i];
                    i++;
                }
            //x should be accurate, unless the cursor is at the last character,
            //and that last character is a carriage return.


        }

    //The current position should be OK, UNLESS the character at mCursorPos is a CR.
    //Then, we actually want to render CR on the next line.

    if(mText[mCursorPos-1]== 10)
        {
            y+=height;
            x=1;
        }


    //x,y specifies the top of the cursor.
    SDLUtility::DrawLine(mSurface, x, y, x, y+height,(mFont->GetFontColor()));

}


//This overrides the parent Draw() method so that
//things can be re-rendered if necessary.
bool PlatformTextBox::Draw()
{

    if(mTextChanged)  FindBreaks();
    if(mTextChanged || mCursorChanged) RenderText();

    mCursorChanged = false;
    mTextChanged = false;

    return PlatformWidget::Draw();
}


//Some key presses can only be handled by the platform-specific code.
//Do this here.
void PlatformTextBox::HandleKeyPress(int keycode, int modkeys,Uint16 unicode)
{

    switch(keycode)
        {
        case PEBLKEY_UP:
        case PEBLKEY_DOWN:

            {
                int change;
                if(keycode == PEBLKEY_UP) change = -1;
                else change = 1;

                //Find x and y of position.
                int x = 0;
                int y = 0;

                int height=mFont->GetTextHeight(mText);
                unsigned int i = 0;
                int linestart = 0;


                while(i < mBreaks.size())
                    {
                        if(mBreaks[i] > mCursorPos)
                            {
                                y = i * height;
                                x = mFont->GetTextWidth(mText.substr(linestart, mCursorPos - linestart));
                                break;
                            }
                        linestart = mBreaks[i];
                        i++;
                    }


                mCursorPos = FindCursorPosition(x, y + change * height);
                mCursorChanged = true;
                break;
            }
        default:
            ;
        }

    PTextBox::HandleKeyPress(keycode, modkeys, unicode);
}
