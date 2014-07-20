//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
////////////////////////////////////////////////////////////////////////////////
//    Name:       src/apps/PEBL.cpp
//    Purpose:    The primary PEBL run-time interpreter.
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

#ifdef PEBL_EMSCRIPTEN
#include "../base/Evaluator-es.h"
#include "../devices/PEventLoop-es.h"
#else
#include "../base/Evaluator.h"
#include "../devices/PEventLoop.h"
#endif

#include "../base/grammar.tab.hpp"
#include "../base/PNode.h"
#include "../base/Loader.h"
#include "../base/PComplexData.h"
#include "../base/PList.h"
#include "../base/FunctionMap.h"
#include "../base/VariableMap.h"
#include "../base/Variant.h"

#include "../libs/PEBLObjects.h"

#include "../utility/PError.h"
#include "../utility/PEBLPath.h"
#include "../utility/PEBLUtility.h"
#include "../utility/rc_ptrs.h"
#include "../utility/BinReloc.h"



#include "Globals.h"

#include <iostream>
#include <signal.h>
#include <list>
#include <string>
#include <algorithm>

//Unix-specific definitions
#if defined(PEBL_UNIX)
//For running at higher priority:
#include <sys/resource.h>
//For better fifo scheduling.
#include <sched.h>

#elif defined(PEBL_WIN32)
//For running at higher priority.
#include <windows.h>

#endif

#ifdef WIN32
#include <time.h>
#include <objbase.h>
#include <shlobj.h>
#endif



#ifdef PEBL_OSX
#include <mach-o/dyld.h>	/* _NSGetExecutablePath */
#include <CoreFoundation/CFBundle.h>
#endif


#ifdef PEBL_MOVIES
#include "WAAVE.h"
#endif

#include "../platforms/sdl/PlatformEnvironment.h"
#include "../platforms/sdl/SDLUtility.h"


extern Evaluator * myEval = NULL;//new Evaluator(v,"Start");

extern PlatformEnvironment * myEnv=NULL;


using std::cerr;
using std::endl;


/// This is the main PEBL interpreter program. It takes files as command-line arguments,
/// which it parses with the bison parser, creating a single tree of PNodes.  Then, it feeds
/// this tree into the loader, which loads the individual functions into a function map.  Then,
/// it sets up any global entities:  a graphical environment, a timer, a global variable map.
/// Finally, it locates the 'Start' function and executes it.


//Prototype for c function defined in grammar.y:
PNode *  parse(const char* filename);
std::list<string> GetFiles(int argc, std::vector<std::string> argv);
void  PrintOptions();

///Initiate some static member data.
FunctionMap Evaluator::mFunctionMap;
PEventLoop *Evaluator::mEventLoop=NULL;
VariableMap Evaluator::gGlobalVariableMap;
const PNode * Evaluator::gEvalNode = NULL;
PEBLPath  Evaluator::gPath;
PCallStack Evaluator::gCallStack;


Loader* myLoader;
PNode * head;

//std::list<PNode> PError::gCallStack;


int PEBLInterpret( int argc, std::vector<std::string> argv )
{
#if defined(PEBL_UNIX) and not defined(PEBL_OSX)
    if(argc==2 && strcmp(argv[1].c_str(), "--install")==0)
        {
            string basedir = "";
            BrInitError error;
            if (br_init (&error) == 0 && error != BR_INIT_ERROR_DISABLED)
                {
                    PError::SignalWarning("Warning: BinReloc failed to initialize.\n Will fallback to hardcoded default path.\n");
                    basedir = "/usr/local/share/pebl/";
                }

            string prefix = br_find_prefix("/usr/local/");
            basedir = prefix + string("/share/pebl/battery/");
            string destdir = "~/Documents/pebl-exp.0.14";

            //Now, copy everything in 'battery' to your documents directory.
            std::cerr << "Creating Documents/pebl-exp.0.14 Directory\n";
            PEBLUtility::SystemCall("mkdir ~/Documents","");
            //PEBLUtility::SystemCall("mkdir "+destdir,"");
            std::cerr << "Copying files to ["+destdir+ "]\n";
            PEBLUtility::SystemCall("cp -R "+ basedir + " " + destdir,"");
            exit(0);
        }
#endif

    PNode * tmp = NULL;

    //Cycle through command-line parameters extracting the files.
    //This does not check for file validity, it just removes any other command-line options,
    //i.e. ones that are of the form <-flag> <option> or whatever.
   //

#if 0
    //THis is just for debugging purposes.
    cout << "Arguments: "<< argv.size()<<"\n";
    std::vector<std::string>::iterator ii = argv.begin();
     while(ii != argv.end())
     {
         cout << *ii << endl;
         ii++;
         cout << "********\n";
     }
#endif

    std::list<std::string> files = GetFiles(argc, argv);

    //Set up the search path.
    Evaluator::gPath.Initialize(files);

    cerr << Evaluator::gPath;

    //Add the built-in PEBL libraries to the files list.
    files.push_back("Design.pbl");
    files.push_back("Utility.pbl");
    files.push_back("Math.pbl");
    files.push_back("Graphics.pbl");
    files.push_back("UI.pbl");

    //    files.push_back("Taguchi.pbl"); //not ready


#ifdef PEBL_EMSCRIPTEN
	std::cout << "Loading filename:[test.pbl]\n";
	string inputfilename = Evaluator::gPath.FindFile("test.pbl");

    if(inputfilename != "")
        {
            cerr << "Processing PEBL Source File1: " <<  inputfilename << endl;
            head  = parse(inputfilename.c_str());
        }
    else
        {
            PError::SignalFatalError("Unable to find file: [" + inputfilename + "].");
        }

#else
    //Process the first command-line argument.
    std::list<std::string>::iterator i = files.begin();
    i++;

    //-----------------------------------------------------------
    //        Process all files on the command-line
    //-----------------------------------------------------------

	std::cout << "Loading filename:[" << *i << "]\n";
	string inputfilename = Evaluator::gPath.FindFile(*i);
    string otherfilename;

    head = NULL;
    if(inputfilename != "")
        {
            cerr << "Processing PEBL Source File1: " <<  inputfilename << endl;
            head  = parse(inputfilename.c_str());
        }
    else
        {
            PError::SignalFatalError("Unable to find file: [" + inputfilename + "].");
        }
i++;
    //If there are any more arguments, process them by accomodating them
    //inside a function list.

    //Increment the iterator to move to the second command-line
   // i++;
    while(i != files.end())
        {
            std::cerr << "********************\n";
        	std::cerr << "Loading file name: ["      << *i <<"]"<< endl;
            otherfilename = Evaluator::gPath.FindFile(*i);
            std::cerr << "Resolved as: [" <<otherfilename <<"]"<< endl;
            if(inputfilename != "")
                {
                    cerr << "Processing PEBL Source File2: " <<  otherfilename << endl;

                    //A filename could be a directory (e.g., with media in it.)
                    //If so, don't parse it.
                    if(!Evaluator::gPath.IsDirectory(otherfilename))
                        {
                            //Make a new node.
                            tmp = parse(otherfilename.c_str());

                            //Now, make a new node that contains head and tmp.
                            head = new OpNode(PEBL_FUNCTIONS, head, tmp, "INTERNAL PEBL STRUCTURE", -1);
                        }
                }
            else
                {
                    PError::SignalFatalError("Unable to find file: ["+*i+"] at [" + otherfilename + "]");
                        //ignore mis-loaded files after the first; this is causing us
                            //problems on osx
                }
            i++;
       }

    //       Done processing files.
    //-----------------------------------------------------
#endif

    cerr << "---------Loading Program---------" << endl;
    //Now, load it into the environment:

    // Create a loader that will load functions into the functionmap
    myLoader = new Loader();
    myLoader->LoadUserFunctions((OpNode*)head);


    cerr <<"Analyzing code for functions." << endl;
    myLoader->FindFunctions(head);


    cerr << "Loading Library functions." << endl;
    myLoader->LoadLibraryFunctions();

    //This just destroys the function tree, not the
    //parsed node structure that is contained within
    //mFunctionMap.
    cerr << "Removing residual function tree\n";
    ((OpNode*)head)->DestroyFunctionTree();
    delete head;
    head = NULL;

#if 0
    cerr << "\n\n--------------------------------\n";
    cerr << "Functions used in program: " << endl;
    cerr << "--------------------------------\n";
    Evaluator::mFunctionMap.DumpValues();
    cerr << "--------------------------------\n\n";
#endif

    //Parse command-line arguments.

    PList *  pList =  new PList();
    PList *  arglist = new PList();


    //Use the current screen resolution as a startingp


    //Initialize display size here with a non-interesting one.
    //It may get set by a command-line argument later.
    std::string displaySize="0x0";


    std::string depth = "32";  //used to be 16; does this matter?
    enum PEBLVideoMode displayMode;
    enum PEBLVideoDepth displayDepth;
    bool windowed = true;
    bool resizeable = false;
    bool unicode = true;
    Variant lang = "en";
    Variant subnum = 0;

    //default the parameter file to ./params/SCRIPTNAME.par
    Variant pfile = Variant("params/")+Variant(inputfilename)+Variant(".par");

    //Extract the command-line variables to bind
    for(int j = 1; j < argc; j++)
        {

            if(strcmp(argv[j].c_str(), "-v")==0 ||
                    strcmp(argv[j].c_str(), "-V")==0)
                {
                    Variant tmp = argv[++j];
					//cout <<"Content of passed-in variable " << j << ":" << tmp << endl;
                    arglist->PushBack(tmp);
                }

            else if(strcmp(argv[j].c_str(), "-s")==0 ||
                    strcmp(argv[j].c_str(), "-S")==0)
                {
                    subnum  = argv[++j];
					//cout << "collecting Subject Number "<< subnum << endl;
  				}
            //set the driver directly from the command-line, if necessary.
            else if(strcmp(argv[j].c_str(),"--driver")==0)
                {
                    if(j+1 < argc)
                        {
                            j++;

                            //This now works on Windows; windib versus directx.
#if defined(PEBL_UNIX)
                            setenv("SDL_VIDEODRIVER", argv[j].c_str() ,1);
#elif defined(PEBL_WINDOWS)

                            _putenv((std::string("SDL_VIDEODRIVER=") + std::string(argv[j])).c_str());
#endif
                        }
                }
            else if(strcmp(argv[j].c_str(),"--display")==0)
                {
                    displaySize = argv[++j];
                }

            else if(strcmp(argv[j].c_str(),"--depth")==0)
                {
                    depth = argv[++j];

                }

            else if (strcmp(argv[j].c_str(),"--fullscreen")==0)
                {
                    windowed = false;
                }
            else if(strcmp(argv[j].c_str(),"--windowed")==0)
                {
                    windowed = true;
                }
            else if(strcmp(argv[j].c_str(),"--unicode")==0)
                {
                    unicode = true;
                }
            else if(strcmp(argv[j].c_str(),"--language")==0)
                {
                    lang = argv[++j];
                }

            else if(strcmp(argv[j].c_str(),"--pfile")==0)
                {
                    pfile = Variant("params/") +Variant(argv[++j]);
                }

            else if(strcmp(argv[j].c_str(),"--resizeable")==0 ||
                    strcmp(argv[j].c_str(),"--resizable")==0  )
                {
                    if(windowed)
                        resizeable = true;
                }

        }


    //Now, set the display modes variables based on the command-line options.
    displayMode = PEBLUtility::GetVideoMode(displaySize);
    displayDepth = PEBLUtility::GetVideoDepth(depth);



    //This sets the video driver, and other platform-specific stuff.
#if defined(PEBL_UNIX)

    //Do specific *nix stuff here (excluding OSX).
    //These can be controlled by a command-line option
    // setenv("SDL_VIDEODRIVER", "dga",1);  //Requires root privileges to run;  fullscreen.
    //setenv("SDL_VIDEODRIVER", "svgalib",1);  //Requires root and special library; allows you to run on virtual terminal.
    // setenv("SDL_VIDEODRIVER", "x11",1);


    //Now, set the priority to the highest it can go.

    //setpriority(PRIO_PROCESS,0,PRIO_MIN);
     setpriority(PRIO_PROCESS,0,0);
    int priority = getpriority(PRIO_PROCESS,0);
    cerr << "Process running at a nice value of " << priority << endl;

    /*
      struct sched_param mysched;
      mysched.sched_priority = sched_get_priority_max(SCHED_FIFO) - 1;
      if( sched_setscheduler( 0, SCHED_RR, &mysched ) == -1 )
      {
      cout << "Unable to enable round-robin scheduling.  Must have root priviledges.\n";
      }
      else
      {
      cout << "Round-robin scheduling enabled.\n";
      }

      struct timespec interval;
      if(sched_rr_get_interval(0,&interval)== -1)
      {
      cout << "Unable to get Round-robin scheduling interval.\n";
      }
      else
      {
      cout << "Round Robin Scheduling Interval: [" <<interval.tv_sec * 1000 + interval.tv_nsec / 1000 <<"] ms.\n";
      }

    */


#elif defined(PEBL_WIN32)
     //Do specific win32 stuff here.

    //SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
    //REALTIME causes program to hang on keyboard input.
    SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);

    //setenv()
#endif

    //cout <<"About to create environment\n";

    // We can't use any SDL-related functions before this function is called.
    // But we may want to know current screen resolution before we set displaymode
    PEBLObjects::MakeEnvironment(displayMode, displayDepth, windowed,resizeable,unicode);

    cerr << "Environment created\n";


    //Seed the random number generator with time of day.
    srand((unsigned int)time(0));

    cerr << "---------Creating Evaluator-----" << endl;
    //Create evaluator, because it contains a function map as a static member variable.
    //Create it with the command-line -v parameters as a list  bound to the argument.

#if defined(PEBL_EMSCRIPTEN)
    std::cerr <<"--------o-o-o-o-o-o--\n";
    arglist->PushBack(Variant(0));
    PComplexData * pcd = new PComplexData(counted_ptr<PEBLObjectBase>(arglist));
    pList->PushBack(Variant(pcd));
#else
    //Now, arglist should contain any values specified with the -v flag.
    if(arglist->Length()==0)
        {
            arglist->PushBack(Variant(0));
            PComplexData * pcd = new PComplexData(counted_ptr<PEBLObjectBase>(arglist));
            pList->PushBack(Variant(pcd));
        }
    else
        {
            PComplexData * pcd = new PComplexData(counted_ptr<PEBLObjectBase>(arglist));
            pList->PushBack(Variant(pcd));
        }
#endif

    PComplexData * pcd2 = new PComplexData(counted_ptr<PEBLObjectBase>(pList));
    Variant v = Variant(pcd2);


    std::list<PNode> tmpcallstack;

    //myEval is now a global, because we have moved to a single-evaluator model:
    myEval = new Evaluator(v,"Start");

    //Set the executable name here:
    myEval->gGlobalVariableMap.AddVariable("gExecutableName", argv[0]);

    //Set the default screen resolution based on the current one.
    Variant cursize = SDLUtility::GetCurrentScreenResolution();

#ifdef PEBL_EMSCRIPTEN

    Variant width = 800;
    Variant height = 600;
#else

    PList * plist = cursize.GetComplexData()->GetList();
    Variant width = plist->First(); //plist->PopFront();
    Variant height = plist->Nth(2);//plist->PopFront();
#endif
    myEval->gGlobalVariableMap.AddVariable("gVideoWidth", width);
    myEval->gGlobalVariableMap.AddVariable("gVideoHeight", height);


    //displaysize may have been set at the command line.  If so, we will need to
    //override it.  It is currently a string called displaysize.


    size_t found = displaySize.find("x");
    if(found == string::npos)
        {
            //Nothing is found.  Use 0s to indicate an invalid displaysize
            width = 0;
            height = 0;
        } else
        {
            cerr <<"Size from command line argument: "  << displaySize.substr(0,found)<< "|"<< displaySize.substr(found+1) <<endl;
            //something was found.
            width =  atoi(displaySize.substr(0,found).c_str());
            height = atoi(displaySize.substr(found+1).c_str());
        }


    if((pInt)width>0  & (pInt)height>0)
        {
            Evaluator::gGlobalVariableMap.AddVariable("gVideoWidth",width);
            Evaluator::gGlobalVariableMap.AddVariable("gVideoHeight",height);
        }


    //Add the subject identifier.
    Evaluator::gGlobalVariableMap.AddVariable("gSubNum",subnum);
    //If this is set to 1, we have reset the subject code, and
    //it is presumably good for all future resets.
    Evaluator::gGlobalVariableMap.AddVariable("gResetSubNum",0);


    //Translate lang to the uppercase 2-letter code
    std::string tmps =lang;
    transform(tmps.begin(),tmps.end(),tmps.begin(),toupper);
    Evaluator::gGlobalVariableMap.AddVariable("gLanguage",Variant(tmps));


    //Add a special 'quote' character.
    Evaluator::gGlobalVariableMap.AddVariable("gQuote",Variant("\""));


    //Add a the default 'base font' names
    //gPEBLBaseFont defaults to a sans serif font
    if((tmps == "CN") | (tmps== "KO") |(tmps == "JP"))
        {
            //ukai handles chinese
            Evaluator::gGlobalVariableMap.AddVariable("gPEBLBaseFont",Variant("wqy-zenhei.ttc"));
            Evaluator::gGlobalVariableMap.AddVariable("gPEBLBaseFontMono",Variant("wqy-zenhei.ttc"));
            Evaluator::gGlobalVariableMap.AddVariable("gPEBLBaseFontSerif",Variant("wqy-zenhei.ttc"));

        } else
        {
            //DejaVu handles most western fonts.
            Evaluator::gGlobalVariableMap.AddVariable("gPEBLBaseFont",Variant("DejaVuSans.ttf"));
            Evaluator::gGlobalVariableMap.AddVariable("gPEBLBaseFontMono",Variant("DejaVuSansMono.ttf"));
            Evaluator::gGlobalVariableMap.AddVariable("gPEBLBaseFontSerif",Variant("DejaVuSerif.ttf"));
        }

    //load the parameter file into a global variable
    Evaluator::gGlobalVariableMap.AddVariable("gParamFile",Variant(pfile));

    //Now, everything should be F-I-N-E fine.
    head = myLoader->GetMainPEBLFunction();

    if(head)
        {
            cerr << "---------Evaluating Program-----" << endl;
            //Execute everything


#ifdef PEBL_EMSCRIPTEN

            myEval->Evaluate1(head);
            //cout << "Finished evaluating head1\n";

            //            while(myEval->GetNodeStackDepth()>0)
            //                {
            //                    myEval->Evaluate1();
            //                    cout << "step complete1\n";
            //                }
            //cout << "Evaluating first step\n";
            myEval -> Evaluate1();
            cerr << "Exiting main loop; going asynchronous\n";
            return 0;
#else

#ifdef PEBL_ITERATIVE_EVAL

            //This creates an iterative evaluator
            myEval->Evaluate1(head);

            while(myEval->GetNodeStackDepth()>0)
                {
                    myEval->Evaluate1();
                }
#else
            //Use traditional recursive version.
            myEval->Evaluate(head);
#endif

            Evaluator::gGlobalVariableMap.Destroy();

            delete myLoader;
            if(myEnv) delete myEnv;
            Evaluator::mFunctionMap.Destroy();

            delete myEval;
            myEval = NULL;
            //Evaluator::gGlobalVariableMap.DumpValues();
#ifdef PEBL_MOVIES
            //Close the wave player library.
            WV_waaveClose();
#endif

            //Be sure SDL quits.  It should probably be handled elsewhere,
            //but this seems to work.

            SDL_Quit();
#endif

            return 0;
        }
    else
        {
            cerr << "Error: Can't evaluate program" << endl;
            return 1;
            delete myLoader;
        }

    return 0;

}

void  CaptureSignal(int signal)
{
    cerr << "Exiting PEBL because of captured signal.\n";

    Evaluator::gGlobalVariableMap.Destroy();

    delete myLoader;
    if(myEnv) delete myEnv;
    Evaluator::mFunctionMap.Destroy();


    //Evaluator::gGlobalVariableMap.DumpValues();

#ifdef PEBL_MOVIES
    //Close the wave player library.
    WV_waaveClose();
#endif


    //quit SDL here.  It should be killed els
    SDL_Quit();


    raise(signal);
    exit(0);
}


int main(int argc,  char *argv[])
{
  int newargc = argc;
    //  Set up some signals to capture
#ifdef SIGHUP
    signal(SIGHUP, CaptureSignal);
#endif

#ifdef SIGKILL
    signal(SIGKILL, CaptureSignal);
#endif

#ifdef SIGSTOP
    signal(SIGSTOP, CaptureSignal);
#endif

    //#ifdef SIGTERM
    //    signal(SIGTERM, CaptureSignal);
    //#endif

    signal(SIGINT, CaptureSignal);


#ifdef SIGQUIT
    signal(SIGQUIT, CaptureSignal);
#endif


    signal(SIGTERM, CaptureSignal);

    //char** new_argv = NULL;
    std::vector<std::string> newargv;

    //cout << "ARGC" << argc << endl ;
 //   if(PEBL_WIN32)
 //  {
 //     myEnv->SetExecutableName(argv[0]);
 //   }

    //cout << PEBL_WIN32 << endl;
    if(newargc == 1)
        {
            //This indicates there are no command-line arguments.

#ifdef PEBL_OSX

             cout << "No command line arguments\n";


            //First, find the location of the app bundle:
			CFBundleRef mainBundle = CFBundleGetMainBundle();
			CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
			char resourcepath[PATH_MAX];
			if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)resourcepath, PATH_MAX))
			{
				PError::SignalFatalError("Unable to identify resource location.\n");// error!
			}
			CFRelease(resourcesURL);


            //Identify location for the launcher script, which should be in the resources path.
            std::string script = "/launcher.pbl";
			std::string base = (std::string)resourcepath ;
			std::string launch = base + script;


            //Identify home directory; it is an environment variable.
			std::string home = "";
			char* val = getenv("HOME");
			if(val)
			{
				home = val;
			}


            //The launcher takes the resources directory as an argument, so create the argument
            std::string v = std::string("-v");

            //Set up the new argv/argc, to contain the launcher and the resource path
            newargc  = 4;


            //Now, everything is ready.  Check for the pebl directory, if it  exists,
            //change to that directory, and select the launcher script to run.
			if(PEBLUtility::FileExists(home + "/Documents/pebl-exp.0.14/"))
			   {

                  //Move to the right directory and run the launcher
				    script = (std::string)resourcepath + (std::string)"/launcher.pbl";
					base = home + "/Documents/pebl-exp.0.14/";
                    PEBLUtility::SetWorkingDirectory(base);
                    launch = script;

                     //In this case, don't specify resources on the command line, so we only need 2 arguments.
				   newargc = 2;

                   newargv.push_back(argv[0]);
                   newargv.push_back(launch);

                   //argv = new_argv;
                   //cout << newargv[0] << " " << newargv[1]  << endl;

			   } else{
                   //pebl-exp.xx does not exist.  We need to run the launcher using the command line argument of resources to
                   //know where to copy from.
                   newargc = 4;

                   newargv.push_back(argv[0]);
                   newargv.push_back(launch);
                   newargv.push_back(v);
                   newargv.push_back(resourcepath);
                   //argv = new_argv;
                   //cout << newargv[0] << " " << newargv[1] << " " << newargv[2] << " " << newargv[3] << endl;

                }



            //End OSX-specific code
#elif defined(PEBL_WIN32)

           //cout << "Autolaunching PEBL\n";
           string basedir = PEBLUtility::StripFile(argv[0]) + "..\\";
            //cout <<"basedir:"<< basedir << endl;

//This may work for vista+
//TCHAR szFolderPath[MAX_PATH];
//if (!SHGetSpecialFolderPath(NULL, szFolderPath,    CSIDL_DEFAULT_MYDOCUMENTS, FALSE))
//{
//    // Uh-oh! An error occurred; handle it.
//}

#if 0
//TCHAR szPath[MAX_PATH];
//if(SUCCEEDED(SHGetFolderPath(NULL,
//                             CSIDL_DEFAULT_MYDOCUMENTS,
//                             NULL,
//                             0,
//                             szPath)))
//{
//    PathAppend(szPath, TEXT("New Doc.txt"));
//    HANDLE hFile = CreateFile(szPath, ...);
//}
 //   std::string docdir = (std::string)szFolderPath;
//
//
 //   string destdir = docdir + "\\pebl-exp.0.13\"";
//    cout << "Destination: " << destdir << endl;
//
#endif
			//See if $launcher.pbl exist.
            // If so, run with those arguments.
			std::string script = "bin\\launcher.pbl";
			std::string launch = basedir + script;

			std::string v = (std::string)"-v";

              //cout << "basedir: " << basedir << endl ;
              //cout << "script " << script << endl ;
              //cout << "launch: " << launch << endl ;


#if (0)
//			if(PEBLUtility::FileExists(destdir))
			   {
			        cout << "File already exists!!!!!!!!!!!!\n";

                  //Move to the right directory.

				    script = "\""+(std::string)destdir + (std::string)"\\fileselect.pbl\"";
				  //  chdir(distdir.c_str());
				    launch = script;

				    v = "";
				   newargc = 2;
			   }
#endif

            //Now, launch the script file we care about.
			std::cout << "*************************launch script:" << launch << endl;
            newargc = 4;

            newargv.push_back(argv[0]);
            newargv.push_back(launch);
            newargv.push_back(v);
            newargv.push_back(basedir);
			//new_argv = new char*[4];
			//new_argv[0]=argv[0];

			//This doesn't work, because launch is gone by the time PEBLInterpret gets run
			//char *plaunch = new char[launch.size()+1];
			//strcpy(plaunch,launch.c_str());
			//char *pv     = new char[v.size()+1];
			//strcpy(pv,v.c_str());
			//char *presources  = new char[basedir.size()+1];
			//strcpy(presources,basedir.c_str());
		//	char *pdest = new char[destdir.size()+1];
		//	strcpy(pdest,destdir.c_str());

			//new_argv[1]= plaunch;
			//new_argv[2]= pv;
			//new_argv[3]= presources;
           // new_argv[4]= pv;
           // new_argv[5]= pdest;
            // argv = new_argv;

        //  cout << argv[0] <<"|" << argv[1] <<"|" << argv[2] <<"|" << argv[3] << endl;
   //END check for Windows
#elif defined PEBL_EMSCRIPTEN
                //Do nothing; no arguments are expected.
#else
            PrintOptions();
            return 1;
#endif
        } else{
            //This is what happens when argc != 1 (when there ARE arguments), on any platform

            for(int i=0; i < argc; i++)
             {
               newargv.push_back(argv[i]);
                cout << argv[i] << endl;
             }
        }

    return PEBLInterpret(newargc, newargv);
}


//This returns a list of the files listed on the command-line.
std::list<std::string> GetFiles(int argc,  std::vector<std::string> argv)
{

    std::list<std::string> tmp;
    std::vector<std::string>::iterator i = argv.begin();


//    i++;

    while(i != argv.end())//int i = 1; i < argc; i++) //skip the first argv, which is just executable name.
        {
            if(i->compare( "-v")==0 ||
               i->compare("-V")==0 ||
               i->compare( "-s")==0 ||
               i->compare( "-S") == 0 ||
               i->compare( "--language")==0 ||
               i->compare("--pfile")==0)

                {
                    //This is the variable switch.  get rid of it and the next argument.
                    i++;
                }
            else if (i->compare("--driver")==0 ||
                     i->compare("--display")==0 ||
                     i->compare("--depth")==0 )
                {
                    //This is a video driver switch.
                    i++;
                }
            else if (i->compare("--windowed")==0 ||
                     i->compare("--fullscreen")==0 ||
                     i->compare("--unicode")==0 ||
                     i->compare("--resizeable")==0 ||
                     i->compare("--resizable")==0)

                {
                    //Don't bother incrementing 'i'
                }
            else
                {
                   // cout << "Adding: [" << *i << "]" << endl;

                    tmp.push_back(std::string(*i));
                }
            i++;
        }
    return tmp;
}

void PrintOptions()
{
    cout << "-------------------------------------------------------------------------------\n";
    cout << "PEBL: The Psychology Experiment Building Language\n";
    cout << "Version 0.14\n";
    cout << "(c) 2003-2014 Shane T. Mueller, Ph.D.\n";
    cout << "smueller@obereed.net   http://pebl.sf.net\n";
    cout << "-------------------------------------------------------------------------------\n";

    cout << "Usage:  Invoke pebl with the experiment script files (.pbl) and command-line\n";
    cout << "arguments.\n\n";
    cout << "example: pebl experiment.pbl -v sub1 --fullscreen --display 800x600 --driver dga\n\n";
    cout << "COMMAND-LINE OPTIONS:\n";
    cout << "-v VALUE1 -v VALUE2\n";
    cout << "  Invokes script and passes VALUE1 and VALUE2 (and any text immediately\n" ;
    cout << "  following -v) to a list in the argument of the Start() function.\n\n";
    cout << "-s IDENTIFIER\n";
    cout << "  Initiates the global variable gSubNum to IDENTIFIER.  If not set here,\n";
    cout << " gSubNum is initiated to 0.\n\n";
    cout << "--driver <drivername>\n";
    cout << "  Sets the video driver, when there is a choice.  For linux SDL, options xf86,\n";
    cout << "  dga, svgalib (from console).  Also controlled via environment variables.\n\n";
    cout << "  On Windows, use either windib or directx\n";
    cout << "--display  <widthxheight>\n";
    cout << "  Controls the screen width and height (in pixels). Screen resolution defaults\n";
    cout << "  to the current screen resolution. In fullscreen mode, PEBL will check whether \n";
    cout << "  the resolution is available for the video screen, and use the default mode if not\n";
    cout << "  Note: Custom screen dimensions can be controlled in-script.\n\n";
    cout << "--depth\n";
    cout << "  Controls the pixel depth.  Depends on your video card.  Currently,\n";
    cout << "  depths of 2,8,15,16,24, and 32 are allowed on the command-line.\n";
    cout << "--language <2 char lang code>\n";
    cout << "  Allows you to specify at the command line a language to enable \n selecting different text labels.\n";
    cout << "--windowed\n";
    cout << "--fullscreen\n";
    cout << "  Controls whether the script will run in a window or fullscreen.\n\n";
    cout << "--resizeable\n";
    cout << "--resizable\n";
    cout << "  Controls whether the window will be resizeable (only in windowed mode)\n\n";
    cout << "--unicode\n";
    cout << "  Turns on unicode handling, with slight overhead\n";
    cout << "--pfile <filename>\n";
    cout << "  Specifies which parameter file to use, gets bound to variable gParamFile.\n";

}
