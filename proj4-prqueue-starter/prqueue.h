#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue {
 public:
  struct NODE {
    int priority;
    T value;
    NODE* parent;
    NODE* left;
    NODE* right;
    NODE* link;  
  };

 private:
  NODE* root;
  size_t sz;

  // Utility pointers for begin and next.
  NODE* curr;
  NODE* temp; 

  // TODO_STUDENT: add private helper function definitions here

  NODE* copy(NODE* node, NODE* parent = nullptr) {
    if (!node) return nullptr;
    NODE* newNode = new NODE{node->priority, node->value, parent, nullptr, nullptr, nullptr};
    newNode->left = copy(node->left, newNode);
    newNode->right = copy(node->right, newNode);
    if (node->link) newNode->link = copy(node->link, nullptr);
    return newNode;
  }

  // Helper function to delete all nodes starting from a given node
  void deleteAllNodes(NODE* node)
  {
    if(node == nullptr) return;

    // Recursively delete left and right children
    deleteAllNodes(node->left);
    deleteAllNodes(node->right);
  
    NODE* current = node->link;
    while (current) {
      NODE* next = current->link;
      delete current;
      current = next;
    }
    delete node;
  }


  // Helper function to find the node with the smallest Priority in the tree
  NODE* findMin(NODE* node) const
  {
    if(node == nullptr)
    {
      return nullptr;
    }
    while(node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }


  // Helper function to remove the smallest node and adjust the tree structure.
  NODE* removeMin(NODE* node)
  {
    if(node == nullptr)
    {
      return nullptr;
    }
    if(node->left == nullptr)
    {
      NODE* rightChild = node->right;

      if(rightChild != nullptr)
      {
        rightChild->parent = node->parent;
      }

      delete node;  // Remove the node with the smallest priority
      return rightChild;
    }

    node->left = removeMin(node->left);
    return node;
  }


  // Helper to perform an in-order Traversal and build the string
  void traversalString(NODE* node, ostringstream& oss) const 
  {
    if(node == nullptr)
    {
      return;
    }

    traversalString(node->left, oss);
    oss << node->priority << " value: " << node->value << endl;

    NODE* linkNode = node->link;
    while (linkNode) {
      oss << linkNode->priority << " value: " << linkNode->value << endl;
      linkNode = linkNode->link;
    }

    traversalString(node->right, oss);
  }

  bool equality(NODE* node1, NODE* node2) const {
    // If both nodes are null, they are equal
    if (!node1 && !node2) return true;
    // If one node is null and the other is not, they are not equal
    if (!node1 || !node2) return false;

    // Check if the current nodes' priorities and values match
    if (node1->priority != node2->priority || node1->value != node2->value)
        return false;

    // Check if the linked lists are equal
    NODE* link1 = node1->link;
    NODE* link2 = node2->link;
    while (link1 && link2) {
        if (link1->priority != link2->priority || link1->value != link2->value)
            return false;
        link1 = link1->link;
        link2 = link2->link;
    }
    // The linked lists are equal if both are null at the same time
    if (link1 != link2) return false;

    // Recursively check left and right children
    return equality(node1->left, node2->left) && equality(node1->right, node2->right);
}

// Helper function to handle nodes that have a link
void handleNodeWithLink(NODE* minNode) {
    NODE* temp = minNode->link;
    minNode->value = temp->value;
    minNode->priority = temp->priority;
    minNode->link = temp->link;
    delete temp;  // Delete the linked node after copying its value
}

// Helper function to handle nodes that do not have a link
void handleNodeWithoutLink(NODE* minNode) {
    NODE* parent = minNode->parent;

    if (!minNode->left && !minNode->right) {
        removeLeafNode(minNode, parent);  // Remove the leaf node
    } else if (minNode->left && !minNode->right) {
        replaceWithLeftChild(minNode, parent);  // Replace node with its left child
    } else if (!minNode->left && minNode->right) {
        replaceWithRightChild(minNode, parent);  // Replace node with its right child
    } else {
        replaceWithInorderSuccessor(minNode);  // Replace node with its inorder successor
    }

    delete minNode;  // Delete the node after handling its removal or replacement
}

// Helper function to remove a leaf node
void removeLeafNode(NODE* minNode, NODE* parent) {
    if (!parent) {
        root = nullptr;  // If the node is the root, set root to null
    } else if (parent->left == minNode) {
        parent->left = nullptr;  // Disconnect the node from its parent
    } else {
        parent->right = nullptr;  // Disconnect the node from its parent
    }
}

// Helper function to replace a node with its left child
void replaceWithLeftChild(NODE* minNode, NODE* parent) {
    if (!parent) {
        root = minNode->left;  // If the node is the root, set the left child as root
    } else if (parent->left == minNode) {
        parent->left = minNode->left;  // Replace with the left child
    } else {
        parent->right = minNode->left;  // Replace with the left child
    }
    minNode->left->parent = parent;  // Update the parent of the left child
}

// Helper function to replace a node with its right child
void replaceWithRightChild(NODE* minNode, NODE* parent) {
    if (!parent) {
        root = minNode->right;  // If the node is the root, set the right child as root
    } else if (parent->left == minNode) {
        parent->left = minNode->right;  // Replace with the right child
    } else {
        parent->right = minNode->right;  // Replace with the right child
    }
    minNode->right->parent = parent;  // Update the parent of the right child
}

// Helper function to replace a node with its inorder successor
void replaceWithInorderSuccessor(NODE* minNode) {
    NODE* successor = findMin(minNode->right);  // Find the inorder successor

    minNode->priority = successor->priority;
    minNode->value = successor->value;

    if (successor->right) {
        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;  // Bypass the successor
        } else {
            successor->parent->right = successor->right;  // Bypass the successor
        }
        successor->right->parent = successor->parent;  // Update the parent of the right child
    } else {
        if (successor->parent->left == successor) {
            successor->parent->left = nullptr;  // Disconnect the successor
        } else {
            successor->parent->right = nullptr;  // Disconnect the successor
        }
    }

    delete successor;  // Delete the successor node
}

 public:


  /// Creates an empty `prqueue`.
  ///
  /// Runs in O(1).
  prqueue() : root(nullptr), sz(0) {}

  /// Returns the number of elements in the `prqueue`.
  ///
  /// Runs in O(1).
  size_t size() const 
  {
    return sz;
  }

  /// Returns a pointer to the root node of the BST.
  ///
  /// Used for testing the internal structure of the BST. Do not edit or
  /// change.
  ///
  /// Runs in O(1).
  NODE* getRoot() 
  {
    return root;
  }

  /// Adds `value` to the `prqueue` with the given `priority`.
  ///
  /// Uses the priority to determine the location in the underlying tree.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  void enqueue(T value, int priority) 
  {
    
    NODE* newNode = new NODE{priority, value, nullptr, nullptr, nullptr, nullptr};

    if(root == nullptr) // If the BST is empty, Then Create a Root Node
    {
      root = newNode;
      sz++;
      return;
    }

      NODE* current = root; // Current node is the Root NODE
      NODE* parent = nullptr; // The Parent of a Root NODE is nullptr

      while (current) {
      parent = current;
      if (priority < current->priority) {
        current = current->left;
      } else if (priority > current->priority) {
        current = current->right;
      } else {
        while (current->link) {
          current = current->link;
        }
        current->link = newNode;
        sz++;
        return;
      }
    }

    newNode->parent = parent;
    if (priority < parent->priority) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
    sz++;
  }

  /// Returns the value with the smallest priority in the `prqueue`, but does
  /// not modify the `prqueue`.
  ///
  /// If the `prqueue` is empty, returns the default value for `T`.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  T peek() const 
  {
    if(root == nullptr)
    {
      return T{};
    }
    return findMin(root)->value;
  }

  /// Returns the value with the smallest priority in the `prqueue` and
  /// removes it from the `prqueue`.
  ///
  /// If the `prqueue` is empty, returns the default value for `T`.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  T dequeue() 
  {
    if (!root) return T{};  // If the tree is empty, return a default value

    NODE* minNode = findMin(root);  // Find the minimum node in the tree
    T minValue = minNode->value;  // Store the value of the min node

    if (minNode->link) {
        handleNodeWithLink(minNode);  // Handle the case where the node has a link
    } else {
        handleNodeWithoutLink(minNode);  // Handle the case where the node does not have a link
    }

    sz--;  // Decrease the size of the tree
    return minValue;  // Return the value of the dequeued node
  }

  /// Converts the `prqueue` to a string representation, with the values
  /// in-order by priority.
  ///
  /// Example:
  ///
  /// ```c++
  /// prqueue<string> names;
  /// names.enqueue("Gwen", 3);
  /// names.enqueue("Jen", 2);
  /// names.enqueue("Ben", 1);
  /// names.enqueue("Sven", 2);
  /// ```
  ///
  /// Calling `names.as_string()` would return the following multi-line
  /// string:
  ///
  /// ```text
  /// 1 value: Ben
  /// 2 value: Jen
  /// 2 value: Sven
  /// 3 value: Gwen
  /// ```
  ///
  /// Runs in O(N), where N is the number of values.
  string as_string() const 
  {
    ostringstream oss;
    traversalString(root, oss);
    return oss.str();
  }

  /// Empties the `prqueue`, freeing all memory it controls.
  ///
  /// Runs in O(N), where N is the number of values.
  void clear() {
    deleteAllNodes(root); // Call helper function do delete all nodes
    // Reset all values, since BST is now empty.
    root = nullptr;
    sz = 0;
  }

  /// Destructor, cleans up all memory associated with `prqueue`.
  ///
  /// Runs in O(N), where N is the number of values.
  ~prqueue() {
    clear();
  }

  /// Copy constructor.
  ///
  /// Copies the value-priority pairs from the provided `prqueue`.
  /// The internal tree structure must be copied exactly.
  ///
  /// Runs in O(N), where N is the number of values in `other`.
  prqueue(const prqueue& other) : root(nullptr), sz(0), curr(nullptr) {
    root = copy(other.root);
    sz = other.sz;
  }

  /// Assignment operator; `operator=`.
  ///
  /// Clears `this` tree, and copies the value-priority pairs from the
  /// provided `prqueue`. The internal tree structure must be copied exactly.
  ///
  /// Runs in O(N + O), where N is the number of values in `this`, and O is
  /// the number of values in `other`.
  prqueue& operator=(const prqueue& other) {
    if (this != &other) {
      clear();
      root = copy(other.root);
      sz = other.sz;
    }
    return *this;
  }

  /// Checks if the contents of `this` and `other` are equivalent.
  ///
  /// Two `prqueues` are equivalent if they have the same priorities and
  /// values, as well as the same internal tree structure.
  ///
  /// These two `prqueue`s would be considered equivalent, because
  /// they have the same internal tree structure:
  ///
  /// ```c++
  /// prqueue<string> a;
  /// a.enqueue("2", 2);
  /// a.enqueue("1", 1);
  /// a.enqueue("3", 3);
  /// ```
  ///
  /// and
  ///
  /// ```c++
  /// prqueue<string> b;
  /// a.enqueue("2", 2);
  /// a.enqueue("3", 3);
  /// a.enqueue("1", 1);
  /// ```
  ///
  /// While this `prqueue`, despite containing the same priority-value pairs,
  /// would not be considered equivalent, because the internal tree structure
  /// is different.
  ///
  /// ```c++
  /// prqueue<string> c;
  /// a.enqueue("1", 1);
  /// a.enqueue("2", 2);
  /// a.enqueue("3", 3);
  /// ```
  ///
  /// Runs in O(N) time, where N is the maximum number of nodes in
  /// either `prqueue`.
  ///
  bool operator==(const prqueue& other) const {
    return equality(root, other.root);
  }

  /// Resets internal state for an iterative inorder traversal.
  ///
  /// See `next` for usage details.
  ///
  /// O(H), where H is the maximum height of the tree.
  void begin() {

    if (!root) {
        curr = nullptr;
        temp = nullptr;
        return;
    }

    
    curr = root;
    while (curr->left) {
        curr = curr->left;
    }

    
    temp = curr;
  }

  /// Uses the internal state to return the next in-order value and priority
  /// by reference, and advances the internal state. Returns true if the
  /// reference parameters were set, and false otherwise.
  ///
  /// Example usage:
  ///
  /// ```c++
  /// pq.begin();
  /// T value;
  /// int priority;
  /// while (pq.next(value, priority)) {
  ///   cout << priority << " value: " << value << endl;
  /// }
  /// ```
  ///
  /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
  /// H is the height of the tree, and M is the number of duplicate
  /// priorities.
  bool next(T& value, int& priority) {

    if (!curr) return false; 

    if (temp != nullptr) {

      value = temp->value;
      priority = temp->priority;
    

      temp = temp->link;
      if (temp != nullptr) {
      
      }
      return true;
  }


    value = curr->value;
    priority = curr->priority;

  
    if (curr->right) {

      curr = curr->right;

      while (curr->left) {
        curr = curr->left; 
    }

      value = curr->value;
      priority = curr->priority;
      temp = curr->link; 
      return true;
    } else {
    
      NODE* parent = curr->parent;
      while (parent && curr == parent->right) {
        curr = parent;
        parent = parent->parent; 
      }

      curr = parent; 
      if (curr == nullptr) {
        return false; 
      }

      temp = curr->link; 
      value = curr->value;
      priority = curr->priority;
      return true;
    }
    return false;
    }
};
