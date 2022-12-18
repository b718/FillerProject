/*
 *  File: imageTileColorPicker.cpp
 *  Implements the image tile color picker for CPSC 221 PA2.
 *
 */

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG &otherimage)
{
  img_other = otherimage;
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p)
{
  HSLAPixel ret;
  unsigned int posX = p.x;
  unsigned int posY = p.y;

  HSLAPixel *holder = img_other.getPixel(posX % img_other.width(), posY % img_other.height());
  ret.a = holder->a;
  ret.h = holder->h;
  ret.l = holder->l;
  ret.s = holder->s;

  return ret;
}