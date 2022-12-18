/*
 *  File: censorColorPicker.cpp
 *  Implements the censor color picker for CPSC 221 PA2.
 *
 */

#include "censorColorPicker.h"

#include <math.h> // gives access to sqrt function

/*
 *  Useful function for computing the Euclidean distance between two PixelPoints
 */
double PointDistance(PixelPoint a, PixelPoint b)
{
  unsigned int diff_x, diff_y;
  if (a.x > b.x)
    diff_x = a.x - b.x;
  else
    diff_x = b.x - a.x;
  if (a.y > b.y)
    diff_y = a.y - b.y;
  else
    diff_y = b.y - a.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

CensorColorPicker::CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG &inputimage)
{
  blockwidth = b_width;
  center = ctr;
  radius = rad;
  img = inputimage;
  blockyimg = PNG(inputimage.width(), inputimage.height()); // not sure about this

  // One to calculate how much it would be for the average
  double aCount = 0;
  double sCount = 0;
  double hCount = 0;
  double lCount = 0;
  int pixCount = 0;
  // for (unsigned int y = 0; y < img.height(); y++)
  // {
  //   for (unsigned int x = 0; x < img.width(); x++)
  //   {
  //     if (x % b_width == 0 && y % b_width == 0)
  //     {
  //       if (x == 0 && y == 0)
  //       {
  //         HSLAPixel *blockPtr = blockyimg.getPixel(x, y);
  //         HSLAPixel *pixPtr = img.getPixel(x, y);
  //         blockPtr->a = pixPtr->a;
  //         blockPtr->h = pixPtr->h;
  //         blockPtr->s = pixPtr->s;
  //         blockPtr->l = pixPtr->l;
  //       }
  //       // we would run that for loop here!
  //     }
  //     else
  //     {
  //       // This allows us to calculate the average
  //       HSLAPixel *pixPtr = img.getPixel(x, y);
  //       aCount += pixPtr->a;
  //       sCount += pixPtr->s;
  //       hCount += pixPtr->h;
  //       lCount += pixPtr->l;

  //       // If we are not at the position fill it with this value for edge cases
  //       HSLAPixel *blockPtr = blockyimg.getPixel(x, y);
  //       blockPtr->a = pixPtr->a;
  //       blockPtr->h = pixPtr->h;
  //       blockPtr->s = pixPtr->s;
  //       blockPtr->l = pixPtr->l;

  //       // Adds to total pixal count so we can divide from it
  //       pixCount++;
  //     }
  //   }
  // }

  for (unsigned int y = 0; y < img.height(); y = y + blockwidth)
  {
    for (unsigned int x = 0; x < img.width(); x = x + blockwidth)
    {
      aCount = 0;
      sCount = 0;
      hCount = 0;
      lCount = 0;
      pixCount = 0;
      // Counting for the average
      for (unsigned int i = y; i < y + blockwidth; i++)
      {
        for (unsigned int j = x; j < x + blockwidth; j++)
        {
          if (i < img.height() && j < img.width())
          {
            HSLAPixel *pixPtr = img.getPixel(j,i);
            aCount += pixPtr->a;
            sCount += pixPtr->s;
            hCount += pixPtr->h;
            lCount += pixPtr->l;
            pixCount++;
          }
          else
          {
            HSLAPixel *blockPtr = blockyimg.getPixel(j,i);
            HSLAPixel *pixPtr = img.getPixel(j,i);
            blockPtr->a = pixPtr->a;
            blockPtr->h = pixPtr->h;
            blockPtr->s = pixPtr->s;
            blockPtr->l = pixPtr->l;
          }
        }
      }

      // Changing Color
      for (unsigned int i = y; i < y + blockwidth; i++)
      {
        for (unsigned int j = x; j < x + blockwidth; j++)
        {
          if (i < img.height() && j < img.width() && (((j - center.x)*(j - center.x)) + ((i - center.y)*(i - center.y)) <= radius*radius))
          {
            HSLAPixel *blockPtr = blockyimg.getPixel(j,i);
            blockPtr->a = aCount / pixCount;
            blockPtr->h = hCount / pixCount;
            blockPtr->s = sCount / pixCount;
            blockPtr->l = lCount / pixCount;
          }
          else
          {
            HSLAPixel *blockPtr = blockyimg.getPixel(j,i);
            HSLAPixel *pixPtr = img.getPixel(j,i);
            blockPtr->a = pixPtr->a;
            blockPtr->h = pixPtr->h;
            blockPtr->s = pixPtr->s;
            blockPtr->l = pixPtr->l;
          }
        }
      }
    }
  }
  // One to assign the new colors
}

HSLAPixel CensorColorPicker::operator()(PixelPoint p)
{
  HSLAPixel ret;
  unsigned int pointX = p.x;
  unsigned int pointY = p.y;

  //fr (for real)
  if (((pointX - center.x)*(pointX - center.x)) + ((pointY - center.y)*(pointY - center.y)) <= radius*radius)
  {
    HSLAPixel *pixPtr = blockyimg.getPixel(pointX, pointY);
    ret.a = pixPtr->a;
    ret.s = pixPtr->s;
    ret.h = pixPtr->h;
    ret.l = pixPtr->l;
  }
  else
  {
    HSLAPixel *pixPtr = img.getPixel(pointX, pointY);
    ret.a = pixPtr->a;
    ret.s = pixPtr->s;
    ret.h = pixPtr->h;
    ret.l = pixPtr->l;
  }
  // Check if this point is within the circular region on the image!

  return ret;
}
