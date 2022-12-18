/*
 * File:        priority.cpp
 * Description: Implements a priority ordering structure specially made for determining the
 *              order of neighbours visited in PA2's filler::fill function.
 *              Note that this does NOT serve the same purpose as the stack/queue
 *              ordering structure which you have also been asked to implement.
 *
 *              Ignoring resize costs, any single insertion or removal operation
 *              should cost at most O(n), where n is the number of PixelPoints
 *              stored in the collection.
 *
 * Date:        2022-02-10 02:04
 *
 */

#include "priority.h"
#include <assert.h>

using namespace cs221util;
using namespace std;

/*
 *  Default constructor
 *  Initializes refcolor to the default color according to the HSLAPixel implementation.
 */
PriorityNeighbours::PriorityNeighbours()
{
  refcolor.h = 0;
  refcolor.s = 0;
  refcolor.l = 1.0;
  refcolor.a = 1.0;
}

/*
 *  Parameterized constructor
 *  Initializes refcolor to the supplied value.
 */
PriorityNeighbours::PriorityNeighbours(HSLAPixel ref)
{
  refcolor.h = ref.h;
  refcolor.s = ref.s;
  refcolor.l = ref.l;
  refcolor.a = ref.a;
}

/*
 *  Inserts an item into the collection
 *  PARAM: p - item to be inserted
 *  POST:  the collection contains p, along with all previously existing items.
 */
void PriorityNeighbours::Insert(PixelPoint p)
{
  points.push_back(p);
}

/*
 *  Removes and returns an item from the collection satisfying the priority condition
 *  PRE:    the collection is not empty (but it would be good to check anyway!).
 *  POST:   the item satisfying the priority condition is removed from the collection.
 *  RETURN: the item satisfying the priority condition
 *
 *  Priority condition:
 *    The PixelPoint in the collection whose color is the minimum distance away
 *    from the reference color is the priority item to be returned.
 *
 *    In case of multiple items with the same priority value (i.e. minimal distance
 *    away from the reference color), the one with the minimal y-coordinate will be
 *    selected.
 *    In case of multiple items with the same priority value and the same y-coordinate,
 *    the one with the minimal x-coordinate will be selected.
 *
 *    ***ATTENTION*** The dist() function in HSLAPixel.h will be very helpful!
 *
 *  Combined with Insert(), think about the time complexity of maintaining the
 *  priority order and/or accessing the priority element in this specific application!
 */
PixelPoint PriorityNeighbours::Remove()
{
  PixelPoint valueReturn;
  vector<PixelPoint> pointRemoved;
  //double refDist = refcolor.dist(refcolor);
  double minDist = 9000; //arbitrary number
  //int counter = 0;

  for(int i = 0; i < points.size(); i++){
    // Iterate through all the points and find the min one!
    PixelPoint p = points.at(i);
    double refDist = refcolor.dist(p.color);

    if(refDist < minDist){
      minDist = refDist;
      valueReturn = p;
    }else if(refDist == minDist){
      if(p.y < valueReturn.y){
        valueReturn = p;
      } else if (p.y == valueReturn.y){
      if(p.x < valueReturn.x){
        valueReturn = p;
      } 
    }
  }
  }
  
  for (PixelPoint elem : points)
  {
    if (!elem.operator==(valueReturn))
    {
      pointRemoved.push_back(elem);
    }
  }
  
  // delete[] points; // do we need this?
  points = pointRemoved;
  
  return valueReturn;
}

/*
 *  Checks if the collection is empty
 *  RETURN: true, if the collection is empty
 *          false, otherwise
 */
bool PriorityNeighbours::IsEmpty() const
{
  return points.empty();
}

/*
 *  Returns the value of the reference color
 */
HSLAPixel PriorityNeighbours::GetReferenceColor() const
{
  return refcolor;
}

/*
 *  Sets the reference color attribute
 *  POST: refcolor is set to the supplied value
 */
void PriorityNeighbours::SetReferenceColor(HSLAPixel ref)
{
  refcolor.h = ref.h;
  refcolor.s = ref.s;
  refcolor.l = ref.l;
  refcolor.a = ref.a;
}