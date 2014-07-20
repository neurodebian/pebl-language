//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformWidget.h
//    Purpose:    Contains SDL-specific interface for GUI Objects
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
#ifndef __PLATFORMWIDGET_H__
#define __PLATFORMWIDGET_H__


#include "../../objects/PWidget.h"
#include "SDL/SDL.h"

///  This is the top-level widget of platform-specific widgets.
///  Widgets inherit from PWidget along two pathways; through
///  PlatformWidget and through their platform-general corresponding widget.
///  This class is used to provide platform-specific drawing mechanisms that may prove useful.


class PlatformWidget:  virtual public PWidget
{
public:
  
    PlatformWidget();
    virtual ~PlatformWidget();
  

    ///This method initiates everything needed to display the main window   
    virtual bool Draw();

    ///Used to extract an SDL surface from the widget.  Used by children drawing themselves on their parent.
    virtual SDL_Surface * GetSDL_Surface();
    
    virtual bool AddSubWidget(PlatformWidget * widget);
    virtual bool RemoveSubWidget(PlatformWidget * widget);
    virtual void SetParentSurface(SDL_Surface * surface);

    ///This uses the SDL_gfx package to 'rotozoom'.
    virtual bool RotoZoom(double angle, double zoomx, double zoomy, int smooth);


    //Draws a pixel on the widget.
    bool SetPoint(int x, int y, PColor col);
    PColor GetPixel(int x, int y);


protected:

    //These are inherited by the SDL-specific widgets:    
    virtual std::ostream & SendToStream(std::ostream& out) const;
    
    virtual bool LockSurface();
    virtual bool UnlockSurface();

 
    //An sdl surface that does all the work.
    SDL_Surface * mSurface;

    ///The parent Surface. If null (0), this has no parent (top-level window).
    SDL_Surface * mParentSurface;
    

};


#endif
