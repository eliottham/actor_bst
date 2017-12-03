/* 
 * Overview of code: testBST tests out to see if the iterator works as it 
 * should be doing.  Also  we implemented more test cases to test out 
 * the other functions we implemented in BST.hpp
 */

#include "BST.hpp"
#include "BSTIterator.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);
    
    // test the template version of the BST  with ints 
    BST<int> btemp;
    for (int item : v) {
        // the auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }

    // now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // test the iterator: the iterator should give an in-order traversal
  
    // sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // this is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    // this is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;


    // test the height of tree
    cout << "Height is " << btemp.height() << "." << endl;
    if(btemp.height() == 2) {
      cout << "success!" << endl;
    }
    else {
      cout << "Incorrect height of BST." << endl;
      return -1;
    }

    // test the size of tree
    cout << "Size is " << btemp.size() << "." << endl;
    if(btemp.size() == 5) {
      cout << "success!" << endl;
    }
    else {
      cout << "Incorrect size of BST." << endl;
      return -1;
    }

    // test if tree is empty
    cout << "Tree is empty? " << btemp.empty() << endl;
    if(btemp.empty()) {
      cout << "Incorrect. Tree is not empty." << endl;
      return -1;
    }
    else {
      cout << "success!" << endl;
    }

    cout << "All tests passed!" << endl;
    return 0;
}
