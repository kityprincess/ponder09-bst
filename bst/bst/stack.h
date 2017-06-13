/***********************************************************************
* Header:
*    Stack
* Summary:
*    This class contains the notion of a stack.
*
*    This will contain the class definition of Stack
* Authors
*    Bryan Lopez, Kimberly Stowe, Matthew Burr & Shayla Nelson
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <new>
#include <cassert>
/************************************************
* Stack
* A class that holds data in stacks
***********************************************/
template <class StackElement>
class Stack
{
public:
   // default constructor
   Stack() : m_capacity(0), m_top(-1), m_data(NULL) {}

   // non-default constructor
   Stack(int in_capacity) throw (const char *);

   // copy constructor
   Stack(const Stack<StackElement> & source) throw (const char *);

   // destructor
   ~Stack()    { if (m_capacity > 0) // If this is true, we have an allocated buffer
                 delete[] m_data; }

   // assignment operator
   Stack<StackElement> & operator =(const Stack<StackElement> & rhs) throw (const char *);

   // check if stack is empty
   bool empty() const { return m_top == -1; };

   // return size
   int size() const { return m_top + 1; }

   // capacity
   int capacity() const { return m_capacity; }

   // clear the stack
   void clear() { m_capacity = 0; m_top = -1; }

   // add a value to the top of the stack
   void push(const StackElement & value) throw (const char *);

   // resize if capacity is reached
   void resize(int in_capacity) throw (const char *);

   // return the value at the top of the stack
   StackElement & top() const throw (const char *);

   // remove the value at the top of the stack
   void pop() throw (const char *);

private:
   StackElement * m_data;           // buffer
   int m_capacity;                  // capacity
   int m_numItems;                  // how many items are in the stack?
   int m_top;                       // top of the stack
};

/***********************************************************************
* STACK :: DEFAULT / NON_DEFAULT CONSTRUCTOR
* Creates an instance of the stack. If the caller provides a Capacity
* we create a Stack with enough storage to hold that capacity
************************************************************************/
template <class StackElement>
Stack<StackElement> ::Stack(int in_capacity) throw (const char *)
   : m_capacity(0), m_top(-1), m_data(NULL)
{
   assert(in_capacity >= 0);
   // First, assure the user specified a valid capacity; if capacity
   // is < 0, we just exit, we've already initialized our values
   // to defaults
   if (in_capacity <= 0)
      return;

   // If we've reached this point, we have an input capacity > 0
   // so we'll try allocating our array
   m_capacity = in_capacity;
   m_data = new (std::nothrow) StackElement[m_capacity];

   // Check to see if we failed to allocate, and if so, throw
   // an error
   if (NULL == m_data)
      throw "ERROR: Unable to allocate a new buffer for Stack";
}

/**********************************************************************
* STACK :: COPY CONSTRUCTOR
* Creates a new Stack by copying the contents of another
**********************************************************************/
template <class StackElement>
Stack<StackElement> ::Stack(const Stack<StackElement> & source) throw (const char *)
   : m_capacity(source.m_capacity), m_top(source.m_top)
{
   // Now we try to allocate our array
   m_data = new (std::nothrow) StackElement[m_capacity];

   // If we failed, we throw an error
   if (NULL == m_data)
      throw "ERROR: Unable to allocate a new buffer for Stack";

   // If we reach this point, we've successfully allocated
   // our buffer, so let's copy the data
   for (int i = 0; i <= m_top; i++)
      m_data[i] = source.m_data[i];
}

/**********************************************************************
* STACK :: ASSIGNMENT
* Assigns one Stack to another, creating a copy of the source
**********************************************************************/
template <class StackElement>
Stack<StackElement> & Stack<StackElement> :: operator =(
   const Stack<StackElement> & rhs) throw (const char *)
{
   // Check to see if we're self-assigning and quit the operation if we
   // are
   if (this == &rhs)
      return *this;

   // Now, check to see if our capacities are the same; if they aren't
   // then we need to delete our existing buffer and (potentially)
   // copy in the new one
   if (m_capacity != rhs.m_capacity)
   {
      if (m_capacity)
         delete[] m_data;

      m_capacity = rhs.m_capacity;

      if (m_capacity)
      {
         m_data = new (std::nothrow) StackElement[m_capacity];

         if (NULL == m_data)
            throw "ERROR: Unable to allocate a new buffer for Stack.";
      }
   }

   // And now we copy over the data
   m_top = rhs.m_top;
   for (int i = 0; i <= m_top; i++)
      m_data[i] = rhs.m_data[i];

   return *this;
}

/****************************************************************
* STACK :: PUSH
* Place a value at the top of the stack
****************************************************************/
template <class StackElement>
void Stack <StackElement> :: push(const StackElement & value) throw (const char *)
{
   if (m_top == -1) {
      m_capacity = 1;
      m_data = new StackElement[m_capacity];
   }

   // double if capacity is reached
   if (m_capacity == m_top + 1)
      resize(m_capacity *= 2);

   m_data[++m_top] = value;
}

/****************************************************************
* STACK :: RESIZE
* Resize stack if capacity is reached
****************************************************************/
template <class StackElement>
void Stack <StackElement> :: resize(int in_capacity) throw (const char *)
{
   try
    {
      StackElement *bufferNew = new StackElement[in_capacity];

      // copy the data into the new buffer
      int i;
      for (i = 0; i < m_top + 1; i++)
         bufferNew[i] = m_data[i];
      bufferNew[i] = '\0';

      // delete the old buffer
      delete [] m_data;

      // reset data
      m_data = bufferNew;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Stack";
      m_capacity /= 2;
   }
}

/****************************************************************
* STACK :: TOP
* Will check what value is at the top of the stack
****************************************************************/
template <class StackElement>
StackElement & Stack <StackElement> :: top() const throw (const char *)
{
   if (!empty())
      return (m_data[m_top]);
   else
   {
      throw "ERROR: Unable to reference the element from an empty Stack";
   }
}

/***************************************************
* STACK :: POP
* Pop an item off the end of the Stack
**************************************************/
template <class StackElement>
void Stack <StackElement> :: pop() throw (const char *)
{
   // If the stack is not empty, pop off the top element
   if (!empty())
      m_top--;
   else
      throw "ERROR: Unable to pop from an empty Stack";
}

#endif // Stack_H

