//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
////////////////////////////////////////////////////////////////////////////////
//    Name:       utility/PEBLUtility.cpp
//    Purpose:    Miscellaneous Utility Functions used in PEBL
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
#include "PEBLUtility.h"
#include "PError.h"
#include "rc_ptrs.h"
#include "../base/Variant.h"
#include "../base/PComplexData.h"
#include "../base/PList.h"
#include "../devices/PKeyboard.h"
#include "../apps/Globals.h"
#include "md5.h"

#include <errno.h>
#include <ctype.h>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <strstream>
#include <algorithm>

#if !defined(PEBL_OSX)
#include <png.h>
#endif

#include <dirent.h>
//#include <errno.h>


#ifdef PEBL_WIN32
#include <direct.h>
#include <windows.h>
//#include <bits/types.h>
#include <shlobj.h>
#elif defined(PEBL_LINUX)
#include <sys/stat.h>
#include <unistd.h>
#include <bits/types.h>
#include <pwd.h>
#elif defined (PEBL_EMSCRIPTEN)
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif defined (PEBL_OSX)
#include <unistd.h>
#include <pwd.h>
#endif

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h> //For md5file O_RDONLY
#include <sys/types.h>
#include <sys/stat.h>

#if defined(PEBL_LINUX) or defined(PEBL_OSX)
#include <sys/mman.h>
#else
#include "mman.h"

#endif

//Some math libraries contain this, but let's not take any chances.
#define PI 3.141592653589793238462643383279502884197169399375


using std::cout;
using std::endl;

std::string PEBLUtility::ToUpper(const std::string & text)
{
    std::string newtext(text);
    std::transform(newtext.begin(), newtext.end(), newtext.begin(), ::toupper);
    return newtext;
}



std::string PEBLUtility::ToLower(const std::string & text)
{
    std::string newtext(text);
    std::transform(newtext.begin(), newtext.end(), newtext.begin(), ::tolower);
    return newtext;
}


//When given a filename, this will strip the filename from
//the path and return the path. If given a directory name
// (ending with a '/' or '\'), it won't strip that character.
const std::string PEBLUtility::StripFile(const std::string &  file)
{
 //   cout << "Stripping file " << file << endl;
#if defined PEBL_UNIX
    char separator = '/';
#else
    char separator = '\\';
#endif

    int lastsep  = 0;
    unsigned long int i = file.size();
    //end
    //Start at the end of the filename and move backward
    while(i > 0)
        {
            if(file[i] == separator)
                {
                    lastsep = i;
                    return file.substr(0,lastsep+1);
                }
            i--;
        }
    return "";
}
// ///This returns a pointer to an upper-case version of the text.
// ///buffer better be at least n items long.
// void PEBLUtility::ToUpper(const char* text, char* buffer, int n)
// {
//     //Go through each letter, copying the upper-case version to buffer.
//     //Stop before the last letter because we need a \0.
//     int i = 0;
//     while(text[i] != '\0' &&  i < (n-1))
//         {
//             buffer[i] = toupper(text[i]);
//             i++;
//         }
//     //Add an end-of-string character
//     buffer[i] = '\0';
// }



// ///This returns a pointer to a lower-case version of the text.
// void PEBLUtility::ToLower(const char* text, char* buffer, int n)
// {

//     //Go through each letter, copying the lower-case version to buffer.
//     //Stop before the last letter because we need a \0.
//     int i = 0;
//     while(text[i] != '\0' && i < (n-1))
//         {
//             buffer[i] = tolower(text[i]);
//             i++;
//         }

//     //Add an end-of-string character
//     buffer[i] = '\0';


// }


Variant PEBLUtility::Tokenize(const char* line, char separator)
{
    //We have a string with separators in it.  Go through it character by character and
    //form a list out of the tokens.


    PList * plist = new PList;
    int i = 0;
    int begin = 0;
    char * token;

    int tokensize;

    //Go through each item of the string.  Cut a token whenever you get to a separator or
    //a character that might be the end of the line.
    while(true)
        {
            if(line[i] == separator
               || line[i] == '\0'
               || line[i] == 10
               || line[i] == 13
               || separator == 0)
                {

                    //line[i] is the separator; the token is from
                    //begin to line[i-1]

                    //tokensize should be from begin to now, substracting out the separator.
                    tokensize = i-begin+(separator==0);

                    //if separator ==0, tokensize is really one bigger, as the separator width is 0.

                    token = (char*)malloc((tokensize+1) * sizeof(char));
                    strncpy(token, &line[begin], tokensize);
                    token[tokensize]=  '\0';


                    plist->PushBack(Variant(token));
                    begin = i+1;  //move begin to the next piece of text.
                }


            if(line[i] == '\0'|| line[i] == 10  || line[i] == 13)
                break;

            //we need to not copy a final empty element if separator==0
            if(separator==0 and line[begin]=='\0')
                {
                    break;
                }
            i++;

        }

    counted_ptr<PEBLObjectBase> tmpObj = counted_ptr<PEBLObjectBase>(plist);
    PComplexData * pcd  = new PComplexData(tmpObj);
    return Variant(pcd);
}


pDouble PEBLUtility::StringToPDouble(const char * mystring)
{
#if defined(strold)
    return strtold(mystring,0);
#else
    return (pDouble)strtod(mystring,0);
#endif
}



pDouble PEBLUtility::RandomUniform()
{
    return (pDouble)rand() / RAND_MAX;
}


/// It will return a floating-
/// point number which is a sample from the N(0,1) distribution.
/// Values are calculated using the Box-Mueller technique.
pDouble PEBLUtility::RandomNormal()
{

    pDouble x1 = RandomUniform();
    pDouble x2 = RandomUniform();

    return sqrt(-2 * log(x1)) * cos(2 * PI * x2);
}

pDouble PEBLUtility::Log2(pDouble val)
{
#if defined(log2)
    return (pDouble)log2((pDouble)val);
#elif defined(log2l)
    return log2l(val);
#else
    return logl(val) / logl(2);
#endif
}

pInt PEBLUtility::Round(pDouble val)
{
#if defined(round)
    return round((pDouble)val);
#elif defined(roundl)
    return roundl(val);
#else
    return (pInt) floor(val+.5);
#endif
}

pDouble PEBLUtility::Round(pDouble val, pInt prec)
{
    pDouble off = pow(10,prec);
    //cout << "Rounding " << val <<" to : " << off << endl;
#if defined(round)
    return (pDouble)round((pDouble)val*off)/off;
#elif defined(roundl)
    return (pDouble)roundl(val*off)/off;
#else
    return (pDouble) ((pInt)(floor(val*off+.5))/off);
#endif
}

pInt PEBLUtility::Truncate(pDouble val)
{
#if defined(truncl)
    return truncl(val);
#elif defined(trunc)
    return trunc((pDouble)val);
#else
    int sign = val < 0 ? -1: 1;
    return sign * Round(sign * val);
#endif

}



///This does as best as it can to translate the letter string
///into a keyboard key.
PEBLKey PEBLUtility::TranslateString(const std::string & let)
{
    //This should all be loaded into a hash table or map on startup.

    //Use as a default the first letter.

    PEBLKey code = PEBLKey(int(let[0]));
    //First, see if we are only a single character.  If so, rock-n-roll.
    if(let.length() == 1)
        {
            //recode uppercase letters into lowercase.
            if(code > 64 && code < 91)
                code = PEBLKey(int(code) + 32);
            return code;
        }


    std::string letters = PEBLUtility::ToLower(let);

    if(letters == "<RETURN>" || letters == "<return>")
        return PEBLKEY_RETURN;
    if(letters == "<esc>" || letters == "<ESC>")
        return PEBLKEY_ESCAPE;
    if(letters == "<back>" || letters == "<BACK>"
       || letters == "<backspace>" || letters == "<BACKSPACE>"
       )
        return PEBLKEY_BACKSPACE;

    if(letters=="<delete>") return PEBLKEY_DELETE;

    if(letters == "<left>")  return PEBLKEY_LEFT;
    if(letters == "<right>") return PEBLKEY_RIGHT;
    if(letters == "<down>")  return PEBLKEY_DOWN;
    if(letters == "<up>")    return PEBLKEY_UP;



    if(letters == "<f1>")  return PEBLKEY_F1;
    if(letters == "<f2>")  return PEBLKEY_F2;
    if(letters == "<f3>")  return PEBLKEY_F3;
    if(letters == "<f4>")  return PEBLKEY_F4;
    if(letters == "<f5>")  return PEBLKEY_F5;
    if(letters == "<f6>")  return PEBLKEY_F6;
    if(letters == "<f7>")  return PEBLKEY_F7;
    if(letters == "<f8>")  return PEBLKEY_F8;
    if(letters == "<f9>")  return PEBLKEY_F9;
    if(letters == "<f10>")  return PEBLKEY_F10;
    if(letters == "<f11>")  return PEBLKEY_F11;
    if(letters == "<f12>")  return PEBLKEY_F12;
    if(letters == "<f13>")  return PEBLKEY_F13;
    if(letters == "<f14>")  return PEBLKEY_F14;
    if(letters == "<f15>")  return PEBLKEY_F15;


/* Key state modifier keys */

    if(letters == "<numlock>")  return PEBLKEY_NUMLOCK;
    if(letters == "<capslock>")  return PEBLKEY_CAPSLOCK;
    if(letters == "<scrollock>")  return PEBLKEY_SCROLLOCK;
    if(letters == "<lshift>")    return PEBLKEY_LSHIFT;
    if(letters == "<rshift>")    return PEBLKEY_RSHIFT;

    if(letters == "<rctrl>")    return PEBLKEY_RCTRL;
    if(letters == "<lctrl>")    return PEBLKEY_LCTRL;
    if(letters == "<ralt>")     return PEBLKEY_RALT;
    if(letters == "<lalt>")     return PEBLKEY_LALT;
    if(letters == "<rmeta>")    return PEBLKEY_RMETA;
    if(letters == "<lmeta>")    return PEBLKEY_LMETA;
    if(letters == "<lsuper>")   return PEBLKEY_LSUPER;
    if(letters == "<rsuper>")   return PEBLKEY_RSUPER;
    if(letters == "<mode>")     return PEBLKEY_MODE;
    if(letters == "<compose>")  return PEBLKEY_COMPOSE;






    if(letters == "<kp_0>") return  PEBLKEY_KP0;
    if(letters == "<kp_1>") return  PEBLKEY_KP1;
    if(letters == "<kp_2>") return  PEBLKEY_KP2;
    if(letters == "<kp_3>") return  PEBLKEY_KP3;
    if(letters == "<kp_4>") return  PEBLKEY_KP4;
    if(letters == "<kp_5>") return  PEBLKEY_KP5;
    if(letters == "<kp_6>") return  PEBLKEY_KP6;
    if(letters == "<kp_7>") return  PEBLKEY_KP7;
    if(letters == "<kp_8>") return  PEBLKEY_KP8;
    if(letters == "<kp_9>") return  PEBLKEY_KP9;

    if(letters == "<kp_period>"  ) return  PEBLKEY_KP_PERIOD;
    if(letters == "<kp_divide>"  ) return  PEBLKEY_KP_DIVIDE;
    if(letters == "<kp_multiply>") return  PEBLKEY_KP_MULTIPLY;
    if(letters == "<kp_minus>"   ) return  PEBLKEY_KP_MINUS;
    if(letters == "<kp_plus>"    ) return  PEBLKEY_KP_PLUS;
    if(letters == "<kp_equals>"  ) return  PEBLKEY_KP_EQUALS;
    if(letters == "<kp_enter>"  )  return  PEBLKEY_KP_ENTER;

    if(letters == "<insert>"  ) return  PEBLKEY_INSERT;
    if(letters == "<home>"    ) return  PEBLKEY_HOME;
    if(letters == "<end>"     ) return  PEBLKEY_END;
    if(letters == "<pageup>"  ) return  PEBLKEY_PAGEUP;
    if(letters == "<pagedown>") return  PEBLKEY_PAGEDOWN;



    return PEBLKEY_UNKNOWN;
}



//This returns a text-valued description of the key pressed.
std::string PEBLUtility::TranslateKeyCode(const PEBLKey key, int modkeys)
{



    //    cout << "translating [" << key << "]\n";

    //These are tailored to US keyboard.
    switch(key)
        {

            /* The keyboard syms have been cleverly chosen to map to ASCII */
        case PEBLKEY_UNKNOWN:        return "<unknown>";
            //   case PEBLKEY_FIRST:         return "<>";  //same as above
            //  case PEBLKEY_NOTHING:        return "<nothing>";  //same as above
        case PEBLKEY_ANYKEY:         return "<ANYKEY>";
        case PEBLKEY_BACKSPACE:      return "<backspace>";
        case PEBLKEY_TAB:            return "<tab>";
        case PEBLKEY_CLEAR:          return "<clear>";
        case PEBLKEY_RETURN:         return "<return>";
        case PEBLKEY_PAUSE:          return "<pause>";
        case PEBLKEY_ESCAPE:         return "<esc>";
        case PEBLKEY_SPACE:          return " ";
        case PEBLKEY_EXCLAIM:        return "!";
        case PEBLKEY_QUOTEDBL:       return "\"";
        case PEBLKEY_HASH:           return "#";
        case PEBLKEY_DOLLAR:         return "$";
        case PEBLKEY_AMPERSAND:      return "&";
        case PEBLKEY_QUOTE:         return ShiftSwitch(modkeys,"'" ,"\"");
        case PEBLKEY_LEFTPAREN:      return "(";
        case PEBLKEY_RIGHTPAREN:     return ")";
        case PEBLKEY_ASTERISK:       return "*";
        case PEBLKEY_PLUS:           return "+";
        case PEBLKEY_COMMA:   return ShiftSwitch(modkeys,"," ,"<");
        case PEBLKEY_MINUS:   return ShiftSwitch(modkeys,"-" ,"_");
        case PEBLKEY_PERIOD:  return ShiftSwitch(modkeys,"." ,">");
        case PEBLKEY_SLASH:   return ShiftSwitch(modkeys,"/",  "?");
        case PEBLKEY_0:       return ShiftSwitch(modkeys,"0",  ")");
        case PEBLKEY_1:       return ShiftSwitch(modkeys,"1",  "!");
        case PEBLKEY_2:       return ShiftSwitch(modkeys,"2",  "@");
        case PEBLKEY_3:       return ShiftSwitch(modkeys,"3",  "#");
        case PEBLKEY_4:       return ShiftSwitch(modkeys,"4",  "$");
        case PEBLKEY_5:       return ShiftSwitch(modkeys,"5",  "%");
        case PEBLKEY_6:       return ShiftSwitch(modkeys,"6",  "^");
        case PEBLKEY_7:       return ShiftSwitch(modkeys,"7",  "&");
        case PEBLKEY_8:       return ShiftSwitch(modkeys,"8",  "*");
        case PEBLKEY_9:       return ShiftSwitch(modkeys,"9",  "(");
        case PEBLKEY_COLON:     return ":";
        case PEBLKEY_SEMICOLON:     return ShiftSwitch(modkeys,";", ":");
        case PEBLKEY_LESS:          return "<";
        case PEBLKEY_EQUALS:        return  ShiftSwitch(modkeys,"=",  "+");
        case PEBLKEY_GREATER:       return ">";
        case PEBLKEY_QUESTION:      return "?";
        case PEBLKEY_AT:            return "@";
        /*
           Skip uppercase letters
        */
        case PEBLKEY_LEFTBRACKET:     return  ShiftSwitch(modkeys,"[",  "{");
        case PEBLKEY_BACKSLASH:       return  ShiftSwitch(modkeys,"\\",  "|");
        case PEBLKEY_RIGHTBRACKET:    return  ShiftSwitch(modkeys,"]",  "}");
        case PEBLKEY_CARET:               return "^";
        case PEBLKEY_UNDERSCORE:          return "_";
        case PEBLKEY_BACKQUOTE:           return ShiftSwitch(modkeys,"`","~");
        case PEBLKEY_a:         return ShiftSwitch(modkeys, "a","A");
        case PEBLKEY_b:         return ShiftSwitch(modkeys, "b","B");
        case PEBLKEY_c:         return ShiftSwitch(modkeys, "c","C");
        case PEBLKEY_d:         return ShiftSwitch(modkeys, "d","D");
        case PEBLKEY_e:         return ShiftSwitch(modkeys, "e","E");
        case PEBLKEY_f:         return ShiftSwitch(modkeys, "f","F");
        case PEBLKEY_g:         return ShiftSwitch(modkeys, "g","G");
        case PEBLKEY_h:         return ShiftSwitch(modkeys, "h","H");
        case PEBLKEY_i:         return ShiftSwitch(modkeys, "i","I");
        case PEBLKEY_j:         return ShiftSwitch(modkeys, "j","J");
        case PEBLKEY_k:         return ShiftSwitch(modkeys, "k","K");
        case PEBLKEY_l:         return ShiftSwitch(modkeys, "l","L");
        case PEBLKEY_m:         return ShiftSwitch(modkeys, "m","M");
        case PEBLKEY_n:         return ShiftSwitch(modkeys, "n","N");
        case PEBLKEY_o:         return ShiftSwitch(modkeys, "o","O");
        case PEBLKEY_p:         return ShiftSwitch(modkeys, "p","P");
        case PEBLKEY_q:         return ShiftSwitch(modkeys, "q","Q");
        case PEBLKEY_r:         return ShiftSwitch(modkeys, "r","R");
        case PEBLKEY_s:         return ShiftSwitch(modkeys, "s","S");
        case PEBLKEY_t:         return ShiftSwitch(modkeys, "t","T");
        case PEBLKEY_u:         return ShiftSwitch(modkeys, "u","U");
        case PEBLKEY_v:         return ShiftSwitch(modkeys, "v","V");
        case PEBLKEY_w:         return ShiftSwitch(modkeys, "w","W");
        case PEBLKEY_x:         return ShiftSwitch(modkeys, "x","X");
        case PEBLKEY_y:         return ShiftSwitch(modkeys, "y","Y");
        case PEBLKEY_z:         return ShiftSwitch(modkeys, "z","Z");
        case PEBLKEY_DELETE:         return "<delete>";
            /* End of ASCII mapped keysyms */

            /*Note: WORLD_0 through WORD_64 are currently unverified and most likely incorrect)*/

            /* International keyboard syms */
        case PEBLKEY_WORLD_0:           return " ";  //160
        case PEBLKEY_WORLD_1:           return "¡";
        case PEBLKEY_WORLD_2:           return "¢";
        case PEBLKEY_WORLD_3:           return  "£";
        case PEBLKEY_WORLD_4:           return  "¤";
        case PEBLKEY_WORLD_5:           return  "¥";
        case PEBLKEY_WORLD_6:           return  "¦";
        case PEBLKEY_WORLD_7:           return  "§";
        case PEBLKEY_WORLD_8:           return  "¨";
        case PEBLKEY_WORLD_9:           return  "©";
        case PEBLKEY_WORLD_10:         return "ª";
        case PEBLKEY_WORLD_11:         return "«";
        case PEBLKEY_WORLD_12:         return "¬";
        case PEBLKEY_WORLD_13:         return "­";
        case PEBLKEY_WORLD_14:         return "®";
        case PEBLKEY_WORLD_15:         return "¯";
        case PEBLKEY_WORLD_16:         return "°";
        case PEBLKEY_WORLD_17:         return "±";
        case PEBLKEY_WORLD_18:         return "²";
        case PEBLKEY_WORLD_19:         return "³";
        case PEBLKEY_WORLD_20:         return "´";  //180
        case PEBLKEY_WORLD_21:         return "µ";
        case PEBLKEY_WORLD_22:         return "¶";
        case PEBLKEY_WORLD_23:         return "·";
        case PEBLKEY_WORLD_24:         return "¸";
        case PEBLKEY_WORLD_25:         return "¹";
        case PEBLKEY_WORLD_26:         return "º";
        case PEBLKEY_WORLD_27:         return "»";
        case PEBLKEY_WORLD_28:         return "¼";
        case PEBLKEY_WORLD_29:         return "½";
        case PEBLKEY_WORLD_30:         return "¾";
        case PEBLKEY_WORLD_31:         return "¿";
        case PEBLKEY_WORLD_32:         return "À";
        case PEBLKEY_WORLD_33:         return "Á";
        case PEBLKEY_WORLD_34:         return "Â";
        case PEBLKEY_WORLD_35:         return "Ã";
        case PEBLKEY_WORLD_36:         return "Ä";
        case PEBLKEY_WORLD_37:         return "Å";
        case PEBLKEY_WORLD_38:         return "Æ";
        case PEBLKEY_WORLD_39:         return "Ç";
        case PEBLKEY_WORLD_40:         return "È";  //200
        case PEBLKEY_WORLD_41:         return "É";
        case PEBLKEY_WORLD_42:         return "Ê";
        case PEBLKEY_WORLD_43:         return "Ë";
        case PEBLKEY_WORLD_44:         return "Ì";
        case PEBLKEY_WORLD_45:         return "Í";
        case PEBLKEY_WORLD_46:         return "Î";
        case PEBLKEY_WORLD_47:         return "Ï";
        case PEBLKEY_WORLD_48:         return "Ð";
        case PEBLKEY_WORLD_49:         return "Ñ";
        case PEBLKEY_WORLD_50:         return "Ò";
        case PEBLKEY_WORLD_51:         return "Ó";
        case PEBLKEY_WORLD_52:         return "Ô";
        case PEBLKEY_WORLD_53:         return "Õ";
        case PEBLKEY_WORLD_54:         return "Ö";
        case PEBLKEY_WORLD_55:         return "×";
        case PEBLKEY_WORLD_56:         return "Ø";
        case PEBLKEY_WORLD_57:         return "Ù";
        case PEBLKEY_WORLD_58:         return "Ú";
        case PEBLKEY_WORLD_59:         return "Û";
        case PEBLKEY_WORLD_60:         return "Ü";   //220
        case PEBLKEY_WORLD_61:         return "Ý";
        case PEBLKEY_WORLD_62:         return "Þ";
        case PEBLKEY_WORLD_63:         return "ß";   //223
        case PEBLKEY_WORLD_64:         return ShiftSwitch(modkeys,"à",  "À");
        case PEBLKEY_WORLD_65:         return ShiftSwitch(modkeys,"á",  "Á");
        case PEBLKEY_WORLD_66:         return ShiftSwitch(modkeys,"â",  "Â");
        case PEBLKEY_WORLD_67:         return ShiftSwitch(modkeys,"ã",  "Ã");
        case PEBLKEY_WORLD_68:         return ShiftSwitch(modkeys,"ä",  "Ä");      //228"ä";
        case PEBLKEY_WORLD_69:         return ShiftSwitch(modkeys,"å",  "Å");
        case PEBLKEY_WORLD_70:         return ShiftSwitch(modkeys,"æ",  "Æ");
        case PEBLKEY_WORLD_71:         return ShiftSwitch(modkeys,"ç",  "Ç");
        case PEBLKEY_WORLD_72:         return ShiftSwitch(modkeys,"è",  "È");
        case PEBLKEY_WORLD_73:         return ShiftSwitch(modkeys,"é",  "É");
        case PEBLKEY_WORLD_74:         return ShiftSwitch(modkeys,"ê",  "Ê");
        case PEBLKEY_WORLD_75:         return ShiftSwitch(modkeys,"ë",  "Ë");
        case PEBLKEY_WORLD_76:         return ShiftSwitch(modkeys,"ì",  "Ì");
        case PEBLKEY_WORLD_77:         return ShiftSwitch(modkeys,"í",  "Í");
        case PEBLKEY_WORLD_78:         return ShiftSwitch(modkeys,"î",  "Î");
        case PEBLKEY_WORLD_79:         return ShiftSwitch(modkeys,"ï",  "Ï");
        case PEBLKEY_WORLD_80:         return ShiftSwitch(modkeys,"ð",  "Ð");
        case PEBLKEY_WORLD_81:         return ShiftSwitch(modkeys,"ñ",  "Ñ");
        case PEBLKEY_WORLD_82:         return ShiftSwitch(modkeys,"ò",  "Ò");
        case PEBLKEY_WORLD_83:         return ShiftSwitch(modkeys,"ó",  "Ó");
        case PEBLKEY_WORLD_84:         return ShiftSwitch(modkeys,"ô",  "Ô");
        case PEBLKEY_WORLD_85:         return ShiftSwitch(modkeys,"õ",  "Õ");
        case PEBLKEY_WORLD_86:         return ShiftSwitch(modkeys,"ö",  "Ö");
        case PEBLKEY_WORLD_87:         return ShiftSwitch(modkeys,"÷",  "×");
        case PEBLKEY_WORLD_88:        return ShiftSwitch(modkeys,"ø",  "Ø");
        case PEBLKEY_WORLD_89:        return ShiftSwitch(modkeys,"ù",  "Ù");
        case PEBLKEY_WORLD_90:        return ShiftSwitch(modkeys,"ú",  "Ú"); //250
        case PEBLKEY_WORLD_91:        return ShiftSwitch(modkeys,"û",  "Û");
        case PEBLKEY_WORLD_92:        return ShiftSwitch(modkeys,"ü",  "Ü");
        case PEBLKEY_WORLD_93:        return ShiftSwitch(modkeys,"ý",  "Ý");
        case PEBLKEY_WORLD_94:        return ShiftSwitch(modkeys,"þ",  "Þ");
        case PEBLKEY_WORLD_95:        return ShiftSwitch(modkeys,"ÿ",  "ß");//255
        /* Numeric keypad */
        case PEBLKEY_KP0:         return "0";
        case PEBLKEY_KP1:         return "1";
        case PEBLKEY_KP2:         return "2";
        case PEBLKEY_KP3:         return "3";
        case PEBLKEY_KP4:         return "4";
        case PEBLKEY_KP5:         return "5";
        case PEBLKEY_KP6:         return "6";
        case PEBLKEY_KP7:         return "7";
        case PEBLKEY_KP8:         return "8";
        case PEBLKEY_KP9:         return "9";
        case PEBLKEY_KP_PERIOD:   return ".";
        case PEBLKEY_KP_DIVIDE:   return "/";
        case PEBLKEY_KP_MULTIPLY: return "*";
        case PEBLKEY_KP_MINUS:    return "-";
        case PEBLKEY_KP_PLUS:     return "+";
        case PEBLKEY_KP_ENTER:    return "<kp_enter>";
        case PEBLKEY_KP_EQUALS:   return "=";

        /* Arrows + Home/End pad */
        case PEBLKEY_UP:         return "<up>";
        case PEBLKEY_DOWN:       return "<down>";
        case PEBLKEY_RIGHT:      return "<right>";
        case PEBLKEY_LEFT:       return "<left>";
        case PEBLKEY_INSERT:     return "<insert>";
        case PEBLKEY_HOME:       return "<home>";
        case PEBLKEY_END:        return "<end>";
        case PEBLKEY_PAGEUP:     return "<pageup>";
        case PEBLKEY_PAGEDOWN:   return "<pagedown>";

        /* Function keys */
        case PEBLKEY_F1:         return "<f1>";
        case PEBLKEY_F2:         return "<f2>";
        case PEBLKEY_F3:         return "<f3>";
        case PEBLKEY_F4:         return "<f4>";
        case PEBLKEY_F5:         return "<f5>";
        case PEBLKEY_F6:         return "<f6>";
        case PEBLKEY_F7:         return "<f7>";
        case PEBLKEY_F8:         return "<f8>";
        case PEBLKEY_F9:         return "<f9>";
        case PEBLKEY_F10:         return "<f10>";
        case PEBLKEY_F11:         return "<f11>";
        case PEBLKEY_F12:         return "<f12>";
        case PEBLKEY_F13:         return "<f13>";
        case PEBLKEY_F14:         return "<f14>";
        case PEBLKEY_F15:         return "<f15>";

        /* Key state modifier keys */
        case PEBLKEY_NUMLOCK:      return "<numlock>";
        case PEBLKEY_CAPSLOCK:     return "<capslock>";
        case PEBLKEY_SCROLLOCK:    return "<scrollock>";
        case PEBLKEY_RSHIFT:       return "<rshift>";
        case PEBLKEY_LSHIFT:       return "<lshift>";
        case PEBLKEY_RCTRL:        return "<rctrl>";
        case PEBLKEY_LCTRL:        return "<lctrl>";
        case PEBLKEY_RALT:         return "<ralt>";
        case PEBLKEY_LALT:         return "<lalt>";
        case PEBLKEY_RMETA:        return "<rmeta>";
        case PEBLKEY_LMETA:        return "<lmeta>";
        case PEBLKEY_LSUPER:       return "<lsuper>";
        case PEBLKEY_RSUPER:       return "<rsuper>";
        case PEBLKEY_MODE:         return "<mode>";
        case PEBLKEY_COMPOSE:      return "<compose>";

        /* Miscellaneous function keys */
        case PEBLKEY_HELP:         return "<help>";
        case PEBLKEY_PRINT:        return "<print>";
        case PEBLKEY_SYSREQ:       return "<sysreq>";
        case PEBLKEY_BREAK:        return "<break>";
        case PEBLKEY_MENU:         return "<menu>";
        case PEBLKEY_POWER:        return "<power>";
        case PEBLKEY_EURO:         return "<euro>";
        case PEBLKEY_UNDO:         return "<undo>";

        /* Add any other keys here */
        case PEBLKEY_LAST:         return "<LAST KEY: ERROR>";
        default:            return "<ERROR>";
    };
}


// //This returns a text-valued description of the key pressed.
// std::string PEBLUtility::TranslateKeyCode(const PEBLKey key, int modkeys)
// {
//     switch(key)
//         {
//             /* The keyboard syms have been cleverly chosen to map to ASCII */
//         case PEBLKEY_UNKNOWN:	     return "<unknown>";
//             //   case PEBLKEY_FIRST:	     return "<>";  //same as above
//             //  case PEBLKEY_NOTHING:        return "<nothing>";  //same as above
//         case PEBLKEY_ANYKEY:	     return "<ANYKEY>";
//         case PEBLKEY_BACKSPACE:      return "<backspace>";
//         case PEBLKEY_TAB:            return "<tab>";
//         case PEBLKEY_CLEAR:          return "<clear>";
//         case PEBLKEY_RETURN:         return "<return>";
//         case PEBLKEY_PAUSE:          return "<pause>";
//         case PEBLKEY_ESCAPE:         return "<esc>";
//         case PEBLKEY_SPACE:          return " ";
//         case PEBLKEY_EXCLAIM:        return "!";
//         case PEBLKEY_QUOTEDBL:       return "\"";
//         case PEBLKEY_HASH:           return "#";
//         case PEBLKEY_DOLLAR:         return "$";
//         case PEBLKEY_AMPERSAND:      return "&";
//         case PEBLKEY_QUOTE:          return "'";
//         case PEBLKEY_LEFTPAREN:      return "(";
//         case PEBLKEY_RIGHTPAREN:     return ")";
//         case PEBLKEY_ASTERISK:       return "*";
//         case PEBLKEY_PLUS:           return "+";
//         case PEBLKEY_COMMA:          return ",";
//         case PEBLKEY_MINUS:          return "-";
//         case PEBLKEY_PERIOD:         return ".";
//         case PEBLKEY_SLASH:          return "/";
//         case PEBLKEY_0:         return "0";
//         case PEBLKEY_1:         return "1";
//         case PEBLKEY_2:         return "2";
//         case PEBLKEY_3:         return "3";
//         case PEBLKEY_4:         return "4";
//         case PEBLKEY_5:         return "5";
//         case PEBLKEY_6:         return "6";
//         case PEBLKEY_7:         return "7";
//         case PEBLKEY_8:         return "8";
//         case PEBLKEY_9:         return "9";
//         case PEBLKEY_COLON:         return ":";
//         case PEBLKEY_SEMICOLON:     return ";";
//         case PEBLKEY_LESS:          return "<";
//         case PEBLKEY_EQUALS:        return "=";
//         case PEBLKEY_GREATER:       return ">";
//         case PEBLKEY_QUESTION:      return "?";
//         case PEBLKEY_AT:            return "@";
//         /*
//            Skip uppercase letters
//         */
//         case PEBLKEY_LEFTBRACKET:         return "[";
//         case PEBLKEY_BACKSLASH:           return "\\";
//         case PEBLKEY_RIGHTBRACKET:        return "]";
//         case PEBLKEY_CARET:               return "^";
//         case PEBLKEY_UNDERSCORE:          return "_";
//         case PEBLKEY_BACKQUOTE:           return "`";
//         case PEBLKEY_a:         return ShiftSwitch(modkeys, "a","A");
//         case PEBLKEY_b:         return ShiftSwitch(modkeys, "b","B");
//         case PEBLKEY_c:         return ShiftSwitch(modkeys, "c","C");
//         case PEBLKEY_d:         return ShiftSwitch(modkeys, "d","D");
//         case PEBLKEY_e:         return ShiftSwitch(modkeys, "e","E");
//         case PEBLKEY_f:         return ShiftSwitch(modkeys, "f","F");
//         case PEBLKEY_g:         return ShiftSwitch(modkeys, "g","G");
//         case PEBLKEY_h:         return ShiftSwitch(modkeys, "h","H");
//         case PEBLKEY_i:         return ShiftSwitch(modkeys, "i","I");
//         case PEBLKEY_j:         return ShiftSwitch(modkeys, "j","J");
//         case PEBLKEY_k:         return ShiftSwitch(modkeys, "k","K");
//         case PEBLKEY_l:         return ShiftSwitch(modkeys, "l","L");
//         case PEBLKEY_m:         return ShiftSwitch(modkeys, "m","M");
//         case PEBLKEY_n:         return ShiftSwitch(modkeys, "n","N");
//         case PEBLKEY_o:         return ShiftSwitch(modkeys, "o","O");
//         case PEBLKEY_p:         return ShiftSwitch(modkeys, "p","P");
//         case PEBLKEY_q:         return ShiftSwitch(modkeys, "q","Q");
//         case PEBLKEY_r:         return ShiftSwitch(modkeys, "r","R");
//         case PEBLKEY_s:         return ShiftSwitch(modkeys, "s","S");
//         case PEBLKEY_t:         return ShiftSwitch(modkeys, "t","T");
//         case PEBLKEY_u:         return ShiftSwitch(modkeys, "u","U");
//         case PEBLKEY_v:         return ShiftSwitch(modkeys, "v","V");
//         case PEBLKEY_w:         return ShiftSwitch(modkeys, "w","W");
//         case PEBLKEY_x:         return ShiftSwitch(modkeys, "x","X");
//         case PEBLKEY_y:         return ShiftSwitch(modkeys, "y","Y");
//         case PEBLKEY_z:         return ShiftSwitch(modkeys, "z","Z");
//         case PEBLKEY_DELETE:         return "<delete>";
//         /* End of ASCII mapped keysyms */

//         /* International keyboard syms */
//         case PEBLKEY_WORLD_0:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_1:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_2:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_3:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_4:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_5:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_6:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_7:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_8:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_9:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_10:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_11:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_12:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_13:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_14:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_15:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_16:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_17:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_18:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_19:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_20:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_21:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_22:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_23:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_24:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_25:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_26:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_27:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_28:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_29:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_30:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_31:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_32:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_33:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_34:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_35:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_36:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_37:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_38:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_39:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_40:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_41:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_42:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_43:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_44:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_45:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_46:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_47:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_48:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_49:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_50:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_51:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_52:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_53:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_54:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_55:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_56:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_57:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_58:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_59:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_60:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_61:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_62:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_63:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_64:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_65:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_66:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_67:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_68:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_69:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_70:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_71:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_72:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_73:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_74:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_75:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_76:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_77:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_78:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_79:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_80:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_81:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_82:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_83:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_84:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_85:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_86:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_87:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_88:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_89:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_90:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_91:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_92:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_93:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_94:         return "<PEBL WORLD KEY>";
//         case PEBLKEY_WORLD_95:         return "<PEBL WORLD KEY>";
//         /* Numeric keypad */
//         case PEBLKEY_KP0:         return "0";
//         case PEBLKEY_KP1:         return "1";
//         case PEBLKEY_KP2:         return "2";
//         case PEBLKEY_KP3:         return "3";
//         case PEBLKEY_KP4:         return "4";
//         case PEBLKEY_KP5:         return "5";
//         case PEBLKEY_KP6:         return "6";
//         case PEBLKEY_KP7:         return "7";
//         case PEBLKEY_KP8:         return "8";
//         case PEBLKEY_KP9:         return "9";
//         case PEBLKEY_KP_PERIOD:   return ".";
//         case PEBLKEY_KP_DIVIDE:   return "/";
//         case PEBLKEY_KP_MULTIPLY: return "*";
//         case PEBLKEY_KP_MINUS:    return "-";
//         case PEBLKEY_KP_PLUS:     return "+";
//         case PEBLKEY_KP_ENTER:    return "<kp_enter>";
//         case PEBLKEY_KP_EQUALS:   return "=";

//         /* Arrows + Home/End pad */
//         case PEBLKEY_UP:         return "<up>";
//         case PEBLKEY_DOWN:       return "<down>";
//         case PEBLKEY_RIGHT:      return "<right>";
//         case PEBLKEY_LEFT:       return "<left>";
//         case PEBLKEY_INSERT:     return "<insert>";
//         case PEBLKEY_HOME:       return "<home>";
//         case PEBLKEY_END:        return "<end>";
//         case PEBLKEY_PAGEUP:     return "<pageup>";
//         case PEBLKEY_PAGEDOWN:   return "<pagedown>";

//         /* Function keys */
//         case PEBLKEY_F1:         return "<F1>";
//         case PEBLKEY_F2:         return "<F2>";
//         case PEBLKEY_F3:         return "<F3>";
//         case PEBLKEY_F4:         return "<F4>";
//         case PEBLKEY_F5:         return "<F5>";
//         case PEBLKEY_F6:         return "<F6>";
//         case PEBLKEY_F7:         return "<F7>";
//         case PEBLKEY_F8:         return "<F8>";
//         case PEBLKEY_F9:         return "<F9>";
//         case PEBLKEY_F10:         return "<F10>";
//         case PEBLKEY_F11:         return "<F11>";
//         case PEBLKEY_F12:         return "<F12>";
//         case PEBLKEY_F13:         return "<F13>";
//         case PEBLKEY_F14:         return "<F14>";
//         case PEBLKEY_F15:         return "<F15>";

//         /* Key state modifier keys */
//         case PEBLKEY_NUMLOCK:      return "<numlock>";
//         case PEBLKEY_CAPSLOCK:     return "<capslock>";
//         case PEBLKEY_SCROLLOCK:    return "<scrollock>";
//         case PEBLKEY_RSHIFT:       return "<rshift>";
//         case PEBLKEY_LSHIFT:       return "<lshift>";
//         case PEBLKEY_RCTRL:        return "<rctrl>";
//         case PEBLKEY_LCTRL:        return "<lctrl>";
//         case PEBLKEY_RALT:         return "<ralt>";
//         case PEBLKEY_LALT:         return "<lalt>";
//         case PEBLKEY_RMETA:        return "<rmeta>";
//         case PEBLKEY_LMETA:        return "<lmeta>";
//         case PEBLKEY_LSUPER:       return "<lsuper>";
//         case PEBLKEY_RSUPER:       return "<rsuper>";
//         case PEBLKEY_MODE:         return "<mode>";
//         case PEBLKEY_COMPOSE:      return "<compose>";

//         /* Miscellaneous function keys */
//         case PEBLKEY_HELP:         return "<help>";
//         case PEBLKEY_PRINT:        return "<print>";
//         case PEBLKEY_SYSREQ:       return "<sysreq>";
//         case PEBLKEY_BREAK:        return "<break>";
//         case PEBLKEY_MENU:         return "<menu>";
//         case PEBLKEY_POWER:        return "<power>";
//         case PEBLKEY_EURO:         return "<euro>";
//         case PEBLKEY_UNDO:         return "<undo>";

//         /* Add any other keys here */
//         case PEBLKEY_LAST:         return "<LAST KEY: ERROR>";
//         default:                   return "<ERROR>";
//     };
// }




PEBLVideoMode PEBLUtility::GetVideoMode(std::string modeline)
{

	PEBLVideoMode mode;

	if(modeline ==        "512x384") mode =PVM_512_384;
	else if (modeline ==  "640x480") mode =	PVM_640_480;
	else if (modeline ==  "800x600")	mode =	PVM_800_600;
	else if (modeline ==	"960x720")	mode =	PVM_960_720;
	else if (modeline ==	"1024x768")	mode =	PVM_1024_768;
	else if (modeline ==	"1152x864")	mode =	PVM_1152_864;
	else if (modeline ==	"1280x1024") mode =	PVM_1280_1024;
	else mode  = PVM_800_600;
	return mode;
}


PEBLVideoDepth PEBLUtility::GetVideoDepth(std::string depthline)
{
	PEBLVideoDepth depth;

	if(depthline == "2")       depth =PVD_2;
	else if (depthline =="15") depth =PVD_15;
	else if (depthline =="16") depth =PVD_16;
	else if (depthline =="24") depth =PVD_24;
	else if (depthline =="32") depth =PVD_32;
	else depth  = PVD_16;

	return depth;
}



//This returns upper if a shift key is pressed, otherwise it returns lower.
std::string PEBLUtility::ShiftSwitch(int modkeys, std::string lower, std::string upper)
{
    if( modkeys & PEBLMOD_SHIFT)
        return upper;
    else
        return lower;
}


Variant PEBLUtility::IsDirectory(std::string path)
{
    DIR *dirp;
    //struct dirent *entry;
    dirp = opendir(path.c_str());


    if(dirp)
        {

			closedir(dirp);
            return Variant(1);
        }
    else
        {
				//closedir(dirp);
            //std::cerr << "Error type: " <<errno << std::endl;
            return Variant(0);
        }
    //entry->d_type;



}

Variant PEBLUtility::FileExists(std::string path)
{

    struct stat stFileInfo;
    //may need to use _stat on windows
    int out = stat(path.c_str(),&stFileInfo);
    //cout << path.c_str()<<"\n";
    //cout << "File info:" << out << endl;
    //  We can get better info about the file
    //  if we look at out.
    return Variant(out==0);
}





Variant PEBLUtility::GetDirectoryListing(std::string path)
{

    //cout << "Getting directory listing\n";
    DIR *dirp;
    struct dirent *entry;
    PList * plist = new PList();
    PComplexData*pcd=NULL;

    dirp = opendir(path.c_str());
    if(dirp)
        {

            //not this is an assignment, not an equality
            while((entry = readdir(dirp)))
                {
                    //cout << entry->d_name << endl;
                    plist->PushBack(Variant(entry->d_name));
                }
        } else {
//ERRNO CODES:
//			EACCES

//				EMFILE
//
//				ENFILE
//				The entire system, or perhaps the file system which contains the directory, cannot support any additional open files at the moment. (This problem cannot happen on the GNU system.)
//				ENOMEM
//				Not enough memory available.

		    Variant codes = "";
			switch (errno) {
				case EACCES:
						codes = "Read permission is denied for the directory named by dirname.(EACCES)";
					break;

			case EMFILE:
					codes = "The process has too many files open (EMFILE).";
					break;
				case ENFILE:
					codes = "The entire system, or perhaps the file system which contains the directory, cannot support any additional open files at the moment. (ENFILE)";
					break;
				case ENOMEM:
					codes = "Not enough memory available. (ENOMEM)";
					break;
				default:
					codes =Variant("Unknown error") + Variant(errno);
					break;
			}

			PError::SignalFatalError(Variant("Unable to get Directory listing at ") + Variant(path) + codes);

		}


        closedir(dirp);

        counted_ptr<PEBLObjectBase> tmplist = counted_ptr<PEBLObjectBase>(plist);
        pcd = new PComplexData(tmplist);
        Variant tmp = Variant(pcd);
        delete pcd;
        return tmp;
}



Variant PEBLUtility::MakeDirectory(std::string path)

{

    if(FileExists(path) && IsDirectory(path))
        {
            return Variant(1);
          }

#ifdef PEBL_UNIX

    if (mkdir(path.c_str(), 0777) == -1)
       {
           PError::SignalFatalError("Unable to create directory: " );//+ Variant(strerror(errno)));
       }

#elif defined(PEBL_WIN32)
    if (mkdir(path.c_str()) == -1)
        {
            //cerr << strerror(errno)<<endl;
            PError::SignalFatalError("Unable to create directory: " + Variant(strerror(errno)));
        }

#endif

    return Variant(1);
}

Variant PEBLUtility::DeleteMyFile(std::string path)
{
   if(FileExists(path))
    {
     if( remove( path.c_str() ) != 0 )
          return Variant(0);
     else
          return Variant(1);
    }
	return Variant(0);

}

Variant PEBLUtility::GetHomeDirectory()
{

#ifdef PEBL_WIN32
  char path[ MAX_PATH ];
  if (SHGetFolderPathA( NULL, CSIDL_PROFILE, NULL, 0, path ) != S_OK)
    {
        PError::SignalFatalError("Unable to find user's home directory!");
    }
#elif defined(PEBL_LINUX) or defined(PEBL_OSX)

  struct passwd *p=getpwuid(getuid());
  std::string path = p->pw_dir;
#elif defined( PEBL_EMSCRIPTEN)

  //this may be wrong?
  std::string path ="~/";

#endif

  return Variant(path);
}

Variant PEBLUtility::GetWorkingDirectory()
{
#if defined(PEBL_WIN32) or  defined(PEBL_OSX)
    //maybe this will work given we compile with g++

    char *path=NULL;
    size_t size = 0;
    path=getcwd(path,size);


#elif defined(PEBL_UNIX) //linux/osx

    char* path = get_current_dir_name();

#elif defined (PEBL_EMSCRIPTEN)
    const char* path = ""; //maybe this won't work
#endif

 return Variant(path);
}

Variant PEBLUtility::SetWorkingDirectory(std::string path)
{
#ifdef PEBL_WIN32

    if(::SetCurrentDirectory(path.c_str()) == FALSE)
        PError::SignalFatalError("Unable to Set Working Directory: " + path);
    //GetLastError should help more here.
#else
    int result = chdir(path.c_str());
   if(result != 0)
        {
            PError::SignalFatalError("Unable to Set Working Directory: " + path);
        }
#endif

 return Variant(true);
}



Variant PEBLUtility::LaunchFile(std::string file)
{

    int x;
    //cout << "Running launchfile\n";
#if defined(PEBL_WIN32)
    HINSTANCE hInst = ShellExecute(0,
                                   "open",                      // Operation to perform
                                   file.c_str(),                // document name???Application name
                                   NULL,                        // Additional parameters
                                   0,                           // Default directory
                                   SW_SHOW);
    //cout<< "LaunchFile:{" << file <<"}{"<< hInst << endl;

   if ((int)hInst == SE_ERR_NOASSOC ||
       (int)hInst == SE_ERR_ASSOCINCOMPLETE ||
       (int)hInst == SE_ERR_ACCESSDENIED)
    {
      SHELLEXECUTEINFO exeInfo = {0};
      exeInfo.cbSize = sizeof(SHELLEXECUTEINFO);
      exeInfo.lpVerb = "openas";
      exeInfo.lpFile = file.c_str();
      exeInfo.fMask = SEE_MASK_INVOKEIDLIST;
      exeInfo.nShow = SW_SHOWDEFAULT;

      // Open up the open as window
      if (ShellExecuteEx(&exeInfo) == FALSE);
      {
        x = false ;
      }
    } else {

       x = ((int)hInst > 32);  //hInst returns an error code > 32 on success.
     }
#elif defined(PEBL_LINUX)


    std::string call2 = "gnome-open " + file;
    int ret = system(call2.c_str());  //do a system call with the argument string.
    x = !ret;



#elif defined(PEBL_OSX)
     std::string call2 = "open " + file;
     int ret  = system(call2.c_str());  //do a s string.
     x = !ret;
#endif

 return Variant(x);
}


Variant PEBLUtility::SystemCall(std::string call, std::string args)
{
    //   cout << "Systemcalling inner\n";


#if defined( PEBL_UNIX )

    std::string tmp = call + " " + args;

    const char* call2 = tmp.c_str();
    int x = system(call2);  //do a system call with the argument string.

#elif defined (PEBL_WIN32)
    std::string tmp = "cmd.exe /c " + call + " " + args;

    //   cout << "["<<tmp <<"]"<< std::endl;
    STARTUPINFO info={sizeof(info)};
    PROCESS_INFORMATION processInfo;
    char* callstring = const_cast<char *>(tmp.c_str());
    if (CreateProcess(NULL,callstring, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
        {
            ::WaitForSingleObject(processInfo.hProcess, INFINITE);
            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);
        } else {
        //        cout << "createprocess failed\n";
        std::cerr << GetLastError() << std::endl;
    }
    int x=0;
#elif defined (PEBL_EMSCRIPTEN)
    std::cerr << "Cannot perform system call in web mode\n";
    int x = 0;
#endif

    return Variant(x);

}


// unicode revers functions adapted from
// http://stackoverflow.com/questions/198199/how-do-you-reverse-a-string-in-place-in-c-or-c
//

#define SWP(x,y) (x^=y, y^=x, x^=y)

void PEBLUtility::strrev(char *p)
{
  char *q = p;
  while(q && *q) ++q; /* find eos */
  for(--q; p < q; ++p, --q) SWP(*p, *q);
}


void PEBLUtility::strrev_utf8(char *p)
{
  char *q = p;
  strrev(p); /* call base case */

  /* Ok, now fix bass-ackwards UTF chars. */
  while(q && *q) ++q; /* find eos */
  while(p < --q)
    switch( (*q & 0xF0) >> 4 ) {
    case 0xF: /* U+010000-U+10FFFF: four bytes. */
      SWP(*(q-0), *(q-3));
      SWP(*(q-1), *(q-2));
      q -= 3;
      break;
    case 0xE: /* U+000800-U+00FFFF: three bytes. */
      SWP(*(q-0), *(q-2));
      q -= 2;
      break;
    case 0xC: /* fall-through */
    case 0xD: /* U+000080-U+0007FF: two bytes. */
      SWP(*(q-0), *(q-1));
      q--;
      break;
    }
}
std::string PEBLUtility::strrev(std::string p)
{

    std::string q = std::string(p);
    std::reverse(q.begin(),q.end());
    return q;
}

std::string PEBLUtility::strrev_utf8(std::string p)
{


    std::wstring q(p.length(), L' '); // Make room for characters
    // Copy string to wstring.
    std::copy(p.begin(), p.end(), q.begin());

    // reverse:
    std::reverse(q.begin(),q.end());

    cout << "[";
    std::wstring::iterator i;

    for(i = q.begin();i<=q.end();i++)
        {
            cout << *i << "|";
        }
    cout << "]\n";

    std::string ns(q.begin(), q.end());
    cout << ns << std::endl;
    return ns;


//     std::string::iterator qq = q.end();

//   /* Ok, now fix backwards UTF chars. */

//         while(qq >= q.begin())
//             {

//                 switch( (*qq & 0xF0) >> 4 )
//                     {

//                     case 0xF: /* U+010000-U+10FFFF: four bytes. */
//                         std::swap(*qq,*(qq-3));
//                         std::swap(*(qq-1),*(qq-2));
//                         //q.replace(qq,qq-3,q,1);
//                         //q.replace(qq-1,qq-2,q,1);
//                         qq -= 3;
//                         break;

//                     case 0xE: /* U+000800-U+00FFFF: three bytes. */
//                         std::swap(*qq,*(qq-2));
//                         //q.replace(qq,qq-2,q,1);
//                         qq -= 2;
//                         break;

//                     case 0xC: /* fall-through */
//                     case 0xD: /* U+000080-U+0007FF: two bytes. */
//                         std::swap(*qq,*(qq-1));
//                         //q.replace(qq,qq-1,q,1);
//                         qq--;
//                         break;
//                     default:
//                         qq--;
//                     }
//             }
//     return q;
}

// Get the size of the file by its file descriptor
unsigned long get_size_by_fd(int fd) {
    struct stat statbuf;
    if(fstat(fd, &statbuf) < 0) exit(-1);
    return statbuf.st_size;
}

std::string PEBLUtility::MD5File(const std::string & filename)
{

    if(FileExists(filename))
        {

            int file_descript;
            unsigned long file_size;
            char* file_buffer;

            //printf("using file:\t%s\n", filename);

            file_descript = open(filename.c_str(), O_RDONLY);
            if(file_descript < 0)
                {
                    PError::SignalFatalError("File does not exist in MD5file\n");
                    return "";
                }

            file_size = get_size_by_fd(file_descript);
            //printf("file size:\t%lu\n", file_size);

            file_buffer = (char*)mmap(0, file_size, PROT_READ, MAP_SHARED,
                               file_descript, 0);


            MD5 *md5 = new MD5();
            md5->update((unsigned char*)file_buffer,file_size);
            //std::string result =  md5((unsigned char*) file_buffer);
            md5->finalize();
            std::string hex = md5->hexdigest();
            delete md5;
            md5=NULL;
            return hex;
        }else{

        return "0";
    }

}


std::string PEBLUtility::MD5String(const std::string & text)
{
    return md5(text);
}


void PEBLUtility::CopyToClipboard(const std::string & text)
{

}
