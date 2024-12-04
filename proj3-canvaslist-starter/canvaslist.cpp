#include "canvaslist.h"

#include <iostream>

using namespace std;

// TODO_STUDENT

// Default constructor. Creates an empty CanvasList.
CanvasList::CanvasList() : list_size(0), list_front(nullptr) {}

  
CanvasList::CanvasList(const CanvasList& other)
{	

	// First set the default values for the member variables
	list_front = nullptr;
	list_size = 0;

	// If the other list is empty, return immediately
	if (other.list_front == nullptr)
	{
		return;
	}

	// Create a new node for the first element in the list
	list_front = new ShapeNode();
	list_front->value = other.list_front->value->copy();
	list_front->next = nullptr;

	// Set up pointers for traversal
	ShapeNode* current = list_front;
	ShapeNode* old = other.list_front->next;

	// Iterate through the remaining nodes in the other list
	while (old != nullptr)
	{
		// Create a new node for the current position
		current->next = new ShapeNode();
		current = current->next;
		current->value = old->value->copy();
		current->next = nullptr;

		// Move to the next node in the other list
		old = old->next;
	}

	// Copy the size of the list
	list_size = other.list_size;

}

// Assignment operator. Sets the current CanvasList to a deep copy of the given CanvasList.
CanvasList& CanvasList::operator=(const CanvasList& other) {

if (this == &other) {
        return *this; 
    }

    clear(); 

    if (other.list_front == nullptr) {
        return *this; // If the other list is empty
    }

    // Create the first node
    list_front = new ShapeNode; // Allocate new node
    list_front->value = other.list_front->value->copy(); // Copy the value
    list_front->next = nullptr; // Initialize next to nullptr

    ShapeNode* current_new = list_front; 
    ShapeNode* current_old = other.list_front->next; 

    // Copy the rest of the nodes
    while (current_old != nullptr) {
        current_new->next = new ShapeNode; 
        current_new->next->value = current_old->value->copy(); 
        current_new->next->next = nullptr; 
        current_new = current_new->next;
        current_old = current_old->next; 
    }

    list_size = other.list_size; // Copy the size

    return *this; // Return the current object

}
 
// Destructor. Clears all allocated memory.
CanvasList::~CanvasList() {
    clear();
}

// Empties the CanvasList, releasing all allocated memory.
void CanvasList::clear() {
    
	while(!empty())
	{
		Shape* shape = pop_front();
		delete shape;
	}

}

// Inserts the given Shape* as a new element in the CanvasList after the given index.
void CanvasList::insert_after(int index, Shape* shape) {

	if(index < 0 || index >= list_size)
	{
		return; // do nothing 
	}

	ShapeNode* current = list_front;
	for(int i = 0; i < index; ++i) // iterates untill reaches the end
	{
		current = current->next;
	}


	ShapeNode* new_node = new ShapeNode{shape, current->next}; // This will initialize the value member and the next member
	// new_node->value = shape
	// new_node->next = current->next
	current->next = new_node;
	list_size++;



}

// Adds the given Shape* to the front of the CanvasList.
void CanvasList::push_front(Shape* shape) {

	ShapeNode* new_node = new ShapeNode{shape, list_front};
	list_front = new_node;
	list_size++;
  
}

// Adds the given Shape* to the back of the CanvasList.
void CanvasList::push_back(Shape* shape) {
  ShapeNode* new_node = new ShapeNode{shape, nullptr};
	if(empty())
	{
		list_front = new_node;
	}else{
		ShapeNode* current = list_front;

		while(current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	list_size++;
}

// Remove and destroys the element at the specified index in this list.
void CanvasList::remove_at(int index) {
    if(index < 0 || index >= list_size) {
        return; // invalid index
    }

    if(index == 0) {
        Shape* shape = pop_front();
        delete shape; // Cleanup handled in pop_front
        return;
    }

    ShapeNode* current = list_front;
    // Traverse to the node just before the one we want to delete
    for(int i = 0; i < index - 1; ++i) {
        current = current->next;
    }

    ShapeNode* to_delete = current->next; // The node to be deleted
    current->next = to_delete->next; 
    delete to_delete->value; // Delete the Shape
    delete to_delete; // Delete the node itself
    list_size--;

}

// Remove and destroys every other element from the CanvasList, starting at index 1.
void CanvasList::remove_every_other() {
	int index = 1;
	ShapeNode* current = list_front;

	while(current && current->next)
	{
		remove_at(index);
		current = current->next;
		index++;
	}  
}

// Removes the element at the front of the CanvasList.
Shape* CanvasList::pop_front() {
   if(empty())
	 {
		return nullptr;
	 }

	 ShapeNode* old_front = list_front;
	 Shape* shape = old_front->value;

	 list_front = list_front->next;
	 delete old_front;
	 list_size--;
	 return shape;

}

// Removes the element at the back of the CanvasList.
Shape* CanvasList::pop_back() {

	// Check if the list is empty
    if (empty()) {
        return nullptr;
    }

    // If there's only one element, use pop_front
    if (list_size == 1) {
        return pop_front(); // pop_front will handle cleanup and size
    }

    // General case for more than one element
    ShapeNode* current = list_front;
    // Traverse to the second-to-last node
    while (current->next->next) {
        current = current->next;
    }

    // Current is now the second-to-last node
    Shape* shape = current->next->value; // Get the last node's value
    delete current->next; // Delete the last node
    current->next = nullptr; // Set the new end of the list
    list_size--; // Decrement the size
    return shape;
	

}

// Returns a pointer to the node at the front of the CanvasList.
ShapeNode* CanvasList::front() const {
  
	return list_front;

}

// Returns whether the CanvasList is empty.
bool CanvasList::empty() const {
  return list_size == 0;
}

// Returns the number of elements in the CanvasList.
int CanvasList::size() const {
  return list_size;
}


// Searches the CanvasList for the first Shape with the given x, y coordinate values.
int CanvasList::find(int x, int y) const {
    
	int index = 0;
	ShapeNode* current = list_front;

	while(current != nullptr)
	{
		if(current->value->getX() == x && current->value->getY() == y)
		{
			return index;
		}
		current = current->next;
		index++;
	}
	return -1; // not found

}

// Returns the Shape* at the given index in the CanvasList.
Shape* CanvasList::shape_at(int index) const {
  
	if(index < 0 || index >= list_size)
	{
		return nullptr; // invalid index 
	}

	ShapeNode* current = list_front;
	for(int i = 0; i < index; ++i)
	{
		current = current->next;
	}

	return current->value;

}

// For each Shape in the CanvasList, outputs its as_string.
void CanvasList::draw() const {
  ShapeNode* current = list_front;
	while(current != nullptr)
	{
		cout << current->value->as_string() << endl;
		current = current->next;
	}
}

// For each node in the CanvasList, prints the node's address and the node's shape's address.
void CanvasList::print_addresses() const {
  
	ShapeNode* current = list_front;
	while(current != nullptr)
	{
		cout << "Node Address: " << current << "\tShape Address: " << current->value << endl;
		current = current->next;
	}

}