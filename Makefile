#//////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////
#//
#//	Copyright (c) 2003-2014
#//	Shane T. Mueller, Ph.D.  smueller at obereed dot net
#//
#//     This file is part of the PEBL project.
#//
#//    PEBL is free software; you can redistribute it and/or modify
#//    it under the terms of the GNU General Public License as published by
#//    the Free Software Foundation; either version 2 of the License, or
#//    (at your option) any later version.
#//
#//    PEBL is distributed in the hope that it will be useful,
#//    but WITHOUT ANY WARRANTY; without even the implied warranty of
#//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#//    GNU General Public License for more details.
#//
#//    You should have received a copy of the GNU General Public License
#//    along with PEBL; if not, write to the Free Software
#//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  
#//    02111-1307 USA
#//
#//////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////

#This only affects install location.  The binary should be 
#locatable anywhere
PREFIX = /usr/local/

PEBL_VERSION =0.14
USE_WAAVE=1       ##Optional; comment out to turn off waave multimedia library
USE_AUDIOIN=1     ##Optional; comment out to turn off  sdl_audioin library
USE_NETWORK=1     ##Optional; comment out to turn off sdl_net library.
USE_PORTS=1 
USE_HTTP=1      ##Optional; turn on/off for http get/set

USE_DEBUG = 1     ##Optional; turn on/off debugging stuff.

C   = gcc
CXX = g++ 
#C = ~/src/emscripten-master/emcc
#CXX = ~/src/emscripten-master/em++
#C = clang
#CXX = clang++

ifdef USE_DEBUG
DEBUGFLAGS =  -DPEBL_DEBUG -g
else
DEBUGFLAGS = 
endif
CFLAGS =   -O3 -std=c99 -DPREFIX=$(PREFIX) -g 

CXXFLAGS0 =  -g -O3  -DPEBL_UNIX  -DPEBL_LINUX -DENABLE_BINRELOC -DPREFIX=$(PREFIX) 


ifdef USE_WAAVE
#	@echo "Using WAAVE movie library";
	CXXFLAGS1 = -DPEBL_MOVIES  
	LINKOPTS1 = -lwaave
endif

ifdef USE_AUDIOIN
#	@echo "Using audio in library"
	CXXFLAGS2 = -DPEBL_AUDIOIN
	LINKOPTS2 = -lsdl_audioin
endif


ifdef USE_NETWORK
      CXXFLAGS3 = -DPEBL_NETWORK
      LINKOPTS3 = -lSDL_net
endif

ifdef USE_PORTS
	CXXFLAGS4 = -DPEBL_USEPORTS
##	CFLAGS4 =  -DPEBL_USEPORTS
endif



ifdef USE_HTTP
	CXXFLAGS5 = -DPEBL_HTTP  
endif



CXXFLAGS = $(CXXFLAGS0) $(CXXFLAGS1) $(CXXFLAGS2) $(CXXFLAGS3) $(CXXFLAGS4) $(CXXFLAGS5)
LINKOPTS = $(LINKOPTS1) $(LINKOPTS2) $(LINKOPTS3)

SDL_CONFIG = /usr/bin/sdl-config

SDL_FLAGS = -I/usr/include/SDL -I/usr/local/include -D_REENTRANT -L/usr/lib -L/usr/local/lib

#ifeq($(USE_WAAVE),1)
#SDL_FLAGS = $(SDLFLAGS) -L/home/smueller/Projects/src/waave-1.0/src 
#endif

#SDL_LIBS = -L/usr/lib -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL -lpthread -lSDLmain


#Comment/uncomment below on OSX
#OSX_FLAGS = -framework AppKit -lSDLmain -DPEBL_OSX
OSX_FLAGS =

#SDLIMG_FLAGS =  -L/usr/lib -L/usr/local/lib -Wl,-rpath,/usr/lib
#SDLIMG_FLAGS =  -L/usr/lib -Wl,-rpath,/usr/lib
#SDLIMG_LIBS =   -lSDL -lSDLmain -lpthread -lSDL_image -lSDL_net 

SHELL = /bin/bash
BISON = /usr/bin/bison
FLEX  = /usr/bin/flex

BIN_DIR  = bin
SBIN_DIR = sbin
OBJ_DIR  = obj
OUT_DIR  = output
SRC_DIR  = src
BASE_DIR = src/base
APPS_DIR = src/apps
LIBS_DIR = src/libs
OBJECTS_DIR = src/objects
DEVICES_DIR = src/devices
PLATFORMS_DIR = src/platforms
SDL_DIR = src/platforms/sdl
UTIL_DIR = src/utility
TEST_DIR = src/tests


vpath %.o   $(OBJ_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.c   $(SRC_DIR)
vpath %.h   $(SRC_DIR)
vpath %.hpp $(SRC_DIR)
vpath %.y   $(SRC_DIR)
vpath %.l   $(SRC_DIR)


PUTILITIES_SRC = $(UTIL_DIR)/PEBLUtility.cpp \
		$(UTIL_DIR)/PError.cpp \
		$(UTIL_DIR)/BinReloc.cpp \
		$(UTIL_DIR)/PEBLPath.cpp \
		$(UTIL_DIR)/PEBLHTTP.cpp \
		$(UTIL_DIR)/happyhttp.cpp \
		$(UTIL_DIR)/md5.cpp


PUTILITIES_OBJ1  = $(patsubst %.cpp, %.o, $(PUTILITIES_SRC))
PUTILITIES_OBJ  = $(patsubst %.c, %.o, $(PUTILITIES_OBJ1))   ##Get the .c file
PUTILITIES_INC1  = $(patsubst %.cpp, %.h, $(PUTILITIES_SRC))
PUTILITIES_INC  = $(patsubst %.c, %.h, $(PUTILITIES_INC1))   ##Get the plain .c file

MAN_DIR  =   doc/pman
PEBL_DOCSRC = 		$(MAN_DIR)/main.tex \
			$(MAN_DIR)/intro.tex \
			$(MAN_DIR)/chap3.tex \
			$(MAN_DIR)/chap4.tex \
			$(MAN_DIR)/chap5.tex \
			$(MAN_DIR)/launcher.tex \
			$(MAN_DIR)/reference.tex \
			$(MAN_DIR)/colors.tex 

PEBLBASE_SRCXX =	$(BASE_DIR)/Evaluator.cpp \
			$(BASE_DIR)/FunctionMap.cpp \
			$(BASE_DIR)/grammar.tab.cpp \
			$(BASE_DIR)/PEBLObject.cpp \
			$(BASE_DIR)/Loader.cpp \
			$(BASE_DIR)/PComplexData.cpp \
			$(BASE_DIR)/PList.cpp \
			$(BASE_DIR)/PNode.cpp \
			$(BASE_DIR)/VariableMap.cpp \
			$(BASE_DIR)/Variant.cpp \
			$(DEVICES_DIR)/PEventLoop.cpp 

PEBLBASE_OBJXX = $(patsubst %.cpp, %.o, $(PEBLBASE_SRCXX))


##This just collects plain .c files, 
PEBLBASE_SRC = lex.yy.c \
		$(UTIL_DIR)/rs232.c
PEBLBASE_OBJ = $(patsubst %.c, %.o, $(PEBLBASE_SRC))


##These are 3rd party libraries we include directly.
#LIB_SRC      = libs/happyhttp/happyhttp.cpp
#LIB_OBJ      =$(patsubst %.cpp, %.o, $(LIB_SRC))



POBJECT_SRC  =  $(OBJECTS_DIR)/PEnvironment.cpp \
		$(OBJECTS_DIR)/PWidget.cpp \
		$(OBJECTS_DIR)/PWindow.cpp  \
		$(OBJECTS_DIR)/PImageBox.cpp \
		$(OBJECTS_DIR)/PCanvas.cpp  \
		$(OBJECTS_DIR)/PColor.cpp  \
		$(OBJECTS_DIR)/PDrawObject.cpp \
		$(OBJECTS_DIR)/PFont.cpp \
		$(OBJECTS_DIR)/PTextObject.cpp \
		$(OBJECTS_DIR)/PLabel.cpp \
		$(OBJECTS_DIR)/PTextBox.cpp \
		$(OBJECTS_DIR)/PMovie.cpp \
		$(OBJECTS_DIR)/PCustomObject.cpp 
##		$(PUTILITIES_SRC)


POBJECT_OBJ  = $(patsubst %.cpp, %.o, $(POBJECT_SRC))
POBJECT_INC  = $(patsubst %.cpp, %.h, $(POBJECT_SRC))


PDEVICES_SRC =  $(DEVICES_DIR)/PDevice.cpp \
	$(DEVICES_DIR)/PEventQueue.cpp \
	$(DEVICES_DIR)/PEvent.cpp\
	$(DEVICES_DIR)/PKeyboard.cpp \
	$(DEVICES_DIR)/PTimer.cpp \
	$(DEVICES_DIR)/DeviceState.cpp \
	$(DEVICES_DIR)/PStream.cpp \
	$(DEVICES_DIR)/PAudioOut.cpp \
	$(DEVICES_DIR)/PNetwork.cpp \
	$(DEVICES_DIR)/PJoystick.cpp \
	$(DEVICES_DIR)/PParallelPort.cpp \
	$(DEVICES_DIR)/PComPort.cpp 



PDEVICES_OBJ  = $(patsubst %.cpp, %.o, $(PDEVICES_SRC))
PDEVICES_INC  = $(patsubst %.cpp, %.h, $(PDEVICES_SRC))



PLATFORM_SDL_SRC  =	$(SDL_DIR)/PlatformEnvironment.cpp \
			$(SDL_DIR)/PlatformWidget.cpp \
			$(SDL_DIR)/PlatformWindow.cpp \
			$(SDL_DIR)/PlatformImageBox.cpp \
			$(SDL_DIR)/PlatformKeyboard.cpp \
			$(SDL_DIR)/PlatformFont.cpp \
			$(SDL_DIR)/PlatformLabel.cpp \
			$(SDL_DIR)/PlatformTextBox.cpp \
			$(SDL_DIR)/PlatformTimer.cpp	\
			$(SDL_DIR)/PlatformDrawObject.cpp \
			$(SDL_DIR)/PlatformCanvas.cpp \
			$(SDL_DIR)/SDLUtility.cpp \
		   	$(SDL_DIR)/PlatformEventQueue.cpp \
			$(SDL_DIR)/PlatformAudioIn.cpp \
			$(SDL_DIR)/PlatformAudioOut.cpp \
			$(SDL_DIR)/PlatformNetwork.cpp \
			$(SDL_DIR)/PlatformJoystick.cpp\
			$(SDL_DIR)/PlatformMovie.cpp 


PLATFORM_SDL_OBJ  = 	$(patsubst %.cpp, %.o, $(PLATFORM_SDL_SRC))
PLATFORM_SDL_INC  = 	$(patsubst %.cpp, %.h, $(PLATFORM_SDL_SRC))


FUNCTIONLIB_SRC = $(LIBS_DIR)/PEBLMath.cpp \
	  	  $(LIBS_DIR)/PEBLStream.cpp \
		  $(LIBS_DIR)/PEBLObjects.cpp \
                  $(LIBS_DIR)/PEBLEnvironment.cpp \
                  $(LIBS_DIR)/PEBLList.cpp \
                  $(LIBS_DIR)/PEBLString.cpp



FUNCTIONLIB_OBJ =  $(patsubst %.cpp, %.o, $(FUNCTIONLIB_SRC))
FUNCTIONLIB_INC =  $(patsubst %.cpp, %.h, $(FUNCTIONLIB_SRC))



VCG_MAKER_SRC = $(BASE_DIR)/VCG.cpp  $(PEBLBASE_SRCXX)  $(POBJECT_SRC) $(FUNCTIONLIB_SRC) $(PUTILITY_SRC)
VCG_MAKER_OBJ = $(patsubst %.cpp, %.o, $(VCG_MAKER_SRC))
VCG_MAKER_INC = $(patsubst %.cpp, %.h, $(VCG_MAKER_SRC))


PEBLMAIN_SRC = 		$(APPS_DIR)/PEBL.cpp \
			$(PEBLBASE_SRCXX) \
			$(PDEVICES_SRC) \
			$(FUNCTIONLIB_SRC) \
			$(POBJECT_SRC) \
			$(PUTILITIES_SRC) \
			$(PLATFORM_SDL_SRC)
###			$(LIB_SRC)

PEBLMAIN_OBJ = $(patsubst %.cpp, %.o, $(PEBLMAIN_SRC))
PEBLMAIN_INC = $(patsubst %.cpp, %.h, $(PEBLMAIN_SRC))

PEBLMAIN_EXTRA = $(LIBS_DIR)/Functions.h \
	           	$(OBJECTS_DIR)/RGBColorNames.h 


DIRS = \
	$(OBJ_DIR) \
	$(OBJ_DIR)/$(SRC_DIR) \
	$(OBJ_DIR)/$(BASE_DIR) \
	$(OBJ_DIR)/$(APPS_DIR) \
	$(OBJ_DIR)/$(OBJECTS_DIR) \
	$(OBJ_DIR)/$(LIBS_DIR) \
	$(OBJ_DIR)/$(DEVICES_DIR) \
	$(OBJ_DIR)/$(PLATFORMS_DIR) \
	$(OBJ_DIR)/$(SDL_DIR) \
	$(OBJ_DIR)/$(UTIL_DIR) \
	$(OBJ_DIR)/$(TEST_DIR) 


##############################
# Dependencies
#
##	   -L$(PREFIX)/lib -lSDL -lpthread -lSDL_image -lSDL_ttf -lSDL_gfx  -lSDL_net -lpng -lSDL_audioin\
#  SDL_FLAGS = -I/usr/include/SDL -I/usr/local/include -D_REENTRANT -L/usr/lib -L/usr/local/lib
#	-L/home/smueller/Projects/src/waave-1.0/src -L/usr/lib  -L/usr/local/lib \
#	-I/usr/include/SDL -I/usr/include -I/usr/local/include -D_REENTRANT \

#d: 
#	@echo $(PEBLMAIN_OBJ)


main:  $(DIRS) $(PEBLMAIN_OBJ) $(PEBLMAIN_INC)
	$(CXX) $(CXXFLAGS) -Wall -Wl,-rpath -Wl,LIBDIR $(DEBUGFLAGS) \
	$(SDL_FLAGS) -g	\
	-o $(BIN_DIR)/pebl \
	$(OSX_FLAGS) $(BASE_DIR)/$(PEBLBASE_SRC) \
	$(patsubst %.o, $(OBJ_DIR)/%.o, $(PEBLMAIN_OBJ)) \
	-lSDL -lSDLmain -lpthread -lSDL_image -lSDL_net -lSDL_ttf -lSDL_gfx  \
	-lpng   $(LINKOPTS)
##  -Wl,-V #verbose linking 
## -Wl,-rpath,/usr/lib \

##Make emscripten target:
em: 
	~/src/emscripten-master/emcc -O2 src/apps/PEBL.cpp -I..  -o pebl.raw.js -s TOTAL_MEMORY=52428800 



doc: $(PEBL_DOCSRC)
	cd doc/pman; pdflatex main.tex
	cp doc/pman/main.pdf doc/pman/PEBLManual$(PEBL_VERSION).pdf

deb:    main doc
	epm -f deb pebl

parse:
	bison -d $(BASE_DIR)/grammar.y -o $(BASE_DIR)/grammar.tab.cpp
	flex -o$(BASE_DIR)/lex.yy.c  $(BASE_DIR)/Pebl.l 

parse-debug:
	bison -d $(BASE_DIR)/grammar.y -t --verbose --graph=bison.vcg -o $(BASE_DIR)/grammar.tab.cpp
	flex  -o$(BASE_DIR)/lex.yy.c -d $(BASE_DIR)/Pebl.l

.PHONY: tests


%.h:
	@echo Updating %.h;
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -g -c $^ -o $(OBJ_DIR)/$@ $(SDL_FLAGS)


$(DIRS): %:
	-test -d $@ || mkdir $@


dox: $(PEBLBASE_SRCXX)
	doxygen pebl.dox


remake: ready clean $(PROGS)
ready:
	-rm -f $(OUT_DIR)/*

.PHONY: dep
dep:
	$(CXX) -MM $(CXXFLAGS)    $(PEBLMAIN_SRC)  > .depend

.PHONY: clean
clean:
	-rm -f $(patsubst %.o, $(OBJ_DIR)/%.o, $(PEBLBASE_OBJ)) \
	$(patsubst %.o,  $(OBJ_DIR)/%.o, $(PEBLBASE_OBJSXX))  \
	$(patsubst %.o,  $(OBJ_DIR)/%.o, $(PEBLMAIN_OBJ))


.PHONY: install

uninstall:
	rm -Rf $(PREFIX)bin/pebl
	rm -Rf $(PREFIX)share/pebl

install: uninstall

	install -d $(PREFIX)bin/	

	cp bin/pebl $(PREFIX)bin/pebl
	rm -Rf $(PREFIX)share/pebl
	install -d $(PREFIX)share/pebl
	install -d $(PREFIX)share/pebl/media
	install -d $(PREFIX)share/pebl/pebl-lib
	install -d $(PREFIX)share/pebl/doc
	install -d $(PREFIX)share/pebl/battery

	cp -R media/* $(PREFIX)share/pebl/media/
	rm -rf `find $(PREFIX)share/pebl/media -type d -name .svn`
	cp  pebl-lib/*.pbl $(PREFIX)share/pebl/pebl-lib/
	cp doc/pman/PEBLManual$(PEBL_VERSION).pdf $(PREFIX)/share/pebl/doc
	cp bin/launcher.pbl $(PREFIX)/share/pebl/pebl-lib/
	chmod -R uga+r $(PREFIX)share/pebl/
#	chmod +s $(PREFIX)bin/pebl ##suid root
	cp -R battery/* $(PREFIX)share/pebl/battery
	cp battery/\.\.png $(PREFIX)share/pebl/battery
	cp battery/\.\.about.txt $(PREFIX)share/pebl/battery
	rm -rf `find $(PREFIX)share/pebl/battery -type d -name .svn`
	rm `find $(PREFIX)share/pebl/battery | grep \~`
	rm -Rf `find $(PREFIX)share/pebl/battery | grep 'data'`
	rm -f $(PREFIX)share/pebl/battery/launch.bat
	rm -f $(PREFIX)share/pebl/battery/PEBLLaunch-log.txt
	rm -f $(PREFIX)share/pebl/battery/*.config
	rm -f $(PREFIX)share/pebl/battery/makelinks-mac.sh
##Now, convert all the battery files to unix format.
	find $(PREFIX)share/pebl/battery -name '*pbl' -exec dos2unix {} \;

ifeq (.depend,$(wildcard .depend))
include .depend
endif
