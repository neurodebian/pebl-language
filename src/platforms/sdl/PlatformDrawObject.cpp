//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
///////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformDrawObject.cpp
//    Purpose:    Platform-specific classes drawing things.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2005-2010 Shane T. Mueller <smueller@obereed.net>
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
///////////////////////////////////////////////////////////////////////////////

#include "PlatformDrawObject.h"
#include "PlatformWidget.h"

#ifdef PEBL_OSX
#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#endif



#include "../../base/PList.h"
#include "../../base/Variant.h"
#include "../../base/PComplexData.h"

#include <iostream>
#include <list>
//using std::list;
using std::vector;
using std::cout;
using std::endl;
// PlatformDrawObject::PlatformDrawObject(PlatformWidget * widget)
// {
//     mSurface = widget->GetSDL_Surface();
//     mParentSurface = NULL;
//     mIsVisible=true;
// }

// PlatformDrawObject::PlatformDrawObject(PlatformWidget * widget, int x, int y ):
//     mSurface(widget->GetSDL_Surface())
// {

//     mX = x;
//     mY = y;


// }

//  PlatformDrawObject::~PlatformDrawObject()
// {
//     //Don't delete the surface--it belongs to somebody else.
// }

//  bool PlatformDrawObject::Draw()
// {
 
//     return true;
// }


// std::ostream & PlatformDrawObject::SendToStream(std::ostream& out) const
// {

//     out << "A draw object";
//     return out;
// }


// SDL_Surface * PlatformDrawObject::GetSDL_Surface()
// {
//     return mSurface;
// }

//  bool PlatformDrawObject::SetParentSurface(SDL_Surface * surface)
// {
//     mParentSurface = surface;
//     return true;
// }


// ///This needs to be used on some platforms/video cards
// bool PlatformDrawObject::LockSurface()
// {
//     if(SDL_MUSTLOCK(mSurface))
//         { 

//             //cout << "Locking-------->" << endl;
//             //The below returns 0 on success, -1 otherwise,
//             //so reverse it for t/f
//             if(SDL_LockSurface(mSurface)<0)
//                 {
//                     std::cerr << "Need to lock surface but can't\n";
//                     return false;
//                 }
//             return true;
//         }
    
//     return false;

// }

// ///This needs to be used on some platforms/video cards
// bool PlatformDrawObject::UnlockSurface()
// {
//    if(SDL_MUSTLOCK(mSurface))
//         { 
//             // cout << "------->Unlocking" << endl;
//             SDL_UnlockSurface(mSurface);
//         }
//    return true;
// }




PlatformLine::PlatformLine(int x1, int y1, int dx, int dy, Variant fg):
    PLine(x1,y1,dx,dy,fg)
{
    mCDT=CDT_DRAWOBJECT;

    mSurface =NULL;
    mParent = NULL;
    mIsVisible=true;
}

PlatformLine::~PlatformLine()
{

}

std::ostream & PlatformLine::SendToStream(std::ostream& out) const
{
    out << "<A line:"<< mX << ", " << mY << "| w: " << mDX+mX << ", h:" << mDY+mY << std::endl;
    return out;
}

bool PlatformLine::Draw()
{

    int result;

    
    result = lineRGBA(mParentSurface,mX, mY, mX+mDX, mY+mDY,
                      mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
    
    return result;
}


PlatformRectangle::PlatformRectangle(int x1, int y1, int dx, int dy, Variant fg, bool filled):
    PRectangle(x1,y1,dx,dy,fg,filled)
{
    mCDT = CDT_DRAWOBJECT;
}

PlatformRectangle::~PlatformRectangle()
{
}

bool PlatformRectangle::Draw()
{

    int result;
    //LockSurface();
    if(mFilled)
        {
            result = boxRGBA(mParentSurface,mX - mDX/2, mY - mDY/2, mX+mDX/2, mY+mDY/2,
                             mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
       
        }
    else
        {
            result = rectangleRGBA(mParentSurface,mX - mDX/2, mY - mDY/2, mX+mDX/2, mY+mDY/2,
                                   mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }
    //UnlockSurface();
    return result;

}

std::ostream & PlatformRectangle::SendToStream(std::ostream& out) const
{
    out << "A Rectangle"<< mX << " " << mY << " " << mDX << " " << mDY << std::endl;
    return out;
}


PlatformSquare::PlatformSquare(int x, int y, int size, Variant fg, bool filled):
    PSquare(x,y,size,fg,filled)

{
    mCDT=CDT_DRAWOBJECT;
}

PlatformSquare::~PlatformSquare()
{
}


bool PlatformSquare::Draw()

{

   int result;
    //LockSurface();
    if(mFilled)
        {
            result = boxRGBA(mParentSurface,mX - mDX/2,  mY - mDY/2, mX+mDX/2, mY+mDY/2,
                             mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }
    else
        {
            result = rectangleRGBA(mParentSurface,mX - mDX/2, mY - mDY/2, mX+mDX/2, mY+mDY/2,
                                   mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }
    //UnlockSurface();
    return result;
}


std::ostream & PlatformSquare::SendToStream(std::ostream& out) const
{
    out << "A Square:"<< mX << " " << mY << " " << mDX << " " << mDY << " vis: "<<mIsVisible << std::endl;
    return out;
}




PlatformEllipse::PlatformEllipse(int x1, int y1, int dx, int dy, Variant fg, bool filled):
    PEllipse(x1,y1,dx,dy,fg, filled)
{
    mCDT = CDT_DRAWOBJECT;
    mSurface =NULL;
    mParent = NULL;
//     mIsVisible=true;
//     mX = x1;
//     mY = y1;

}

PlatformEllipse::~PlatformEllipse()
{

}

std::ostream & PlatformEllipse::SendToStream(std::ostream& out) const
{
    out << "<An ellipse:"<< mX << ", " << mY << ":" << mRX << ", " << mRY << std::endl;
    return out;
}

bool PlatformEllipse::Draw()
{

    int result;
    //LockSurface();
    if(mFilled)
        {
            result = filledEllipseRGBA(mParentSurface,mX, mY, mRX, mRY,
                                     mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
            
        }
    else
        {
            result = ellipseRGBA(mParentSurface,mX, mY, mRX, mRY,
                                 mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }
    //UnlockSurface();
    return result;
}



PlatformCircle::PlatformCircle(int x1, int y1, int r, Variant fg, bool filled):
    PCircle(x1,y1,r,fg,filled)
{
    mCDT=CDT_DRAWOBJECT;
    mSurface =NULL;
    mParent = NULL;
    mIsVisible=true;

}

PlatformCircle::~PlatformCircle()
{

}

std::ostream & PlatformCircle::SendToStream(std::ostream& out) const
{
    out << "<A Circle :"<< mX << ", " << mY << ":" << mR  << std::endl;
    return out;
}

bool PlatformCircle::Draw()
{
    int result;
    //LockSurface();
    if(mFilled)
        {
            result = filledCircleRGBA(mParentSurface, mX,  mY, (int)mR,
                                      mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());

        }
    else
        {
            result = circleRGBA(mParentSurface,mX, mY, (int)mR,
                                mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }
    //UnlockSurface();
    return result;
}




PlatformPolygon::PlatformPolygon(int x1, int y1, Variant xpoints,  Variant ypoints, Variant fg, bool filled):
    PPolygon(x1,y1,xpoints,ypoints,fg,filled)
{
    mCDT=CDT_DRAWOBJECT;
    mSurface =NULL;
    mParent = NULL;
    mIsVisible=true;

}

PlatformPolygon::~PlatformPolygon()
{

}

std::ostream & PlatformPolygon::SendToStream(std::ostream& out) const
{
    out << "<A Polygon :"<< mX << ", " << mY << ":" << std::endl;
    return out;
}

bool PlatformPolygon::Draw()
{
    int result;

    //We need to transform the double-list points into int vectors for 
    //the x and y points, plus the length.

    PList * pxlist = mXPoints.GetComplexData()->GetList();
    PList * pylist = mYPoints.GetComplexData()->GetList();

    int length = pxlist->Length();
    Sint16 *x = new Sint16[length];
    Sint16 *y = new Sint16[length];

    vector<Variant>::iterator p1 = pxlist->Begin();    
    vector<Variant>::iterator p2 = pylist->Begin();

    int i = 0;
    while(p1 != pxlist->End())
        {
            x[i]=  (Sint16)((int)(*p1)) + (Sint16)mX;
            y[i]=  (Sint16)((int)(*p2)) + (Sint16)mY;
            p1++;
            p2++;
            i++;
        }


    if(mFilled)
        {
            result = filledPolygonRGBA(mParentSurface,x,y,length,
                                       mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }
    else
        {
            result =polygonRGBA(mParentSurface,x,y,(int)length,
                                       mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
        }

        delete[] x;
        delete[] y;

    //UnlockSurface();
    return result;
}



PlatformBezier::PlatformBezier(int x1, int y1, Variant xpoints,  Variant ypoints, int steps, Variant fg):
    PBezier(x1,y1,xpoints,ypoints,steps, fg)
{

    mCDT=CDT_DRAWOBJECT;
    mSurface =NULL;
    mParent = NULL;
    mIsVisible=true;

}

PlatformBezier::~PlatformBezier()
{

}

std::ostream & PlatformBezier::SendToStream(std::ostream& out) const
{
    out << "<A Bezier :"<< mX << ", " << mY << ":" << std::endl;
    return out;
}

bool PlatformBezier::Draw()
{
    int result;


    //We need to transform the double-list points into int vectors for 
    //the x and y points, plus the length.

    PList * pxlist = mXPoints.GetComplexData()->GetList();
    PList * pylist = mYPoints.GetComplexData()->GetList();

    int length = pxlist->Length();
    Sint16 *x = new Sint16[length];
    Sint16 *y = new Sint16[length];

    vector<Variant>::iterator p1 = pxlist->Begin();    
    vector<Variant>::iterator p2 = pylist->Begin();

    int i = 0;
    while(p1 != pxlist->End())
        {
            x[i]=  (Sint16)((int)(*p1)) + (Sint16)mX;
            y[i]=  (Sint16)((int)(*p2)) + (Sint16)mY;
            p1++;
            p2++;
            i++;
            
        }

    
    result = bezierRGBA(mParentSurface,x,y,length,mSteps,
                        mColor.GetRed(), mColor.GetGreen(), mColor.GetBlue(), mColor.GetAlpha());
    
    delete[] x;
    delete[] y;

    //UnlockSurface();
    return result;
}
