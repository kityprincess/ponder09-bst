/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST <T> tree = BST <T>();
   int j = 0;

   // inserts the items from our array into a binary tree
   for (int i = 0; i < num; i++)
      tree.insert(array[i]);
   
   // puts the items back in our array in order
   for (BSTIterator <T> it = tree.begin(); it != tree.end(); ++it, j++)
      array[j] = *it;
}

#endif // SORT_BINARY_H
