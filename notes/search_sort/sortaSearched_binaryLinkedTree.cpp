#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class BST
{

	private:

	typedef struct Node_Struct
	{
		int data;
		struct Node_struct* left;
		struct Node_struct* right;
	}Node;

	Node* root; // The root node, a pointer to the first node


	public:

	BST() : root(nullptr) {} // Default constructor to initialize the variables
	
	Node* createNode(int data); // Member function definition

};

BST::Node* BST::createNode(int data) 
{
	Node* newNode = new Node;
	newNode->data = data;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

BST::void BST::write()
{
	
}