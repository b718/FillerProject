/*
 *  File:        filler.cpp
 *  Description: Implementation of functions in the filler namespace.
 *
 */

/*
 *  Performs a flood fill using breadth first search.
 *
 *  PARAM:  config - FillerConfig struct to setup the fill
 *  RETURN: animation object illustrating progression of flood fill algorithm
 */
animation filler::FillBFS(FillerConfig &config)
{

  return Fill<Queue>(config);
  // We need a queue
}

/*
 *  Performs a flood fill using depth first search.
 *
 *  PARAM:  config - FillerConfig struct to setup the fill
 *  RETURN: animation object illustrating progression of flood fill algorithm
 */
animation filler::FillDFS(FillerConfig &config)
{

  return Fill<Stack>(config);
  // We need a stack
}

/*
 *  Run a flood fill on an image starting at the seed point
 *
 *  PARAM:  config - FillerConfig struct with data for flood fill of image
 *  RETURN: animation object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure>
animation filler::Fill(FillerConfig &config)
{
  /*
   * You need to implement this function!
   *
   * This is the basic description of a flood-fill algorithm: Every fill
   * algorithm requires an ordering structure, which is passed to this
   * function via its template parameter. For a breadth-first-search
   * fill, that structure is a Queue, for a depth-first-search, that
   * structure is a Stack. To begin the algorithm, you simply place the
   * given point in the ordering structure, marking it processed
   * (the way you mark it is a design decision you'll make yourself).
   * We have a choice to either change the color, if appropriate, when we
   * add the point to the OS, or when we take it off. In our test cases,
   * we have assumed that you will change the color when a point is added
   * to the structure.
   * Until the structure is empty, you do the following:
   *
   * 1.     Remove a point from the ordering structure, and then...
   *
   *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
   *              within (or equal to) tolerance distance from the seed point,
   *              to the ordering structure, and
   *              mark them as processed.
   *        2.    if it is an appropriate frame, send the current PNG to the
   *              animation (as described below).
   *
   * 2.     When implementing your breadth-first-search and
   *        depth-first-search fills, you will need to explore neighboring
   *        pixels (up/down/left/right) in some order.
   *
   *        While the order in which you examine neighbors does not matter
   *        for a proper fill, you must use the same order as we do for
   *        your animations to come out like ours! The order you should put
   *        neighboring pixels **ONTO** the queue or stack is based on the
   *        following priority condition:
   *        ** MINIMUM COLOR DISTANCE FROM THE CURRENT PIXEL **
   *        Ties are broken first by minimum y-coordinate, then by minimum x-coordinate.
   *        The HSLAPixel.dist() function will be useful, and you should
   *        take advantage of the functionality in your PriorityNeighbours class.
   *
   *        If you process the neighbours in a different order, your fill may
   *        still work correctly, but your animations will be different
   *        from the grading scripts!
   *
   * 3.     For every k pixels filled, **starting at the kth pixel**, you
   *        must add a frame to the animation, where k = frameFreq.
   *
   *        For example, if frameFreq is 4, then after the 4th pixel has
   *        been filled you should add a frame to the animation, then again
   *        after the 8th pixel, etc.  You must only add frames for the
   *        number of pixels that have been filled, not the number that
   *        have been checked. So if frameFreq is set to 1, a pixel should
   *        be filled every frame.
   *
   * 4.     Finally, as you leave the function, send one last frame to the
   *        animation. This frame will be the final result of the fill, and
   *        it will be the one we test against.
   *
   */

  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;
  OrderingStructure<PixelPoint> os;
  int frameReq = config.frameFreq;
  double tolerance = config.tolerance;
  vector<vector<bool>> tracker; // this will track all of the nodes we have visited
  // vector<PixelPoint> tracker;

  // We also need something to keep track of where we have been
  // - We will use a 2d array of booleans for this!

  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited

  // First we need to decide if we are using a stack or a queue
  // Second we need to understand how to traverse through it
  // - With Stack and Queues and the way we add them
  // Third, we need to figure out the frames and when we add one frame
  // Fourth, we need to debug, do the perfect state first then edge cases

  // We first remove a node, edit it, and then find its friends, edit them and repeat!

  // We need to iterate over the entire image!
  os.Add(config.seedpoint); // First step is to add it into our OS
                            //  This means that that x, y for seed is true!

  while (!os.IsEmpty())
  {
    PixelPoint currPixel = os.Remove();       // Take the first thing off
    tracker[currPixel.x][currPixel.y] = true; // Since we are processing it we set it to true!
    // HSLAPixel* imgPixPtr = config.img.getPixel(currPixel.x, currPixel.y);
    // picker

    // We need to go left, right, up, and down!
    //               x-1, x+1, y+1, y-1!
    if (tracker[currPixel.x - 1][currPixel.y] != true && currPixel.color.dist(*config.img.getPixel(currPixel.x - 1, currPixel.y))) // leftcase
    {
    }

    if (tracker[currPixel.x + 1][currPixel.y] != true && currPixel.color.dist(*config.img.getPixel(currPixel.x + 1, currPixel.y))) // leftcase
    {
    }

    if (tracker[currPixel.x][currPixel.y - 1] != true && currPixel.color.dist(*config.img.getPixel(currPixel.x, currPixel.y - 1))) // leftcase
    {
    }

    if (tracker[currPixel.x][currPixel.y + 1] != true && currPixel.color.dist(*config.img.getPixel(currPixel.x, currPixel.y + 1))) // leftcase
    {
    }

    os.Add(config.neighbourorder.Remove());
  }
  // Finally here, we need to do framereq!

  anim.addFrame(config.img); // Sending the last frame to the animation as we leave!
  return anim;
}
