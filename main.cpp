/*
 * Overview of code:  The main prompts the user for an actor name, and the main
 * calls the functions to find the actors of the tree, print the size and 
 * height of the tree, and whether the actors exists, and prompts them if 
 * they want to try again.
 */

#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include<fstream>
#include<string>
    		
using namespace std;

int main(int argc, char* argv[])
{
    // size of tree should be stored in local variable size.
    // height of tree should be stored in local variable height.
    // input name will be stored in a string name
    unsigned int size = 0;
    unsigned int height = 0;
    std::string name = "";
  
    // check arguments
    if(argc != 2){
        cout << "Invalid number of arguments.\n" 
             << "Usage: ./main <input filename>.\n";
        return -1;
    }
  
    // open file 
    ifstream in;
    in.open(argv[1]);

    
  
    // check if input file was actually opened
    if(!in.is_open()) 
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }
	else {
        BST<string> tree;
        
        while (getline(in, name)) {
            tree.insert(name);    
        }

        height = tree.height();

        size = tree.size();

        cout << "Size of tree: " << size << endl;
        cout << "Height of tree: " << height << endl;

        char prompt = 'y';
        while (prompt != 'n') {
            cout << "Enter actor/actress name: " << endl;
            getline(cin, name);
            
            BSTIterator<string> checkWord = tree.find(name);
            if (checkWord != 0) {
                cout << name << " found!" << endl;
            }
            else {
                cout << name << " NOT found" << "\n";
            }
            cout << "Search again? (y/n)" << endl;
            cin >> prompt;  // get the first character
            // then ignore until newline
            cin.ignore( numeric_limits <streamsize> ::max(), '\n' );  
        }
        in.close();
    }
    
    return 0;

}
