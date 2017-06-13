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

   // non-default AND default constructor
   // Since we provide a default value for the parameter, this can be
   // used as the default constructor too
   Stack(int in_capacity = 0) throw (const char *);

   // copy constructor
   Stack(const Stack<StackElement> & source) throw (const char *);

   // destructor
   ~Stack() {
      if (m_capacity > 0) // If this is true, we have an allocated buffer
         delete[] m_data;
   }

   // assignment operator
   Stack<StackElement> & operator = (const Stack<StackElement> & rhs) throw (const char *);

   // check if stack is empty
   bool empty() const { return m_top == -1; };

   // return size
   int size() const { return m_top + 1; }

   // capacity
   int capacity() const { return m_capacity; }

   // clear the stack
   void clear() { m_top = -1; }

   // add a value to the top of the stack
   void push(const StackElement & value) throw (const char *);

   // return the value at the top of the stack
   StackElement & top() const throw (const char *);

   // remove the value at the top of the stack
   void pop() throw (const char *);

private:
   StackElement * m_data;              // buffer
   int m_capacity;                     // capacity
   int m_top;                          // top of the stack
   void resize() throw (const char*);  //resize the stack
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
Stack<StackElement> & Stack<StackElement> :: operator =
(const Stack<StackElement> & rhs) throw (const char *)
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
      // We only delete our data array if we have data
      // note that we're assuming that m_data is not null if m_capacity
      // is not zero.
      if (m_capacity)
         delete[] m_data;

      m_capacity = rhs.m_capacity;

      // We only create a new array if our source had one (i.e.
      // it had capacity)
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
void Stack <StackElement> ::push(const StackElement & value) throw (const char *)
{
   if (m_top == m_capacity - 1)
   {
      resize();
   }

   if (m_top < m_capacity - 1)
   {
      ++m_top;
      m_data[m_top] = value;
   }

   else
   {
      throw "ERROR: Unable to allocate a new buffer for Stack";
   }
}

/****************************************************************
* STACK :: TOP
* Will check what value is at the top of the stack
****************************************************************/
template <class StackElement>
StackElement & Stack <StackElement> ::top() const throw (const char *)
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
void Stack <StackElement> ::pop() throw (const char *)
{
   // If the stack is not empty, pop off the top element
   if (!empty())
      m_top--;
   else
      throw "ERROR: Unable to pop from an empty Stack";
}

/***************************************************
* STACK :: RESIZE
* Increases the size of the array to accomodate more
* data.
****************************************************/
template <class StackElement>
void Stack <StackElement> ::resize() throw (const char*)
{
   // First, check to see if we have an array
   // if not, we simply create a small one and
   // return
   if (!m_capacity)
   {
      m_data = new (std::nothrow) StackElement[1];

      if (NULL == m_data)
         throw "ERROR: Unable to allocate a new buffer for Stack";

      m_capacity = 1;
      return;
   }

   // If we reach this point, then we have
   // an array, so we need to double its size
   // and copy over the existing data
   StackElement * new_data = new (std::nothrow) StackElement[m_capacity * 2];

   if (NULL == new_data)
      throw "ERROR: Unable to allocate a new buffer for Stack";

   // We increase m_capacity _after_ we know we've succeeded in
   // doubling the array size, so that we know m_capacity matches
   // reality
   m_capacity *= 2;

   // Then, we copy over our existing data
   for (int i = 0; i <= m_top; i++)
      new_data[i] = m_data[i];

   // Delete our old buffer and swap in the new one
   delete[] m_data;
   m_data = new_data;
}

#endif // Stack_H