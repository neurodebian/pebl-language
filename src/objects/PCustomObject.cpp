//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PCustomObject.cpp
//    Purpose:     Contains generic specs for all objects containing text
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
#include "../utility/PError.h"
#include "PCustomObject.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;

PCustomObject::PCustomObject():
    PEBLObjectBase(CDT_CUSTOMOBJECT),
    mName("Unknown Custom Object")
{

}



PCustomObject::PCustomObject(const std::string & name):
    PEBLObjectBase(CDT_CUSTOMOBJECT),
    mName(name)
{

}


PCustomObject::PCustomObject( PCustomObject &object):
    PEBLObjectBase(object)
{

}


PCustomObject::~PCustomObject()
{
    mProperties.clear();
}


bool PCustomObject::SetProperty(std::string name, Variant v)
{
    //We won't do any validation here.  Maybe in the future
    //some validation cuold be done here; allowing the user
    //to specify things like value type, or a subset of values.

    mProperties[name]=v;
    return true;
}


Variant PCustomObject::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);
}


ObjectValidationError PCustomObject::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}

ObjectValidationError PCustomObject::ValidateProperty(std::string name)const
{
   ObjectValidationError ove = PEBLObjectBase::ValidateProperty(name);
    if(ove == OVE_VALID)
        return ove;
    else
        return OVE_INVALID_PROPERTY_NAME;

}


/// This sends the color descriptions to the specified stream.
std::ostream & PCustomObject::SendToStream(std::ostream& out) const
{
    out << ObjectName()<< std::flush;
    return out;
}


std::string PCustomObject::ObjectName() const
{
    return mName;
}
