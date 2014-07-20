//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformWidget.cpp
//    Purpose:    Contains SDL-specific interface GUI objects
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
////////////////////////////////////////////////////////////////////////////////
#include "PlatformWidget.h"

#ifdef PEBL_OSX
#include "SDL.h"
#include "SDL_rotozoom.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_rotozoom.h"
#endif

#include "SDLUtility.h"
#include "../../utility/PError.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

//Standard constructor 
PlatformWidget::PlatformWidget():
    mSurface(NULL),
    mParentSurface(NULL)
{

}

PlatformWidget::~PlatformWidget()
{
    //Remove this from its parent (if one exists)
    if(mParent)
        mParent->RemoveSubWidget(this);

    RemoveSubWidgets();
    
    //This can crash here whin widget is a window--not sure why yet?
    SDL_FreeSurface(mSurface);

}



std::ostream & PlatformWidget::SendToStream(std::ostream& out) const
{
    out << "<SDL PlatformWidget> " << std::flush;
    return out;
}




bool PlatformWidget::Draw()
{

    //cout <<"Drawing: " << mSurface->refcount << endl;
    if(IsVisible())
        {
            //To draw a widget, draw each of the window's subwidgets
            //(using PlatformWidget::Draw(SDLSurface)
            //This should be done backwards, so that the last item added
            //(which is on the front) will be the last item drawn.


            std::list<PWidget *>::iterator p = mSubWidgets.end();
            while(p != mSubWidgets.begin())
                {

                    //decrement iterator--moving backward so we draw things in 
                    //reverse order.
                    p--;
                    //Draw the subwidget
                    if((*p)->IsVisible())
                        {
                            (*p)->Draw();
                        }
                }
            
            //Once the widget sub-items are drawn, draw the widget to its parent.
            if (mParentSurface)
                {        
                    
                    //cout << "PRE mdrawxy" << mDrawX << "," << mDrawY << endl;
                    //Set a tmp surface to mSurface. If we are not rotozooming, it gets used 
                    //directly; otherwise, tmp will be a morphed version of the original.
                    SDL_Surface * tmp = mSurface;
                    bool zoom = false;
                    //Check to see if any roto-zooming is needed
                    if(fabs(mZoomX-1.0)>.001 || fabs(mZoomY-1.0)>.001 || fabs(mRotation)>.001)
                        {
                            zoom = true;
                        }

                    if(zoom)
                        {

                    
                            tmp = rotozoomSurfaceXY(mSurface, mRotation,mZoomX, mZoomY, 1); 
                            //SDL_SetAlpha(tmp,0,SDL_ALPHA_TRANSPARENT);
                            //SDL_SetAlpha(tmp, 0, SDL_ALPHA_OPAQUE );        
                            //We need to reset the sizes.
                            mWidth = tmp->w;
                            mHeight = tmp->h;
                            //cout << mRotation << ":" << mZoomX<< ":" << mZoomY << endl;
                            //cout << mSurface->w << "," << mSurface->h << " : "  << tmp->w << "," << tmp->h << endl;
                                
                            PWidget::SetProperty("WIDTH",mWidth);
                            PWidget::SetProperty("HEIGHT",mHeight);
                            PWidget::SetProperty("ZOOMX",mZoomX);
                            PWidget::SetProperty("ZOOMY",mZoomY);
                            
                            
                            //SetPosition(mX,mY); //Reset position so
                            //objects get centered properly
                        }
                    else
                        {

                            //width and height need resetting back 
                            //to original, assuming they had been

                            //This can cause crashing, when a label is empty.  
                            if(mSurface)
                                {
                                    mWidth = mSurface->w;
                                    mHeight = mSurface->h;
                                }
                            else
                                {
                                    mWidth = 0;
                                    mHeight = 0;
                                }
                            PWidget::SetProperty("WIDTH", mWidth);
                            PWidget::SetProperty("HEIGHT", mHeight);
                            PWidget::SetProperty("ZOOMX",1);
                            PWidget::SetProperty("ZOOMY",1);
                            //cout << "PRE2 mdrawxy" << mDrawX << "," << mDrawY << endl;
                            //SetPosition(mX,mY);
                            //cout << "POST1 mdrawxy" << mDrawX << "," << mDrawY << endl;
                        }

                    //cout << "POST2 mdrawxy" << mDrawX << "," << mDrawY << endl;

                    SDL_Rect  fromRect = {0,0,mWidth,mHeight};
                    SDL_Rect  toRect   = {mDrawX,mDrawY,mWidth,mHeight};
                    //  unsigned long int start =SDL_GetTicks();
                    //cout << "blitting to: " <<mDrawX << "," << mDrawY << endl;
                    SDL_BlitSurface(tmp, &fromRect, mParentSurface, &toRect);
                    //  unsigned long int end =SDL_GetTicks();
                    //     cout << "Time to BlitSurface:  " << end - start << endl;
                    
                    //If we zoomed, we need to free the tmp; otherwise, tmp is the same as mSurface.
                    if(zoom) SDL_FreeSurface(tmp);

                }
            else
                {
                    // IF there is no parent, this is probably a window, which 
                    // performs a SDL_Flip after this method is called.
                }
        }
    return true;
}


//Sets a pixel to be a certain color.
//This won't work on a window, only objects added to the window.
bool PlatformWidget::SetPoint(int x, int y, PColor col)
{
    //    std::cout << "Setting point " << x << " " << y << std::endl;

    SDLUtility::DrawPixel(mSurface,x,y,col);
    return true;
}


PColor PlatformWidget::GetPixel(int x, int y)
{
    return SDLUtility::GetPixelColor(mSurface,x,y);
}



bool PlatformWidget::RotoZoom(double angle, double zoomx, double zoomy, int smooth)

{


    SDL_Surface * tmp = rotozoomSurfaceXY(mSurface, angle,zoomx, zoomy, smooth); 
    SDL_FreeSurface(mSurface);
    mSurface = tmp;
    
    
    //We need to reset the sizes.

    mWidth = mSurface->w;
    mHeight = mSurface->h;
    PWidget::SetProperty("WIDTH", mSurface->w);
    PWidget::SetProperty("HEIGHT", mSurface->h);
    if(mSurface)return true;
    else return false;
}



SDL_Surface * PlatformWidget::GetSDL_Surface()
{
    return mSurface;
}




bool PlatformWidget::AddSubWidget(PlatformWidget * child)
{


    if(strcmp(child->ObjectName().c_str(),"PlatformMovie")==0)
        {
            PError::SignalFatalError("Cannot add movie to another widget\n");
        } else {
        child->SetParentSurface(mSurface);
        PWidget::AddSubWidget(child);
    }
    
    return true;
}


bool PlatformWidget::RemoveSubWidget(PlatformWidget * child)
{
    child->SetParentSurface(NULL);
    PWidget::RemoveSubWidget(child);

    return true;
}

void PlatformWidget::SetParentSurface(SDL_Surface* surface)
{
    mParentSurface = surface;
}


///This needs to be used on some platforms/video cards
bool PlatformWidget::LockSurface()
{
    if(SDL_MUSTLOCK(mSurface))
        { 

            //cout << "Locking-------->" << endl;
            //The below returns 0 on success, -1 otherwise,
            //so reverse it for t/f
            if(SDL_LockSurface(mSurface)<0)
                {
                    cerr << "Need to lock surface but can't\n";
                    return false;
                }
            return true;
        }
    
    return false;

}

///This needs to be used on some platforms/video cards
bool PlatformWidget::UnlockSurface()
{
   if(SDL_MUSTLOCK(mSurface))
        { 
            // cout << "------->Unlocking" << endl;
            SDL_UnlockSurface(mSurface);
        }
   return true;
}
