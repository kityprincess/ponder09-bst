/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Author:
 *    
 * Summary:
 *    
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include <cassert>
#include <stack>
#include "bnode.h"

/*************************************************************************
* CLASS: BSTITERATOR
* Iterator for a BST
**************************************************************************/
template <class T>
class BSTIterator
{
public:
   BSTIterator<T> & operator -- ();
   BSTIterator<T> & operator ++ () { return *this; };
   T & operator * () const { return nodes.top()->data; }

private:
   stack<BinaryNode<T> * > nodes;
};

/***************************************************************************
* CLASS: BST
* A Binary Search Tree
****************************************************************************/
template <class T>
class BST
{
public:
   BST() { }
   BST(const BST & in_source) { }
   BST & operator = (const BST & in_source) { return *this; }
   int size() const { return 0; }
   bool empty() const { return false; }
   void clear() { }
   void insert(const T & in_value) { }
   void remove(const BSTIterator<T> & in_pItem) { }

   BSTIterator<T> find(const T & in_value) const { BSTIterator<T> result; return result;  }
   BSTIterator<T> begin() const { BSTIterator<T> result; return result; }
   BSTIterator<T> end() const { BSTIterator<T> result; return result;  }
   BSTIterator<T> rbegin() const { BSTIterator<T> result; return result;  }
   BSTIterator<T> rend() const { BSTIterator<T> result; return result;  }

private:
   BinaryNode<T> * root;

};

/************************************************************************
* :: NOT EQUAL (BSTITERATOR)
* Indicates whether two BSTIterators point to the same node
*************************************************************************/
template <class T>
bool operator != (const BSTIterator<T> & lhs, const BSTIterator<T> & rhs)
{
   return false;
}

/************************************************************************
* :: EQUAL (BSTITERATOR)
* Indicates whether two BSTIterators point to the same node
*************************************************************************/
template <class T>
bool operator == (const BSTIterator<T> & lhs, const BSTIterator<T> & rhs)
{
   return false;
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

#endif // BST_H

