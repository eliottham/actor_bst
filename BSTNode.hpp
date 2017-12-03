/* 
 * Overview of code:  This is the implementation of the BSTNode class and
 * sets up what constitutes a BSTNode, such as its successor, children,
 * parent, and data.
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {

public:
  Data const data; 
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  // the const Data in this node.

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d);


  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor(); 

}; 

template <typename Data>
BSTNode<Data>::BSTNode(const Data & d) : data(d), left(0), right(0), parent(0) {}

/* Return a pointer to the BSTNode that contains the item that is sequentially next 
 * in the tree */
template <typename Data>
BSTNode<Data>* BSTNode<Data>::successor()
{
  BSTNode<Data>* successor = nullptr; 

  if(this->right != nullptr) {
    // the successor lies in the right subtree
    successor = this->right;
    while(successor->left != nullptr) {
      successor = successor->left;
    }
  }
  else {
    // if the successor is an ancestor and we are at the root, return nullptr
    if(this->parent == nullptr) {
      return nullptr;
    }
    // if successor is not in the right subtree, it is the ancestor in which
    // its left child equals node
    BSTNode<Data>* node = this;
    successor = this->parent;
    while(successor->left != node) {
      if(successor->parent == nullptr) {
        // if we get to the root and it is still not the successor, return nullptr
	return nullptr;
      }
      node = node->parent;
      successor = successor->parent;
     }
  }
  return successor;
}

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
