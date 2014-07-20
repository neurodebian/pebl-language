//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/SDLUtility.h
//    Purpose:    Contains miscellaneous utility functions.
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

#include "SDLUtility.h"
#include "../../objects/PColor.h"
#include "../../utility/PError.h"
#include "../../base/PList.h"
#include "../../base/PComplexData.h"
#include "PlatformWindow.h"
#include "SDL/SDL.h"
#if !defined(PEBL_OSX)
#include <png.h>
#endif
#include <math.h>
#include <iostream>
using std::cout;
using std::flush;
using std::endl;

/// These are SDL-specific utilities that don't fit into a single class very well.


SDL_Color  SDLUtility::PColorToSDLColor(PColor pcolor)
{
  SDL_Color scolor;
  scolor.r = pcolor.GetRed();
  scolor.g = pcolor.GetGreen();
  scolor.b = pcolor.GetBlue();
  scolor.unused = pcolor.GetAlpha();

  return scolor;
}

PColor SDLUtility::SDLColorToPColor(SDL_Color scolor)
{

  return PColor(scolor.r, scolor.g, scolor.b, scolor.unused);
}




///  This sets a pixel to be a certain color.
void SDLUtility::DrawPixel(SDL_Surface *surface, int x, int y, PColor pcolor)
{

    SDL_Color sdlcolor = PColorToSDLColor(pcolor);
    Uint32 pixel = SDL_MapRGBA(surface->format,
                               pcolor.GetRed(), pcolor.GetGreen(),
                               pcolor.GetBlue(), pcolor.GetAlpha());

    //Only draw the pixel if it is actually in the surface.
    if(x < 0
       || x >= surface->w
       || y < 0
       || y >= surface->h)
        {
            //cout << "outside: "<< x<< " " << y << endl;
            return;
        }

    //cout << "inside: "<< x << " " << y << " " << surface->w << " " << surface->h << endl;

    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }

}

///  This sets a pixel to be a certain color.
void SDLUtility::DrawLine(SDL_Surface *surface, int x1, int y1, int x2, int y2, PColor pcolor)
{
    //Draw a pixel on every point between (x1,y1) and (x2,y2)

    //We need a rough estimate of the number of steps to take.

    int length = (int)(sqrt((double)(x1-x2) * (x1 - x2) + (y1-y2)*(y1-y2)) * 2);

    //Draw twice for each intermediate pixel.
    float deltax = (float)(x2 - x1) / length;
    float deltay = (float)(y2 - y1) / length;


    for(int i = 0; i < length; i++)
        {
            DrawPixel( surface, (int)(x1 + deltax * i), (int)( y1 +deltay*i), pcolor);
        }

    //Draw the end pixel just for kicks.
    DrawPixel(surface, x2, y2, pcolor);

}

///  This sets a pixel to be a certain color.
void SDLUtility::DrawSmoothLine(SDL_Surface *surface, int x1, int y1, int x2, int y2, PColor pcolor)
{
    //Draw a pixel on every point between (x1,y1) and (x2,y2)

    DrawLine(surface, x1, y1, x2, y2, pcolor);


}


/*
     * Return the pixel value at (x, y)
     * NOTE: The surface must be locked before calling this!
     */
Uint32 SDLUtility::GetPixel(SDL_Surface *surface, int x, int y)
    {
        int bpp = surface->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

       switch (bpp) {
       case 1:
           return *p;

       case 2:
           return *(Uint16 *)p;

       case 3:
           if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
               return p[0] << 16 | p[1] << 8 | p[2];
           else
               return p[0] | p[1] << 8 | p[2] << 16;

       case 4:
           return *(Uint32 *)p;

     default:
         return 0;       /* shouldn't happen, but avoids warnings */
     } // switch
 }


/// This extracts the color of a pixel.
PColor SDLUtility::GetPixelColor(SDL_Surface *surface, int x, int y)
{
    Uint32 pxl =GetPixel(surface,x,y);
    Uint8 r;
    Uint8 g;
    Uint8 b;

    SDL_GetRGB(pxl, surface->format, &r,&g,&b);

    //    cout <<"Uint pxl:" << pxl << endl;
    PColor col = PColor(r,g,b,0);
    return col;
}



int SDLUtility::WritePNG(const Variant fname, PlatformWidget* wid)
{
#if ! defined(PEBL_OSX)
    SDL_Surface * surf = wid->GetSDL_Surface();


     //Make and save a png out of a surface
    png_structp png_ptr;
    png_infop info_ptr;
    png_text text_ptr[4];
    unsigned char **png_rows;
    Uint8 r, g, b;
    int x, y, count;
    //     Uint32(*getpixel) (SDL_Surface *, int, int) = getpixels[surf->format->BytesPerPixel];


    FILE* fi = fopen(fname.GetString().c_str(),"wb");
    if (!fi)
      {
         std::cerr << "[WritePng] file ["<< fname << "]  could not be opened for writing\n";
         return 0;
      }


     png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
     //png_create_write_struct could fail, for whatever reason.
     if (png_ptr == NULL)
         {
            std::cerr << "[WritePng] failed to create PNG struct\n";

             fclose(fi);
             png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
             return 0;

         }
     else
         {
             //same deal for png_create_info_struct
             info_ptr = png_create_info_struct(png_ptr);
             if (info_ptr == NULL)
                 {
                     fclose(fi);
                     png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
                     return 0;
                 }
            else
                {
                    //Nothing failed so far.
                    if (setjmp(png_jmpbuf(png_ptr)))
                        {
                            fclose(fi);
                            png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
                            return 0;
                        }
                    else
                        {

                            //Everything has succedded so far.
                            //Initialize
                            png_init_io(png_ptr, fi);

                            info_ptr->width = surf->w;
                            info_ptr->height = surf->h;
                            info_ptr->bit_depth = 8;
                            info_ptr->color_type = PNG_COLOR_TYPE_RGB;
                            info_ptr->interlace_type = 1;
                            info_ptr->valid = 0;	// will be updated by various png_set_FOO() functions

                            png_set_sRGB_gAMA_and_cHRM(png_ptr, info_ptr,
                                                       PNG_sRGB_INTENT_PERCEPTUAL);

                            /* Set headers */

                            count = 0;

                            /*
                              if (title != NULL && strlen(title) > 0)
                              {
                              text_ptr[count].key = "Title";
                              text_ptr[count].text = title;
                              text_ptr[count].compression = PNG_TEXT_COMPRESSION_NONE;
                              count++;
                              }
                            */

                            text_ptr[count].key = (png_charp) "Software";
                            text_ptr[count].text =  (png_charp) "PEBL ";
                            text_ptr[count].compression = PNG_TEXT_COMPRESSION_NONE;
                            count++;


                            png_set_text(png_ptr, info_ptr, text_ptr, count);

                            png_write_info(png_ptr, info_ptr);



                            /* Save the picture: */

                            png_rows = (unsigned char**)malloc(sizeof(char *)* surf->h);

                            for (y = 0; y < surf->h; y++)
                                {
                                    png_rows[y] = (unsigned char*)malloc(sizeof(char) * 3 * surf->w);

                                    for (x = 0; x < surf->w; x++)
                                        {

                                            SDL_GetRGB(GetPixel(surf, x, y), surf->format, &r, &g, &b);

                                            png_rows[y][x * 3 + 0] = r;
                                            png_rows[y][x * 3 + 1] = g;
                                            png_rows[y][x * 3 + 2] = b;
                                        }
                                }

                            png_write_image(png_ptr, png_rows);

                            for (y = 0; y < surf->h; y++)
                                free(png_rows[y]);

                            free(png_rows);


                            png_write_end(png_ptr, NULL);

                            png_destroy_write_struct(&png_ptr, &info_ptr);
                            fclose(fi);

                            return 1;
                        }
                }
        }
#endif
    return 0;

}

Variant SDLUtility::GetCurrentScreenResolution()
{

    const SDL_VideoInfo * info = SDL_GetVideoInfo();

    int w,h;

    if(info)
        {
            w = info->current_w;
            h = info->current_h;

        }else
        {
            w = 0;
            h = 0;
        }

    PList * newlist = new PList();
    newlist->PushBack(Variant(w));
    newlist->PushBack(Variant(h));

    counted_ptr<PEBLObjectBase> newlist2 = counted_ptr<PEBLObjectBase>(newlist);
    PComplexData * pcd=new PComplexData(newlist2);
    return Variant(pcd);

}


void SDLUtility::CopyToClipboard(std::string text)
{
    //Not available in SDL 1.2
}
