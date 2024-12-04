#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Node
{
	int data;
	struct Node* next;
};
 void linkedListTraversal(struct Node *ptr)
{
	while (ptr != NULL)
	{
		printf("Element: %d\n", ptr->data);
		ptr = ptr->next;
	}
}

int main()
{
	struct Node* head;
	struct Node* second;
	struct Node* third;

	// Allocate memory for nodes in the linked list in Heap
	head = (struct Node *)malloc(sizeof(struct Node));
	second = (struct Node *)malloc(sizeof(struct Node));
	third = (struct Node *)malloc(sizeof(struct Node));

	// Link first and second nodes.
	head->data = 7;
	head->next = second;

	// Link second and third nodes
	second->data = 11;
	second->next = third;

	// Terminate the list at the third node
	third->data = 66;
	third->next = NULL;

	linkedListTraversal(head);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Node
{
public:
	int data;
	Node* next;

	// Constructor to initialize data and next pointer
	Node(int data)
	{
		this->data = data;
		this->next = nullptr;
	}
};

void linkedListTraversal(Node* ptr)
{
	while (ptr != nullptr)
	{
		cout << "Element: " << ptr->data << endl;
		ptr = ptr->next;
	}
}

int main()
{
	Node* head = new Node(7);
	Node* second = new Node(11);
	Node* third = new Node(66);

	// Link the nodes
	head->next = second;
	second->next = third;

	linkedListTraversal(head);

	delete head;
	delete second;
	delete third;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
Example 

Write a function that, given the head of a sorted linked list,
Removes and destroys all duplicates such that each node value appears only once in the list.
Returns a pointer to the new head.

before:

Node* head -> 1 -> 1 -> 2 -> 3 -> 3 -> 3 -> nullptr

After:

Node* result -> 1 -> 2 -> 3 -> nullptr

return head;
*/


struct node 
{
	int val;
	node* next;
};

node* traverseLinkedList(node* head)
{
	node* current = head;

	while(current != nullptr && current->next != nullptr){
		if(current->val == current->next->val)
		{
			node* temp = current->next; // You just need to point at the next value
			current->next = current->next->next;
			delete temp;
			
		}else{
			current = current->next;
		}
	}
	return head;
}

int main(){

	// Later create a function to do all of This.
	node* head = new node;
	node* second = new node;
	node* third = new node;
	node* fourth = new node;
	node* fifth = new node;
	node* sixth = new node;

	head->val = 1;
	head->next = second;

	second->val = 1;
	second->next = third;

	third->val = 2;
	third->next = fourth;

	fourth->val = 3;
	fourth->next = fifth;

	fifth->val = 3;
	fifth->next = sixth;

	sixth->val = 3;
	sixth->next = nullptr;

	head = traverseLinkedList(head);

	node* current = head;
	while(current != nullptr)
	{
		cout << current->val << " -> ";
		current = current->next;
	}

	cout << "nullptr" << endl;

	// Free the memory used by the linked list 
	current = head;
	while(current != nullptr)
	{
		node* temp = current;
		current = current->next;
		delete temp;
	}



}