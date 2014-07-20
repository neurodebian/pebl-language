//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PKeyboard.h
//    Purpose:    Primary Keyboard Interface Device
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2004 Shane T. Mueller <smueller@obereed.net>
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
#ifndef __PKEYBOARD_H__
#define __PKEYBOARD_H__

#include "PDevice.h"

#include <list>
#include <string>

class ValueState;

//The following mimics the SDL almost exactly. 
enum PEBLKey 
    {
        /* The keyboard syms have been cleverly chosen to map to ASCII */
        PEBLKEY_UNKNOWN		= 0,
        PEBLKEY_FIRST		= 0,
        PEBLKEY_NOTHING    = 0,    //This is a special key code
        PEBLKEY_ANYKEY     = 1,    //This is a special key code 
        PEBLKEY_BACKSPACE	= 8,
        PEBLKEY_TAB	    = 9,
        PEBLKEY_CLEAR      = 12,
        PEBLKEY_RETURN	= 13,
        PEBLKEY_PAUSE		= 19,
        PEBLKEY_ESCAPE	= 27,
        PEBLKEY_SPACE		= 32,
        PEBLKEY_EXCLAIM		= 33,
        PEBLKEY_QUOTEDBL	= 34,
        PEBLKEY_HASH		= 35,
        PEBLKEY_DOLLAR		= 36,
        PEBLKEY_AMPERSAND	= 38,
        PEBLKEY_QUOTE		= 39,
        PEBLKEY_LEFTPAREN	= 40,
        PEBLKEY_RIGHTPAREN	= 41,
        PEBLKEY_ASTERISK	= 42,
        PEBLKEY_PLUS		= 43,
        PEBLKEY_COMMA		= 44,
        PEBLKEY_MINUS		= 45,
        PEBLKEY_PERIOD		= 46,
        PEBLKEY_SLASH		= 47,
        PEBLKEY_0			= 48,
        PEBLKEY_1			= 49,
        PEBLKEY_2			= 50,
        PEBLKEY_3			= 51,
        PEBLKEY_4			= 52,
        PEBLKEY_5			= 53,
        PEBLKEY_6			= 54,
        PEBLKEY_7			= 55,
        PEBLKEY_8			= 56,
        PEBLKEY_9			= 57,
        PEBLKEY_COLON		= 58,
        PEBLKEY_SEMICOLON	= 59,
        PEBLKEY_LESS		= 60,
        PEBLKEY_EQUALS		= 61,
        PEBLKEY_GREATER		= 62,
        PEBLKEY_QUESTION	= 63,
        PEBLKEY_AT			= 64,
        /* 
           Skip uppercase letters
        */
        PEBLKEY_LEFTBRACKET	= 91,
        PEBLKEY_BACKSLASH	= 92,
        PEBLKEY_RIGHTBRACKET= 93,
        PEBLKEY_CARET		= 94,
        PEBLKEY_UNDERSCORE	= 95,
        PEBLKEY_BACKQUOTE	= 96,
        PEBLKEY_a			= 97,
        PEBLKEY_b			= 98,
        PEBLKEY_c			= 99,
        PEBLKEY_d			= 100,
        PEBLKEY_e			= 101,
        PEBLKEY_f			= 102,
        PEBLKEY_g			= 103,
        PEBLKEY_h			= 104,
        PEBLKEY_i			= 105,
        PEBLKEY_j			= 106,
        PEBLKEY_k			= 107,
        PEBLKEY_l			= 108,
        PEBLKEY_m			= 109,
        PEBLKEY_n			= 110,
        PEBLKEY_o			= 111,
        PEBLKEY_p			= 112,
        PEBLKEY_q			= 113,
        PEBLKEY_r			= 114,
        PEBLKEY_s			= 115,
        PEBLKEY_t			= 116,
        PEBLKEY_u			= 117,
        PEBLKEY_v			= 118,
        PEBLKEY_w			= 119,
        PEBLKEY_x			= 120,
        PEBLKEY_y			= 121,
        PEBLKEY_z			= 122,
        PEBLKEY_DELETE		= 127,
        /* End of ASCII mapped keysyms */

        /* International keyboard syms */
        PEBLKEY_WORLD_0		= 160,		/* 0xA0 */
        PEBLKEY_WORLD_1		= 161,
        PEBLKEY_WORLD_2		= 162,
        PEBLKEY_WORLD_3		= 163,
        PEBLKEY_WORLD_4		= 164,
        PEBLKEY_WORLD_5		= 165,
        PEBLKEY_WORLD_6		= 166,
        PEBLKEY_WORLD_7		= 167,
        PEBLKEY_WORLD_8		= 168,
        PEBLKEY_WORLD_9		= 169,
        PEBLKEY_WORLD_10	= 170,
        PEBLKEY_WORLD_11	= 171,
        PEBLKEY_WORLD_12	= 172,
        PEBLKEY_WORLD_13	= 173,
        PEBLKEY_WORLD_14	= 174,
        PEBLKEY_WORLD_15	= 175,
        PEBLKEY_WORLD_16	= 176,
        PEBLKEY_WORLD_17	= 177,
        PEBLKEY_WORLD_18	= 178,
        PEBLKEY_WORLD_19	= 179,
        PEBLKEY_WORLD_20	= 180,
        PEBLKEY_WORLD_21	= 181,
        PEBLKEY_WORLD_22	= 182,
        PEBLKEY_WORLD_23	= 183,
        PEBLKEY_WORLD_24	= 184,
        PEBLKEY_WORLD_25	= 185,
        PEBLKEY_WORLD_26	= 186,
        PEBLKEY_WORLD_27	= 187,
        PEBLKEY_WORLD_28	= 188,
        PEBLKEY_WORLD_29	= 189,
        PEBLKEY_WORLD_30	= 190,
        PEBLKEY_WORLD_31	= 191,
        PEBLKEY_WORLD_32	= 192,
        PEBLKEY_WORLD_33	= 193,
        PEBLKEY_WORLD_34	= 194,
        PEBLKEY_WORLD_35	= 195,
        PEBLKEY_WORLD_36	= 196,
        PEBLKEY_WORLD_37	= 197,
        PEBLKEY_WORLD_38	= 198,
        PEBLKEY_WORLD_39	= 199,
        PEBLKEY_WORLD_40	= 200,
        PEBLKEY_WORLD_41	= 201,
        PEBLKEY_WORLD_42	= 202,
        PEBLKEY_WORLD_43	= 203,
        PEBLKEY_WORLD_44	= 204,
        PEBLKEY_WORLD_45	= 205,
        PEBLKEY_WORLD_46	= 206,
        PEBLKEY_WORLD_47	= 207,
        PEBLKEY_WORLD_48	= 208,
        PEBLKEY_WORLD_49	= 209,
        PEBLKEY_WORLD_50	= 210,
        PEBLKEY_WORLD_51	= 211,
        PEBLKEY_WORLD_52	= 212,
        PEBLKEY_WORLD_53	= 213,
        PEBLKEY_WORLD_54	= 214,
        PEBLKEY_WORLD_55	= 215,
        PEBLKEY_WORLD_56	= 216,
        PEBLKEY_WORLD_57	= 217,
        PEBLKEY_WORLD_58	= 218,
        PEBLKEY_WORLD_59	= 219,
        PEBLKEY_WORLD_60	= 220,
        PEBLKEY_WORLD_61	= 221,
        PEBLKEY_WORLD_62	= 222,
        PEBLKEY_WORLD_63	= 223,
        PEBLKEY_WORLD_64	= 224,
        PEBLKEY_WORLD_65	= 225,
        PEBLKEY_WORLD_66	= 226,
        PEBLKEY_WORLD_67	= 227,
        PEBLKEY_WORLD_68	= 228,
        PEBLKEY_WORLD_69	= 229,
        PEBLKEY_WORLD_70	= 230,
        PEBLKEY_WORLD_71	= 231,
        PEBLKEY_WORLD_72	= 232,
        PEBLKEY_WORLD_73	= 233,
        PEBLKEY_WORLD_74	= 234,
        PEBLKEY_WORLD_75    = 235,
        PEBLKEY_WORLD_76	= 236,
        PEBLKEY_WORLD_77	= 237,
        PEBLKEY_WORLD_78	= 238,
        PEBLKEY_WORLD_79	= 239,
        PEBLKEY_WORLD_80	= 240,
        PEBLKEY_WORLD_81	= 241,
        PEBLKEY_WORLD_82	= 242,
        PEBLKEY_WORLD_83	= 243,
        PEBLKEY_WORLD_84	= 244,
        PEBLKEY_WORLD_85	= 245,
        PEBLKEY_WORLD_86	= 246,
        PEBLKEY_WORLD_87	= 247,
        PEBLKEY_WORLD_88	= 248,
        PEBLKEY_WORLD_89	= 249,
        PEBLKEY_WORLD_90	= 250,
        PEBLKEY_WORLD_91	= 251,
        PEBLKEY_WORLD_92	= 252,
        PEBLKEY_WORLD_93	= 253,
        PEBLKEY_WORLD_94	= 254,
        PEBLKEY_WORLD_95	= 255,		/* 0xFF */

        /* Numeric keypad */
        PEBLKEY_KP0		    = 256,
        PEBLKEY_KP1	        = 257,
        PEBLKEY_KP2	        = 258,
        PEBLKEY_KP3         = 259,
        PEBLKEY_KP4         = 260,
        PEBLKEY_KP5         = 261,
        PEBLKEY_KP6         = 262,
        PEBLKEY_KP7         = 263,
        PEBLKEY_KP8         = 264,
        PEBLKEY_KP9         = 265,
        PEBLKEY_KP_PERIOD   = 266,
        PEBLKEY_KP_DIVIDE   = 267,
        PEBLKEY_KP_MULTIPLY = 268,
        PEBLKEY_KP_MINUS	= 269,
        PEBLKEY_KP_PLUS		= 270,
        PEBLKEY_KP_ENTER	= 271,
        PEBLKEY_KP_EQUALS	= 272,

        /* Arrows + Home/End pad */
        PEBLKEY_UP			= 273,
        PEBLKEY_DOWN		= 274,
        PEBLKEY_RIGHT		= 275,
        PEBLKEY_LEFT		= 276,
        PEBLKEY_INSERT		= 277,
        PEBLKEY_HOME		= 278,
        PEBLKEY_END		    = 279,
        PEBLKEY_PAGEUP		= 280,
        PEBLKEY_PAGEDOWN	= 281,

        /* Function keys */
        PEBLKEY_F1          = 282,
        PEBLKEY_F2          = 283,
        PEBLKEY_F3          = 284,
        PEBLKEY_F4          = 285,
        PEBLKEY_F5          = 286,
        PEBLKEY_F6          = 287,
        PEBLKEY_F7          = 288,
        PEBLKEY_F8          = 289,
        PEBLKEY_F9          = 290,
        PEBLKEY_F10         = 291,
        PEBLKEY_F11         = 292,
        PEBLKEY_F12         = 293,
        PEBLKEY_F13         = 294,
        PEBLKEY_F14         = 295,
        PEBLKEY_F15         = 296,

        /* Key state modifier keys */
        PEBLKEY_NUMLOCK		= 300,
        PEBLKEY_CAPSLOCK    = 301,
        PEBLKEY_SCROLLOCK   = 302,
        PEBLKEY_RSHIFT		= 303,
        PEBLKEY_LSHIFT		= 304,
        PEBLKEY_RCTRL		= 305,
        PEBLKEY_LCTRL		= 306,
        PEBLKEY_RALT		= 307,
        PEBLKEY_LALT		= 308,
        PEBLKEY_RMETA		= 309,
        PEBLKEY_LMETA		= 310,
        PEBLKEY_LSUPER		= 311,		/* Left "Windows" key */
        PEBLKEY_RSUPER		= 312,		/* Right "Windows" key */
        PEBLKEY_MODE		= 313,		/* "Alt Gr" key */
        PEBLKEY_COMPOSE		= 314,		/* Multi-key compose key */

        /* Miscellaneous function keys */
        PEBLKEY_HELP		= 315,
        PEBLKEY_PRINT		= 316,
        PEBLKEY_SYSREQ		= 317,
        PEBLKEY_BREAK		= 318,
        PEBLKEY_MENU		= 319,
        PEBLKEY_POWER		= 320,		/* Power Macintosh power key */
        PEBLKEY_EURO		= 321,		/* Some european keyboards */
        PEBLKEY_UNDO		= 322,		/* Atari keyboard has Undo */

        /* Add any other keys here */
        PEBLKEY_LAST
    };


/* Enumeration of valid key mods (possibly OR'd together) */
enum PEBLModKey
    {
        PEBLMOD_NONE  = 0x0000,
        PEBLMOD_LSHIFT= 0x0001,
        PEBLMOD_RSHIFT= 0x0002,
        PEBLMOD_LCTRL = 0x0040,
        PEBLMOD_RCTRL = 0x0080,
        PEBLMOD_LALT  = 0x0100,
        PEBLMOD_RALT  = 0x0200,
        PEBLMOD_LMETA = 0x0400,
        PEBLMOD_RMETA = 0x0800,
        PEBLMOD_NUM   = 0x1000,
        PEBLMOD_CAPS  = 0x2000,
        PEBLMOD_MODE  = 0x4000,
        PEBLMOD_RESERVED = 0x8000
    };
    


#define PEBLMOD_CTRL	(PEBLMOD_LCTRL|PEBLMOD_RCTRL)
#define PEBLMOD_SHIFT	(PEBLMOD_LSHIFT|PEBLMOD_RSHIFT)
#define PEBLMOD_ALT    (PEBLMOD_LALT|PEBLMOD_RALT)
#define PEBLMOD_META	(PEBLMOD_LMETA|PEBLMOD_RMETA)


///
///  This is the base Keyboard class.  It is 'virtual' and must
///  be overridden by a PlatformKeyboard class, but contains keycodes
///

class PKeyboard: virtual public PDevice
{
    
public:    


    ///The Standard constructor.  
    PKeyboard();
    
    ///The Standard destructor.  
    virtual ~PKeyboard();


    ///Translate a letter string to the appropriate keyboard symbol
    virtual PEBLKey TranslateString(std::string letter) const;

    virtual std::string TranslateKeyCode(const PEBLKey key)const;

    ///This will test whether a specific key is down,
    ///and return true if it is.
    virtual PEBLKey IsKeyDown(PEBLKey key) const = 0;

    ///This will test whether a specific key is up, and
    ///return true if it is.
    virtual bool IsKeyUp(PEBLKey key) const = 0;
    virtual int GetState(int iface)const; 
    //    virtual int TestDevice(const DeviceState & state) const = 0;

    virtual PEBL_DEVICE_TYPE GetDeviceType(){return PDT_KEYBOARD;};
    virtual int GetModKeys() const;  //This gets an or-ed together representation
    //                         //of which mod keys are pressed.

protected:

    //Inheritable printing Method.
    virtual std::ostream& SendToStream(std::ostream& out)const; 

private:
};





#endif
