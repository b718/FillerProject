/*
 *  File:        stack.cpp
 *  Description: Implementation of the Stack class.
 *
 *               Complete your implementation in this file
 */

/*
 *  Default constructor. Remember to initialize any variables you need
 *  and allocate any required memory. The initial size of `items` should
 *  be DEFAULTCAPACITY defined in stack.h.
 *
 */
template <class T>
Stack<T>::Stack()
{
  // The header states that they want the array implementation of the Stack!
  items = new T[DEFAULTCAPACITY];
  max_items = DEFAULTCAPACITY;
  num_items = 0;
}

/*
 *  Destructor. Remember to free any memory allocated.
 */
template <class T>
Stack<T>::~Stack()
{
  delete items;
  items = nullptr;
  max_items = 0; // Unsure about this line
  num_items = 0;

  // We delete the item that it points to and then set the ptr to null!
  // The only issue is that, I don't think this delete all of the things it points to!
}

/*
 *  Adds the parameter object to the top of the Stack. That is, the
 *  element should go at the end of the array. If the dynamic array
 *  holding the stack elements is full the array should be resized. Resize should be
 *  called by multiplying current capacity EXPANSIONFACTOR defined in stack.h.
 *  To be clear resize should happen before adding the element to the stack and only
 *  when the stack is completely full.
 *
 *  PARAM: item - the object to be added to the Stack.
 */
template <class T>
void Stack<T>::Push(const T &item)
{
  if (num_items == (max_items))
  {
    Resize(max_items * EXPANSIONFACTOR);
    // items[num_items] = item;
    // num_items++;
    // Lets say for example we had an array of size 1,
    // we would fill index[0], and then add 1 to the num_items
  }
  items[num_items] = item;
  num_items++;
};

/*
 *  Removes the object on top of the Stack, and returns it. That is, remove
 *  the element at the end of the array. You may assume this function
 *  is only called when the Stack is not empty. If the size of the stack changes
 *  to strictly less than a ratio of 1.0 / SHRINKRATE (where SHRINKRATE is defined in stack.h)
 *  after the item is removed the Stack should be resized to the larger of max_items / EXPANSIONFACTOR,
 *  or DEFAULTCAPACITY.
 *
 *  RETURN: the element that used to be at the top of the Stack.
 */
template <class T>
T Stack<T>::Pop()
{
  T item = NULL;
  // int afterPopSize = num_items;
  // afterPopSize--;

  num_items--;
  item = items[num_items];

  // Note to self, when you do num_items--; it actually subtracts num_items as well which is
  // why it was off by 1 everytime

  // We didnt compare the ratios here
  // if (afterPopSize < (1.0 / SHRINKRATE))
  // {
  //   num_items--;
  //   item = items[num_items];
  //   Resize(num_items);
  // }
  // else
  // {
  //   num_items--;
  //   item = items[num_items];
  // }

  // convert to double for accuracy!
  double numberItems = num_items;
  double maxNumberItems = max_items;
  double ratioOfNumberItemsAndMax = numberItems/maxNumberItems;
  if((ratioOfNumberItemsAndMax) < (1.0 / SHRINKRATE)){
      if(maxNumberItems/EXPANSIONFACTOR > DEFAULTCAPACITY){
        Resize(maxNumberItems/EXPANSIONFACTOR);
      }else {
        Resize(DEFAULTCAPACITY);
      }
  }

  return item;
};

/*
 *  Adds the given element to the ordering structure.
 *  See OrderingStructure::Add()
 */
template <class T>
void Stack<T>::Add(const T &item)
{
  // complete your implementation below
  // Hint: this should call another Stack function
  //   to add the element to the Stack
  Push(item);
}

/*
 *  Removes an element from the ordering structure. You may assume
 *  that this function is only called when the ordering structure is
 *  not empty.
 *  See OrderingStructure::Remove()
 */
template <class T>
T Stack<T>::Remove()
{
  // complete your implementation below
  // Hint: this should call another Stack function
  //   to remove an element from the Stack and return it.

  // We need to loop through and find a specific element!

  T item = Pop();
  return item;
}

/*
 *  Finds the object on top of the Stack, and returns it to the caller.
 *  Unlike Pop(), this operation does not alter the Stack itself.
 *  It should look at the end of the array. You may assume this function
 *  is only called when the Stack is not empty.
 *
 *  RETURN: the element at the top of the Stack.
 */
template <class T>
T Stack<T>::Peek()
{
  T item = NULL;
  size_t itemsNum = num_items;
  item = items[itemsNum - 1];

  return item;
};

/*
 *  Determines if the Stack is empty.
 *  RETURN: true if the stack is empty,
 *          false otherwise.
 */
template <class T>
bool Stack<T>::IsEmpty() const
{
  if (num_items > 0)
  {
    return false;
  }
  else
  {
    return true;
  }
};

/*
 *  Return the maximum number of items the stack can hold.
 *
 *  Note: This is an implementation detail we would normally hide.
 *  We include it here for testing purposes.
 *
 *  RETURN: maximum number of items the stack can hold (int)
 */
template <class T>
size_t Stack<T>::Capacity() const
{

  return max_items;
};

/*
 *  Return the number of items on the stack.
 *  RETURN: number of items on the stack (int)
 */
template <class T>
size_t Stack<T>::Size() const
{

  return num_items;
};

/*
 *  Resize the the member variable `items`.
 *  The minimum size is the number of items in the Stack.
 *  Don't forget to free up any memory that is no longer used.
 *  PRE: n >= num_items, i.e. the new size has room for all items in the structure
 *  PARAM: n - the capacity of the stack after resizing
 */
template <class T>
void Stack<T>::Resize(size_t n)
{
  // complete your implementation below
  // The idea is that we do EXPANSIONFACTOR*DEFAULTCAPACITY
  // And we also have to consider the shrinking case as well!

  // What we wrote here is not a good way to do it!
  // T *resizeArr = nullptr;
  // if (n == (max_items))
  // {
  //   resizeArr = new T[max_items * EXPANSIONFACTOR];

  //   for (int i = 0; i < n; i++)
  //   {
  //     resizeArr[i] = items[i];
  //   }

  //   max_items = max_items * EXPANSIONFACTOR;
  // }
  // else if (n < (1.0 / SHRINKRATE))
  // {

  //   //     max_items / EXPANSIONFACTOR,
  //   // *  or DEFAULTCAPACITY.
  //   if ((max_items / EXPANSIONFACTOR) > DEFAULTCAPACITY)
  //   {
  //     resizeArr = new T[max_items / EXPANSIONFACTOR];
  //   }
  //   else
  //   {
  //     resizeArr = new T[DEFAULTCAPACITY];
  //   }

  //   for (int i = 0; i < n; i++)
  //   {
  //     resizeArr[i] = items[i];
  //   }

  //    if ((max_items / EXPANSIONFACTOR) > DEFAULTCAPACITY)
  //   {
  //     max_items = max_items / EXPANSIONFACTOR;
  //   }
  //   else
  //   {
  //     max_items = DEFAULTCAPACITY;
  //   }
  // }

  T *resizeArr = new T[n];
  for (int i = 0; i < n; i++)
  {
    resizeArr[i] = items[i];
  }

  max_items = n;
  delete items;

  items = resizeArr;
};
