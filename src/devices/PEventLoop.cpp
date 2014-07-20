//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PEventLoop.cpp
//    Purpose:    Primary generic timer event device
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
#include "PEventLoop.h"
#include "PDevice.h"
#include "PEventQueue.h"
#include "../platforms/sdl/PlatformEventQueue.h"
#include "../base/FunctionMap.h"

#include "../apps/Globals.h"

#ifdef PEBL_EMSCRIPTEN
#include "PEventLoop-es.h"
#include "../base/Evaluator-es.h"
#include "emscripten.h"
#else
#include "PEventLoop.h"
#include "../base/Evaluator.h"
#endif


#include "../base/PComplexData.h"
#include "../base/PEBLObject.h"
#include "../base/grammar.tab.hpp"

#include "../utility/Defs.h"

#include "../libs/PEBLEnvironment.h"
#include <iostream>

using std::flush;
using std::endl;

extern PlatformEventQueue * gEventQueue;

/// This is the standard PEventLoop constructor
PEventLoop::PEventLoop()
{
    //cout << "Creating event loop\n";

}

/// This is the standard pNode destructor
PEventLoop::~PEventLoop()
{
    // Standard Destructor
    //cout << "Destroying venet loop\n";
}



/// This function will 'register' a specific event that will be tested for
/// in an event-loop.  This allows multiple tests to be registered (time limit, key press, etc.)
/// and tested within a fairly tight compiled loop, without the user having to write his/her own 
/// interpreted event loop.
void PEventLoop::RegisterState(DeviceState * state,
                               const std::string & function,
                               Variant parameters)
{


    //cout << "Registering a state\n";
    //Add the state to the states list.
    mStates.push_back(state);
    //Make a PNode representing the function. If the function-name is null, push a
    //null PNode onto the vector; this is a short-cut for an end-of-loop event.
    if(function != "")
        {

            //Get the node associated with the function name.
            //Note that node will be the right node of a PEBL_FUNCTION node
            //The namenode goes on the left.
            Variant fname = Variant(function.c_str(),P_DATA_FUNCTION);
            DataNode * namenode = new DataNode(fname,"user-generated function",-1);                                        

            //On the right, we need a node representing the lambda function.

            //we need the arglist too.

            PNode * node = Evaluator::mFunctionMap.GetFunction(function);

            PNode * arglist = ((OpNode*)node)->GetLeft();

            PNode * fnode = new OpNode(PEBL_FUNCTION, namenode, arglist, "user-generated", -1);


            mNodes.push_back(fnode);


        }
    else
        {
            
            mNodes.push_back(NULL);
        }
    //Add parameters, for use later.
    //parameters is passed in as a pointer, and must be attached to a counted pointer
    //if we are to maintain it once the original function is gone.


    mParameters.push_back(parameters);
    mIsEvent.push_back(false);
}

/// This function will 'register' a specific event that will be tested for
/// in an event-loop.  This allows multiple tests to be registered (time limit, key press, etc.)
/// and tested within a fairly tight compiled loop, without the user having to write his/her own 
/// interpreted event loop.

/// This method takes over ownership of the DeviceState, and is responsible for cleaning it up 
/// when finished.
void PEventLoop::RegisterEvent(DeviceState * state, const std::string &  function, Variant parameters)
{
    //cout << "Adding a state2--[" << function <<"]"<< endl;

    //Add the state to the states list.
    mStates.push_back(state);
    //Make a PNode representing the function. If the function-name is null, push a
    //null PNode onto the vector; this is a short-cut for an end-of-loop event.
    if(function != "")
        {

            //Get the node associated with the function name.
            //Note that node will be the right node of a PEBL_FUNCTION node
            //The namenode goes on the left.
            Variant fname = Variant(function.c_str(),P_DATA_FUNCTION);
            DataNode * namenode = new DataNode(fname,"user-generated function",-1);                                        

            //On the right, we need a node representing the lambda function.
            
            PNode * node = Evaluator::mFunctionMap.GetFunction(function);

            PNode * arglist =  ((OpNode*)node)->GetLeft();

            PNode * fnode = new OpNode(PEBL_FUNCTION, namenode, arglist, "user-generated", -1);



            mNodes.push_back(fnode);
        }
    else
        {
            mNodes.push_back(NULL);
        }
    //Add parameters, for use later.
    
    mParameters.push_back(parameters);
    mIsEvent.push_back(true);
}



void PEventLoop::Clear()
{
    
    //cout << "CLEARING EVENT LOOP VIA CLEAR\n";

    //When the eventloop is Clear()ed, the states should be deleted one-by-one,
    //to avoid a memory leak.
    
    std::vector<DeviceState*>::iterator i = mStates.begin();

    while(i != mStates.end())
        {
            //memory crash here:
            //cout << "Deleting: " << *i << endl;
            if(*i)  delete *i;
            i++;
        }

    mStates.clear();
    mNodes.clear();
    mParameters.clear();
    mIsEvent.clear();
    
}


/// The following method will initiate an event loop.  It will repetitively
/// cycle through each of the devices-events registered and determine if any are 
/// satisfied.  Whenever one is satisfied, it will follow the directive of that
/// event.  It will continue until a STOPEVENTLOOP event is processed.


PEvent PEventLoop::Loop()
{
    //cout << "starting loop.  mstates.size: " << mStates.size() <<endl;
    
    Evaluator * myEval = new Evaluator();
    unsigned int i, result =0;
    PEvent returnval(PDT_UNKNOWN,0);

    //Enter a variable into the global variable map.  The loop will exit
    //when this is set false.
    myEval->gGlobalVariableMap.AddVariable("gKeepLooping", 1);

    //cout <<"*****" <<myEval->gGlobalVariableMap.RetrieveValue("gKeepLooping") << "--"<< mStates.size() << std::endl;

    //while loop stops when gKeepLooping turns false or there are no more states to check for.
    //    bool stop = (mStates.size()==0) ||
    //        ((pInt)(myEval->gGlobalVariableMap.RetrieveValue("gKeepLooping"))==(pInt)0);

    while(myEval->gGlobalVariableMap.RetrieveValue("gKeepLooping"))
        {
            //Output time for each event loop cycle.
            //std::cerr <<  "time:"<< SDL_GetTicks() << std::endl;

            //At the beginning of a cycle, the event queue has not yet been primed.
            gEventQueue->Prime();
            
            // cout << mStates.size() << "  ";
            
            //Scan through each event in the event vector.         
            for(i = 0; i < mStates.size(); i++)
                {
                    //cout << i << "/"<<mStates.size() << ":"<<  mNodes[i] << "\n";

                    if(mIsEvent[i])   //The test is for an event queue-type event.
                        {
                            
                            // Note: 'events' contrast with 'states', handled later.
                           // These are devices which send events through the PEBL Event queue.
                            // So, if the current test is an 'event' state, we need to check the event queue.
                            
                            //Only test the event if the queue is not empty.
                            if(!gEventQueue->IsEmpty())
                                {
                                    //cout << mStates.size() << endl;
                                    //Now, we only should test an event if it is the proper device type.
                                    //cout << "statetype ["<<i<<"]" << endl;
                                    //cout << mStates[i]->GetDeviceType() << "---" << std::flush;
                                    //cout <<*(mStates[i]) << endl;
                                    //cout << "Event: " << PDT_WINDOW_RESIZE <<"|"<< gEventQueue->GetFirstEventType() << endl;
                                    if(gEventQueue->GetFirstEventType() == mStates[i]->GetDeviceType())
                                        {
                                            


                                            //Now, just test the device.
                                            result = mStates[i]->TestDevice();
                                            //cout << "Result:" << result << endl;
                                               
                                            if(result)
                                                {
                                                    returnval = gEventQueue->GetFirstEvent();
                                                    

                                                    // The test was successful.  
                                                    
                                                    if(mNodes[i])  //Execute mNodes
                                                        {
                                                            //Add the parameters, as a list, to the stack.
                                                            
                                                            myEval->Push(mParameters[i]);
                                                            myEval->CallFunction((OpNode*)mNodes[i]);
                                                            myEval->Pop();

                                                        }
                                                    else       //If mNodes[i] is null, terminate
                                                        {
                                                            //std::cout << "Ending loop with gkeeplooping2\n";
                                                            myEval->gGlobalVariableMap.AddVariable("gKeepLooping", 0);
                                                            
                                                        }
                                            goto end; 
                                                }
                                        }
                                }
                        }
                    else
                        {
                            //mStates[i] isn't a device-type state.

                            //The test examines the device's state directly.
                            //I don't think any devices support TestDevice currently.

                            //result = mStates[i]->TestDevice();
                            result = mStates[i]->TestDevice();
                            //cout << "Resultb:" << result << endl;
                            
                            if(result)

                                {
                                    //We need to create a 'dummy' event to use here.
                                    PEBL_DummyEvent pde;
                                    pde.value = mStates[i]->GetInterface();
                                    



                                    if(mStates[i]->GetDevice()->GetDeviceType() == PDT_TIMER)
                                        {
                                    
                                            returnval = PEvent(PDT_TIMER,0);
                                            returnval.SetDummyEvent(pde);

                                        } 
                                    else
                                        {

                                            //If this was a time-check event, make a PDT_timer
                                            //time needs to go in  the 0 below.
                                            //returnval = PEvent(PDT_DUMMY,0);
                                            
                                            returnval = PEvent((PEBL_DEVICE_TYPE)pde.value,0);
                                            returnval.SetDummyEvent(pde);
                                        }
                                    //If mNodes[i] is null, terminate
 
                                    if(mNodes[i])
                                        {
                                            //cout << i << ": " << mNodes[i] << std::endl;

                                            //Add the parameters, as a list, to the stack.
                                            //Put the parameter on the top of the stack.

                                            Variant v2 = Variant(mParameters[i]);

                                            myEval->Push(v2);



                                            //myEval->Evaluate(mNodes[i]);
                                            myEval->CallFunction((OpNode*)mNodes[i]);
                                            //The top of the stack will be whatever is returned,
                                            //which should be nothing, or at least
                                            //cout << "About to pop:" << myEval->Peek() << std::endl;

                                            //The return value is currently unused.
                                            // we could use it to remove an event dynamically.
                                           
                                            myEval->Pop();


                                        }
                                    else
                                        {
                                            //std::cout << "Ending loop with gkeeplooping\n";
                                            myEval->gGlobalVariableMap.AddVariable("gKeepLooping", 0);

                                        }
                                    goto end;                                    
                                    
                                }
                        }
                end:;
                    //                    cout << std::endl;
                }

            //end:
            //Get rid of the top item in the event queue
            gEventQueue->PopEvent();

            //This does a nano sleep function to avoid burning cpu, if the gSleepEasy variable is set.
            //Probably is only available on unix.
#if defined(PEBL_UNIX)
            if(myEval->gGlobalVariableMap.Exists("gSleepEasy") )
                {
                    if(myEval->gGlobalVariableMap.RetrieveValue("gSleepEasy"))
                    {
                        struct timespec a,b;
                        a.tv_sec  = 0;   
                        a.tv_nsec = 100000; //1 ms
                        //int retval = nanosleep(&a,&b);
                        nanosleep(&a,&b);
                    }
                }
#endif

#if defined(PEBL_WIN32)
           if(myEval->gGlobalVariableMap.Exists("gSleepEasy") )
                {
                    if(myEval->gGlobalVariableMap.RetrieveValue("gSleepEasy"))
                    {
                       //Sleep(1);  //sleep about 1 ms(might be as much as 10)
                       SDL_Delay(1);
                    }
                }

#endif

           //recompute the stopping criterion
           if(mStates.size()==0) 
               myEval->gGlobalVariableMap.AddVariable("gKeepLooping",0);
           //!(myEval->gGlobalVariableMap.RetrieveValue("gKeepLooping"));
           //cout << mStates.size() << " " << (myEval->gGlobalVariableMap.RetrieveValue("gKeepLooping")) << "---" << stop << std::endl;
        }

    delete myEval;
    return returnval;
}


//Overload of the << operator
std::ostream & operator <<(std::ostream & out, const PEventLoop & loop )
{

    out << "PEBL Event Loop: " << flush;
    loop.Print(out);
    return out;

}


void PEventLoop::Print(std::ostream & out) const
{
    out << " ---------------\n";
    out << "Number of states:" <<mStates.size() << endl;

}
