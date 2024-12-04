#include <string>
#include <fstream>

using namespace std;

class StringTreeNode {
  public:
  string data;
  StringTreeNode* left;
  StringTreeNode* right;

  StringTreeNode(string data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
  }
  StringTreeNode(string data, StringTreeNode* left, StringTreeNode* right) {
    this->data = data;
    this->left = left;
    this->right = right;
  }
};

class StringTree {
 public:
  StringTreeNode* root;

  StringTree(StringTreeNode* root) {
    this->root = root;
  }

  StringTree(istream& input);
  void serialize(ostream& output);
  ~StringTree();

 private:
  // TODO_STUDENT: declare recursive helpers for the...


  // - Constructor
  // - Serializer
  // - Destructor

  void constructor(StringTreeNode*& curr, istream& input);
  void serializeHelper(StringTreeNode* curr, ostream& output);
  void destructorHelper(StringTreeNode* curr);

};