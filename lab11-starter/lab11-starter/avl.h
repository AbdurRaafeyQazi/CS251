#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

class Node {
 public:
  int data;
  int height;
  Node* left;
  Node* right;
};

class AVLTree {
  public:

    AVLTree();
    Node* root;
    int size;
    void insert(int value);
    string toString();
    int getSize();


  private: 
    void _insert(Node*& curr, int value);
    void _toString(Node* curr, ostringstream& oss, bool& isAVL, int& brokenValue, int& brokenHeight);
    int _max(int x, int y);
    int _getHeight(Node* n);
    int _getBalance(Node* n);
    void _leftRotate(Node*& n);
    void _rightRotate(Node*& n);
};

AVLTree::AVLTree() {
    this->root = nullptr;
    this->size = 0;
}

int AVLTree::getSize() {
    return this->size;
}

string AVLTree::toString() {
    // Returns the string representation of an 
    // inorder traversal of the tree.

    bool isAVL = true;
    int brokenValue = -1;
    int brokenHeight = 99999999;

    ostringstream oss("");
    oss << "Print format for each node ---> <data:height:balance>\n\n";

    _toString(this->root, oss, isAVL, brokenValue, brokenHeight);

    oss << "\n\n";
    if (isAVL) {
      oss << "Valid AVL Tree";
    }
    else {
      oss << "Invalid AVL Tree, broken at " << brokenValue;
    }

    return oss.str();
}

void AVLTree::_toString(Node* curr, ostringstream& oss, bool& isAVL, int& brokenValue, int& brokenHeight) {
    if (curr == nullptr) {
        return;
    }
    
    _toString(curr->left, oss, isAVL, brokenValue, brokenHeight);

    int balance = _getBalance(curr);
    if ((balance < -1 || balance > 1) && curr->height < brokenHeight) {
      isAVL = false;
      brokenValue = curr->data;
      brokenHeight = curr->height;
    }
    oss << curr->data << ":" << curr->height << ":" << balance << " ";

    _toString(curr->right, oss, isAVL, brokenValue, brokenHeight);
}

int AVLTree::_getHeight(Node* n) {
  if (n == nullptr) {
    return -1;
  }

  return n->height;
}

int AVLTree::_getBalance(Node* n) {
  if (n == nullptr) {
    return 0;
  }
  else {
    return _getHeight(n->left) - _getHeight(n->right);
  }
}

int AVLTree::_max(int x, int y) {
  return (x >= y ? x : y);
}
