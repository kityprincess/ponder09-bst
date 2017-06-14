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
   BSTIterator() { nodes.push(NULL); }
   BSTIterator(BinaryNode<T> * in_node) { nodes.push(in_node); }
   BSTIterator(stack<BinaryNode<T> * > in_stack) { nodes = in_stack; }
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
   BST() : root(NULL) { }
   ~BST() { clear(); }
   BST(BST <T> & in_source) throw (const char *);
   BST & operator = (const BST & in_source);

   int size() const;
   bool empty() const { return root == NULL; }
   void clear() { deleteBinaryTree(root); root = NULL; }
   void insert(const T & in_value);
   void remove(const BSTIterator<T> & in_pItem);

   BSTIterator<T> find(const T & in_value) const { BSTIterator<T> result; return result;  }
   BSTIterator<T> begin() const;
   BSTIterator<T> end() { return BSTIterator <T>(NULL); }
   BSTIterator<T> rbegin() const;
   BSTIterator<T> rend() { return BSTIterator <T>(NULL); }

private:
   void insertInternal(const T & in_value, BinaryNode<T> * & in_subtree);
   BinaryNode <T> * findLeft(BinaryNode <T> * pElement) const;
   BinaryNode <T> * findRight(BinaryNode <T> * pElement) const;
   BinaryNode<T> * copy(BinaryNode <T> * pElement);
   BinaryNode<T> * root;
};

/***********************************************************************
* BST :: COPY
* Copies over the elements in a tree
***********************************************************************/
template <class T>
BinaryNode<T> * BST<T> :: copy(BinaryNode <T> * pElement)
{
   if (pElement == NULL)
   {
      return pElement;
   }

   BinaryNode <T> * newNode;
   try
   {
   newNode = new BinaryNode <T>(pElement->data);
   if (pElement->pLeft != NULL)
      {
         newNode->pLeft = copy(pElement->pLeft);
      }
   if (pElement->pRight != NULL)
      {
         newNode->pRight = copy(pElement->pRight);
      }
    }
    catch(std::bad_alloc)
    {
       throw "ERROR: Unable to allocate a node";
    }
    return newNode;
}

/*******************************************
 * BST :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
BST <T> :: BST(BST <T> & in_source) throw (const char *)
{
   if (in_source.root != NULL)
   {
      this->root = copy(in_source.root);
   }
}

/*******************************************
 * BST :: ASSIGNMENT OPERATOR
 *******************************************/
 template <class T>
 BST<T> & BST<T> :: operator = (const BST & in_source)
 {
    this->root = copy(in_source.root);
    return *this;
 }

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

/*****************************************
* BST:: SIZE
* Number of elements in binary search tree.
*****************************************/
template <class T>
int BST<T> :: size() const
{
   // no elements in tree
   if (root == NULL)
      return 0;

   // add root and any subtrees
   int size = 1;

   if (root->pLeft)
      size += root->pLeft->size();

   if (root->pRight)
      size += root->pRight->size();

   return size;
}

/**************************************************
* BST :: INSERT
* Adds a new value to the BST in the appropriate
* spot.
* Note: DOES NOT ATTEMPT TO BALANCE THE TREE
*************************************************/
template<class T>
void BST<T> :: insert(const T & in_value)
{
   insertInternal(in_value, root);
}

/**************************************************
* BST :: REMOVE
* Remove a value from the BST and adjust tree.
*************************************************/
template<class T>
void BST<T> :: remove(const BSTIterator<T> & in_pItem)
{
   //BinaryNode <T> node = *in_pItem;
   // No item to remove
   //if (find(node) == NULL)
   //{
   //   cout << "Item not found.";
   //   return;
   //}

   //// Case where there are 2 children
   //if (node->pLeft != NULL && node->pRight != NULL)
   //{
   //   // find the in-order successor
   //   BinaryNode <T> successor = node->pRight;
   //   while (successor->pLeft != NULL)
   //   {
   //      successor = successor->pLeft;
   //   }
   //   node->data = successor->data;
   //   node = successor;
   //}

   //// Case where there are no children or 1 child
   //BinaryNode <T> subtree = node->pLeft;
   //if (subtree == NULL)
   //   subtree = node->pRight;
   //if (node->pParent == NULL)
   //   root = subtree;
   //else if (node->pParent->pLeft == node)
   //   node->pParent->pLeft = subtree;
   //else node->pParent->pRight == subtree;
   //delete node;
}

/**************************************************
* BST :: INSERTINTERNAL
* Implements a recursive algorithm to insert a
* binary node in the right spot
* Note: DOES NOT ATTEMPT TO BALANCE THE TREE
*************************************************/
template<class T>
void BST<T> :: insertInternal(const T & in_value, BinaryNode<T> * & in_subtree)
{
   if (NULL == in_subtree)
   {
      try
      {
         in_subtree = new BinaryNode<T>(in_value);
      }
      catch (bad_alloc ex)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }
   else if (in_value < in_subtree->data)
      insertInternal(in_value, in_subtree->pLeft);
   else if (in_value > in_subtree->data)
      insertInternal(in_value, in_subtree->pRight);
   else
      return;
}

/**************************************************
* BST :: FINDLEFT
* Finds the leftmost data element.
*************************************************/
template <class T>
BinaryNode <T> * BST<T> :: findLeft(BinaryNode <T> * pElement) const
{
   BinaryNode <T> * tempLeft = NULL;

   if (pElement != 0)
   {
      findLeft(pElement->pLeft);
      tempLeft = pElement;
   }

   return tempLeft;
}

/**************************************************
* BST :: FINDRIGHT
* Finds the rightmost data element.
*************************************************/
template <class T>
BinaryNode <T> * BST<T> :: findRight(BinaryNode <T> * pElement) const
{
   BinaryNode <T> * tempRight = NULL;

   if (pElement != 0)
   {
      findRight(pElement->pRight);
      tempRight = pElement;
   }

   return tempRight;
}

/**************************************************
* BST :: BEGIN
* Returns an iterator to the leftmost element in the list
*************************************************/
template <class T>
BSTIterator<T> BST<T> :: begin() const
{
   return BSTIterator<T>(findLeft(root));
}

/**************************************************
* BST :: RBEGIN
* Returns an iterator to the rightmost element in the list
*************************************************/
template <class T>
BSTIterator<T> BST<T> :: rbegin() const
{
   return BSTIterator<T>(findRight(root));
}

#endif // BST_H