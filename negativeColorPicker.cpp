/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  img = inputimg;
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  HSLAPixel ret;
  HSLAPixel* pixPtr = img.getPixel(p.x, p.y);
  ret.a = pixPtr->a;
  ret.s = pixPtr->s;
  if(fmod((pixPtr->h + 180.0), 360) == 360){
     ret.h = 0;
  }else {
    ret.h =  fmod((pixPtr->h + 180.0), 360);
  }
  //(p.color.h + 180.0) % 360;
  ret.l = (1.0 - pixPtr->l);

  return ret; 
}
