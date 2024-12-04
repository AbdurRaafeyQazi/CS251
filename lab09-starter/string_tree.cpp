#include <string>
#include <fstream>
#include <iostream>

#include "string_tree.h"

using namespace std;

StringTree::StringTree(istream& input)
{

StringTree::constructor(root, input); 

}

void StringTree::constructor(StringTreeNode*& curr, istream& input)
{  
  string s; 
  if(getline(input, s))
  {
    curr = new StringTreeNode(s.substr(3));
    if(s[0] == 'I')
    {                                                                  
      StringTree::constructor(curr->left, input);
      StringTree::constructor(curr->right, input);
    }
  }else{
    curr = nullptr;
  }
}

void StringTree::serialize(ostream& output) {
    serializeHelper(root, output);
}

void StringTree::serializeHelper(StringTreeNode* curr, ostream& output) {
    if (curr == nullptr) {
        return; // Skip outputting "N\n" for null nodes
    }
    output << (curr->left || curr->right ? "I: " : "L: ") << curr->data << "\n";
    serializeHelper(curr->left, output);
    serializeHelper(curr->right, output);
}

StringTree::~StringTree() {
    destructorHelper(root);
}

void StringTree::destructorHelper(StringTreeNode* curr) {
    if (curr == nullptr) return;
    destructorHelper(curr->left);
    destructorHelper(curr->right);
    delete curr;
}