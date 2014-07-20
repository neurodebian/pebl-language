//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       utility/PEBLHTTP.h
//    Purpose:    Class enabling HTTP GET and POST commands.
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2013-2014 Shane T. Mueller <smueller@obereed.net>
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
#ifndef __PEBLHTTP_H__
#define __PEBLHTTP_H__

#ifdef PEBL_HTTP
#include "happyhttp.h"


#include "../base/Variant.h"
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstring>


// This uses a simple http library called 'happyhttp'
// it is a slim wrapper around that, but we abstract from.
// aLSO , this should enable using PEBLPaths, PErrors, and such.
// the library to maybe someday use curl or the wget commands
// in emscripten.

class PEBLHTTP
{

public:
    PEBLHTTP(Variant host);
    virtual ~PEBLHTTP();

    virtual int GetHTTPFile(Variant fname, Variant savename);
    virtual int GetHTTPText(Variant fname);
    virtual int PostHTTP(Variant name, Variant headers,Variant body);

    virtual FILE * GetFileObject(){return mFile;};
    virtual std::string * GetTextObject(){return mText;};

    virtual void SetByteCount(int n){mByteCount = n;}
    virtual  int GetByteCount(){return mByteCount;};

    virtual void SetStatus(int status){std::cout << "Setting statuse:" << status << std::endl;mStatus= status;};
    virtual int GetStatus(){return mStatus;};

    virtual  void SetReason(std::string reason){mReason = reason;};


    FILE*  mFile; //file to stream to.


 private:
    int mStatus;  //http status number
    std::string mReason;

    std::string * mText;
    Variant mHost;
    Variant mFileName;
    Variant mSaveName;



    int mByteCount;
};
#endif
#endif
