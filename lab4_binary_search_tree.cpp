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
	if (root == NULL)
		return TaskItem(-1, "N/A");
	TaskItem *temp = root;
	while (temp->right != NULL) {
		temp = temp->right;
	}
	//temp will be the furthest right node, which is the max
	return *temp;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (root == NULL)
		return TaskItem(-1, "N/A");
	TaskItem *temp = root;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	//temp will be the furthest left node, which is the min
	return *temp;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	return get_node_depth(root);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	//prints with breadth first traversal
	cout << "PRINTING BREADTH-FIRST TREE: " << endl;
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
	TaskItem *find = new TaskItem(val);	//node we are looking for
	TaskItem *temp = root;
	if (root == NULL) {	//obviously doesn't exist if root is null
		return false;
	} else if (find->priority == temp->priority) {	//if root is the one we're looking for
		return true;
	}
	while (temp->left || temp->right) {	//while current root is not a leaf node
		if (find->priority == temp->priority) {	//if current node is the one we're looking for
			return true;
		} else if (find->priority > temp->priority && temp->right) {	//if right child exists and k > kc, move to the right
			temp = temp->right;
		} else if (find->priority < temp->priority && temp->left) {		//if left child exists and k < kc, move to the left
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
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	if (n == NULL)	//if empty tree
        return -1;
    else {
        int leftD = get_node_depth(n->left);
        int rightD = get_node_depth(n->right);
        
        if (leftD > rightD)
            return (leftD + 1);
        else
            return (rightD + 1);
    }
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	TaskItem *temp = root;
	TaskItem *ins = new TaskItem(val);	//node we are inserting
	if (root == NULL) {	//if tree is empty, node goes to the root
		root = ins;
		size++;
		return true;
	}
	while (temp != NULL) {	
		if (ins->priority == temp->priority) {	//if node already exists in tree
			return false;
		} else if (ins->priority < temp->priority && temp->left) {	//if left child exists and k < kc, move to the left
			temp = temp->left;
		} else if (ins->priority > temp->priority && temp->right) {	//if right child exists and k > kc, move to the right
			temp = temp->right;
		} else {	//if no children exist in the required direction, exit the loop
			break;
		}
	}
	//temp will be the parent of the node to be inserted
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
	if (root == NULL) {	//if tree is empty, can't remove anything
		return false;
	}
	TaskItem *del = new TaskItem(val);	//node to be deleted
	TaskItem *tester = root;	//current node
	TaskItem *parent = root;	//current node's parent
	while (tester != NULL) {
		if (del->priority < tester->priority && tester->left) {
			parent = tester;
			tester = tester->left;
		} else if (del->priority > tester->priority && tester->right) {
			parent = tester;
			tester = tester->right;
		} else {	//if no child exists in the required direction, exit the loop
			break;
		}
	}
	//tester is the node that will be deleted
	//parent is the parent of tester node
	if (tester->priority != del->priority) {	//check to confirm the above statement
		return false;							//if false, the node to be removed doesn't exist
	}
	
	//CASE 1: Node being deleted is leaf node
	if (tester->left == NULL && tester->right == NULL) {
		//delete that node directly
		if (del->priority == root->priority) {	//check for root
			root = NULL;
		} else if (del->priority < parent->priority) {	//must change the parent's left/right pointer
			parent->left = NULL;
		} else if (del->priority > parent->priority) { //must change the parent's left/right pointer
			parent->right = NULL;
		}
		tester = NULL;
		delete del;
		del = NULL;
		parent = NULL;
		size--;
		return true;
	}
	
	//CASE 2: Node being deleted has one child
	//Create a temp pointer to the node being deleted
	//link the parent node to the child node
	//delete the node pointed to by the temporary pointer
	if (tester->left && tester->right == NULL) {	//if the one child is a left child
		if (del->priority == root->priority) {	//check root
			root = root->left; //root now points to its left child
		} else if (del->priority < parent->priority) {	
			parent->left = tester->left;	//bypasses tester, edits parent's left child
		} else if (del->priority > parent->priority) {
			parent->right = tester->left;	//bypasses tester, edits parent's right child
		}
		tester = NULL;
		delete del;
		del = NULL;
		parent = NULL;
		size--;
		return true;
	}
	else if (tester->right && tester->left == NULL) { //if the one child is a right child
		if (del->priority == root->priority) {	//check root
			root = root->right; //root now points to its right child
		} else if (del->priority < parent->priority) {
			parent->left = tester->right;	//bypasses tester, edits parent's left child
		} else if (del->priority > parent->priority) {
			parent->right = tester->right;	//bypasses tester edits parent's right child
		}
		tester = NULL;
		delete del;
		del = NULL;
		parent = NULL;
		size--;
		return true;	
	}
	
	
	//CASE 3: Node being deleted has 2 children
	//find min of right subtree, copy that value
	TaskItem *temp = tester->right; //tester is the root of right subtree
	while (temp->left != NULL) {
		temp = temp->left;
	}
	//temp now has the minimum value of right subtree
	
	//replace node to be deleted with that value
	//delete the node that you took the min value from
	if (del->priority == root->priority) {	//check root
		remove(*temp);	//recursively remove the min node, will have either 0 or 1 child
		root->priority = temp->priority;
		root->description = temp->description;
		size--;
		return true;
	} else if (del->priority < parent->priority) {
		remove(*temp);	//recursively remove the min node, will have either 0 or 1 child
		parent->left->priority = temp->priority;
		parent->left->description = temp->description;
		size--;
		return true;
	} else if (del->priority > parent->priority) {
		remove(*temp);	//recursively remove the min node, will have either 0 or 1 child
		parent->right->priority = temp->priority;
		parent->right->description = temp->description;
		size--;
		return true;
	}
		
}
