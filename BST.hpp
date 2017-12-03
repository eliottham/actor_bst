/*
 * Overview of code: This is the BST class in which we implement the functions
 * to insert nodes of the BST, find specific nodes, find the size of the BST, 
 * find the height of the BST, and to check if it is empty.
 */
#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
#include <queue>
using namespace std;

template<typename Data>
class BST {

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
   */
  BST() : root(nullptr), isize(0) {}


  /** Default destructor.
      Delete every node in this BST.
  */
  ~BST();

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return a pair where the first element is an iterator 
   *  pointing to either the newly inserted element or the element 
   *  that was already in the BST, and the second element is true if the 
   *  element was newly inserted or false if it was already in the BST.
   * 
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  
   */
  std::pair<iterator, bool> insert(const Data& item);


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const;

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const;
  
  /** Return the height of the BST.
      height of a tree starts with root at height 0
   */ 
  unsigned int height() const;


  /** Return true if the BST is empty, else false.
   */ 
  bool empty() const;

  /** Return an iterator pointing to the first (smallest) item in the BST.
   */ 
  iterator begin() const;

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const;


private:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;
  
  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Find the first element of the BST
   * Helper function for the begin method above.
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root);

  /** do a postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n);
 };


// ********** Function definitions ****************


/** Default destructor.
    Delete every node in this BST.
*/
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either 
 *  the newly inserted element or the element that was already in the BST, 
 *  and the second element is true if the element was newly inserted or false 
 *  if it was already in the BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
  // check if the tree if empty, then make the item the root
  if(!root){
    root = new BSTNode<Data>(item);
    isize++;
    return pair<BSTIterator<Data>, bool>(BSTIterator<Data>(root),true);
  }

  // check for if the tree if not empty
  BSTNode<Data> * currentNode = root;
  BSTNode<Data> * newNode = new BSTNode<Data>(item);

  // while true
  while(1){
    // check if current item is less than the current node's value
    if(item < currentNode->data){
      // check if the current node does not have a left child and attach newNode
      if(currentNode->left == nullptr){
        currentNode->left = newNode;
        newNode->parent = currentNode;
        isize++;
        return pair<BSTIterator<Data>, bool>(BSTIterator<Data>(newNode),true);
      }
      // check if the current node has a left child, so change the pointer to
      // its left child
      else{
        currentNode = currentNode->left;
	continue;
      }	
    }
    // check if current item is greater than the current node's value
    else if(currentNode->data < item){
      // check if current node does not have a right child and attach newNode
      if(currentNode->right ==nullptr){
        currentNode->right = newNode;
        newNode->parent = currentNode;
        isize++;
        return pair<BSTIterator<Data>, bool>(BSTIterator<Data>(newNode),true);
      }
      // check if the current node has a right child, so change the pointer to
      // its right child
      else{
        currentNode = currentNode->right;
	continue;
      }
    }
    else{
    // check for if the desired node to be inserted already exists, then return false
      return pair<BSTIterator<Data>, bool>(BSTIterator<Data>(currentNode),false);
    }	
  }
}



/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{
  // check for if the tree if not empty
  BSTNode<Data> * currentNode = root;
  if(currentNode == nullptr) {
    return BSTIterator<Data>(nullptr);
  }

  // while true
  while(1){
    // check if current item is less than the current node's value
    if(item < currentNode->data){
      // check if the current node does not have a left child and point past the
      // last node
      if(currentNode->left == nullptr){
        return BSTIterator<Data>(nullptr);
      }
      // check if the current node has a left child, so change the pointer to
      // its left child
      else{
        currentNode = currentNode->left;
	continue;
      }	
    }
    // check if current item is greater than the current node's value
    else if(currentNode->data < item){
      // check if current node does not have a right child and point past the
      // last node
      if(currentNode->right ==nullptr){
        return BSTIterator<Data>(nullptr);
      }
      // check if the current node has a right child, so change the pointer to
      // its right child
      else{
        currentNode = currentNode->right;
	continue;
      }
    }
    // check for if the desired node is found, then return iterator pointing to
    // the item
    else{
      return BSTIterator<Data>(currentNode);    
    }	
  }
}

  
/** Return the number of items currently in the BST.
 */ 
template <typename Data>
unsigned int BST<Data>::size() const
{  
   return isize;
}

/** Return the height of the BST.
 */
template <typename Data> 
unsigned int BST<Data>::height() const
{ 
  int height = 0;
  // initialize the queue
  queue<BSTNode<Data> *> current_level;
  queue<BSTNode<Data> *> next_level;

  if(root == nullptr){
    return 0;
  }
  
  // push root into the queue
  current_level.push(root);
  
  // while the current level has nodes
  while(!current_level.empty()){
    // go through each of these nodes and check for children
    BSTNode<Data> * node = current_level.front();
    current_level.pop();

    // add the children of the current node to the queue of next_level
    if(node->left != nullptr) {
      next_level.push(node->left);
    }
    if(node->right != nullptr) {
      next_level.push(node->right);
    }
    
    // if the current level is empty and the next level is not
    if(current_level.empty() && !next_level.empty()) {
        // increase the height and set the current level to the next level
        // and clear the next level; continue until there are no more levels.
	height++;
	current_level.swap(next_level);
	queue<BSTNode<Data> *> empty;
	next_level.swap(empty);
    }
  }
  return height;
}

/** Return true if the BST is empty, else false.
 */ 
template <typename Data>
bool BST<Data>::empty() const
{
  // check for if size of the BST is 0, meaning that its empty
  if(isize == 0) {
    return true;
  }
  return false;
}

/** Return an iterator pointing to the first (smallest) item in the BST.
 */ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */ 
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  BSTNode<Data> * current = root;
  
  // the left most node is the first element of the BST
  while(current->left != nullptr){
    current = current->left;
  }
 
  return current;
}

/** do a postorder traversal, deleting nodes
 */
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
  if(n == nullptr){
    return;
  }

  // recursively delete while n has a left child
  if(n->left){
   deleteAll(n->left);
  }

  // recursively delete while n has a right child
  if(n->right){
   deleteAll(n->right);
  }

  delete n;

  n = nullptr;
}

#endif //BST_HPP