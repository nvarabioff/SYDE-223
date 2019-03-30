#include <iostream>
#include <sstream>
#include <queue>

#include "lab4_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	delete root;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	//traverse to the right child of the root node, if a right child exists
	//at current node, if right child exists, traverse, otherwise, current node has highest key value
	TaskItem *temp = root;
	while (temp->right != NULL) {
		temp = temp->right;
	}
	return *temp;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	TaskItem *temp = root;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return *temp;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {	//NOT DONE - TEST7
	unsigned int h = 0;

	return h;
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	//prints with breadth first traversal
	if (root == NULL) {
      	cout << "";
    } else {
		std::stringstream ss;
		std::queue<BinarySearchTree::TaskItem*> node_queue;
		node_queue.push(root);
		while (!node_queue.empty()) {
			BinarySearchTree::TaskItem* cur_node = node_queue.front();
			node_queue.pop();
			ss << cur_node->priority << " ";
			if (cur_node->left) {
				node_queue.push(cur_node->left);
			}
			if (cur_node->right) {
				node_queue.push(cur_node->right);
			}
		}
	    
		std::string level_order_str = ss.str();
	
		cout << level_order_str.substr(0, level_order_str.size() - 1) << endl;
	}
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	TaskItem *find = new TaskItem(val);
	TaskItem *temp = root;
	if (root == NULL) {
		return false;
	} else if (find->priority == temp->priority) {
		return true;
	}
	while (temp->left || temp->right) {
		if (find->priority == temp->priority) {
			return true;
		} else if (find->priority > temp->priority && temp->right) {
			temp = temp->right;
		} else if (find->priority < temp->priority && temp->left) {
			temp = temp->left;
		} 
	}
	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {	//OPTIONAL - LATER
	TaskItem *temp = root;
	int count = 0;
	if (n == temp) {
		return count;
	} else {
		count++;
		
	}
	
	
	return count;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	TaskItem *temp = root;
	TaskItem *ins = new TaskItem(val);
	if (root == NULL) {
		root = ins;
		size++;
		return true;
	}
	while (temp != NULL) {
		if (ins->priority == temp->priority) {
			return false;
		} else if (ins->priority < temp->priority && temp->left != NULL) {
			temp = temp->left;
		} else if (ins->priority > temp->priority && temp->right != NULL) {
			temp = temp->right;
		} else {
			break;
		}
	}
	if (ins->priority < temp->priority) {
		temp->left = ins;
		size++;
		return true;
	} else if (ins->priority > temp->priority) {
		temp->right = ins;
		size++;
		return true;
	}
	return false;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	if (root == NULL) {
		return false;
	}
	TaskItem *del = new TaskItem(val);
	TaskItem *tester = root;
	TaskItem *parent = root;
	while (tester != NULL) {
		if (del->priority < tester->priority && tester->left != NULL) {
			parent = tester;
			tester = tester->left;
		} else if (del->priority > tester->priority && tester->right != NULL) {
			parent = tester;
			tester = tester->right;
		} else {
			break;
		}
	}
	//tester is the node that will be deleted
	if (tester->priority != del->priority) {
		return false;
	}
	//1. Node being deleted is leaf node
	if (tester->left == NULL && tester->right == NULL) {
		//delete that node directly
		size--;
		if (del->priority == root->priority) {
			root = NULL; //potential memory issues here
		} else if (del->priority < parent->priority) {
			parent->left = NULL;
		}
		else if (del->priority > parent->priority) {
			parent->right = NULL;
		}
		delete tester;
		//tester = NULL;
		//delete del;
		//delete parent;
		return true;
	}
	
	//2. Node being deleted has one child
	//Create a temp pointer to the node being deleted
	//link the parent node to the child node
	//delete the node pointed to by the temporary pointer
	if (tester->left != NULL && tester->right == NULL) {
		if (del->priority == root->priority) {
			root = root->left; //potential memory issues here
		} else if (del->priority < parent->priority) {
			parent->left = tester->left;
		} else if (del->priority > parent->priority) {
			parent->right = tester->left;
		}
		delete tester;
		//delete del;
		//delete parent;
		size--;
		return true;
	}
	else if (tester->right != NULL && tester->left == NULL) {
		if (del->priority == root->priority) {
			root = root->right; //potential memory issues here
		} else if (del->priority < parent->priority) {
			parent->left = tester->right;
		} else if (del->priority > parent->priority) {
			parent->right = tester->right;
		}
		delete tester;
		//delete del;
		//delete parent;
		size--;
		return true;	
	}
	//3. Node being deleted has 2 children
	//find min of right subtree, copy that value
	TaskItem *temp = tester->right; //tester is the root
	while (temp->left != NULL) {
		temp = temp->left;
	}
	//temp now has the minimum value
	
	//replace node to be deleted with that value
	//delete the node that you took the min value from
	if (del->priority == root->priority) {
		remove(*temp);
		root->priority = temp->priority;
		root->description = temp->description;
		size--;
		return true;
	} else if (del->priority < parent->priority) {
		remove(*temp);
		parent->left->priority = temp->priority;
		size--;
		return true;
	} else if (del->priority > parent->priority) {
		remove(*temp);
		parent->right->priority = temp->priority;
		size--;
		return true;
	}
		
}
