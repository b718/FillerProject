/*
*  File:        queue.cpp
*  Description: Implementation of the Queue class.
*
*               Complete your implementation in this file
*/

/*
*  Adds the parameter object to the back of the Queue.
*
*  NOTE: This fuction should have O(1) behavior over n operations!
*
*  PARAM: item -  object to be added to the Queue.
*/
template <class T>
void Queue<T>::Enqueue(T const& item)
{
  // We need to decide which of the 2 stacks represents the
  // actual queue and which will always be empty!  

  while(!stack_1.IsEmpty()){
    stack_2.Push(stack_1.Pop());
  }

  stack_2.Push(item);

  while(!stack_2.IsEmpty()){
    stack_1.Push(stack_2.Pop());
  }
}

/*
*  Removes the object at the front of the Queue, and returns it to
*  the caller. You may assume that this function is only called
*  when the Queue is non-empty.
*
*  NOTE: This function should have O(1) behavior over n operations!
*
*  RETURN: the item that used to be at the front of the Queue.
*/
template <class T>
T Queue<T>::Dequeue()
{
  
  T item = stack_1.Pop();
  return item;
}

/*
*  Adds an element to the ordering structure.
*
*  See OrderingStructure::Add()
*/
template <class T>
void Queue<T>::Add(const T& item)
{
  // complete your implementation below
  // Hint: this function should call a Queue
  //  function to add the element to the Queue.

  Enqueue(item);
  
}

/*
*  Removes an element from the ordering structure.
*
*  See OrderingStructure::Remove()
*/
template <class T>
T Queue<T>::Remove()
{
  // complete your implementation below
  // Hint: this function should call a Queue
  // function to remove an element from the Queue and return it. You will
  // need to replace the following line.
  
  T item = Dequeue();
  return item; 
}

/*
*  Finds the object at the front of the Queue, and returns it to
*  the caller. Unlike Dequeue(), this operation does (conceptually!) not alter the
*  Queue; however, you may need to alter the internal representation of the Queue.
*  You may assume that this function is only called when the
*  Queue is non-empty.
*
*  NOTE: This function should have O(1) behavior over n operations!
*
*  RETURN: the item at the front of the queue.
*/
template <class T>
T Queue<T>::Peek()
{
  
  T item = stack_1.Peek();
  return item; 
}

/*
*  Determines if the Queue is empty.
*
*  RETURN: true if the stack is empty,
*          false otherwise.
* 
*  NOTE: This function must always run in O(1) time!
*/
template <class T>
bool Queue<T>::IsEmpty() const
{
  
  return stack_1.IsEmpty();
}
