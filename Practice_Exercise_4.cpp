#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//EXERCISE 1:

struct BinaryTreeNode {
    int data; // value of the node
    BinaryTreeNode* left; // pointer to the left node
    BinaryTreeNode* right; // pointer to the right node
    BinaryTreeNode(int new_val) : data(new_val), left(NULL), right(NULL) {}
};

void find_and_print_sum_of_nodes(BinaryTreeNode* T, int desired_sum, int cur_sum, string buffer) {
    if (!T) return;
    
    int new_sum = cur_sum + T->data;
    
    string a;
    stringstream aa;
    aa << T->data;
    a = aa.str();
    
    string new_buffer = buffer + " " + a;
    
    if (new_sum == desired_sum)
        cout << new_buffer << endl;
    
    // down left subtree
    find_and_print_sum_of_nodes(T->left, desired_sum, new_sum, new_buffer);
    
    // down right subtree
    find_and_print_sum_of_nodes(T->right, desired_sum, new_sum, new_buffer);
    
    // restart from left subtree
    find_and_print_sum_of_nodes(T->left, desired_sum, cur_sum, buffer);
    
    // restart from right subtree
    find_and_print_sum_of_nodes(T->right, desired_sum, cur_sum, buffer);
    
}

// PURPOSE: Runs demonstrative tests
void test01() {
    BinaryTreeNode* root = new BinaryTreeNode(5);
    root->left = new BinaryTreeNode(3);
    root->right = new BinaryTreeNode(1);
    root->left->left = new BinaryTreeNode(-1);
    root->left->right = new BinaryTreeNode(8);
    root->right->right = new BinaryTreeNode(11);
    root->left->left->left = new BinaryTreeNode(18);
    root->left->right->left = new BinaryTreeNode(6);
    
    find_and_print_sum_of_nodes(root, 17, 0, " ");
    
    cout << endl << endl ;
}

void test02() {
    BinaryTreeNode* root = new BinaryTreeNode(0);
    root->left = new BinaryTreeNode(20);
    root->right = new BinaryTreeNode(22);
    root->left->left = new BinaryTreeNode(23);
    root->left->right = new BinaryTreeNode(5);
    root->right->left = new BinaryTreeNode(20);
    root->right->right = new BinaryTreeNode(-2);
    root->left->left->right = new BinaryTreeNode(-1);
    root->left->right->left = new BinaryTreeNode(37);
    root->right->left->right = new BinaryTreeNode(0);
    root->right->right->right = new BinaryTreeNode(7);
    
    find_and_print_sum_of_nodes(root, 42, 0, " ");
    
    cout << endl << endl;
}

void test03() {
    BinaryTreeNode* root = new BinaryTreeNode(1);
    root->left = new BinaryTreeNode(-2);
    root->right = new BinaryTreeNode(7);
    root->right->left = new BinaryTreeNode(0);
    root->right->right = new BinaryTreeNode(-9);
    root->right->left->right = new BinaryTreeNode(-1);
    
    find_and_print_sum_of_nodes(root, -1, 0, " ");
    
    cout << endl << endl;
}


//EXERCISE 2:

struct BTNode {
    int value;
    BTNode* left;
    BTNode* right;
    BTNode(int new_value) : value(new_value), left(NULL), right(NULL) {}
};

//PURPOSE: find non-cyclical path with maximum sum in given binary tree
int find_max_sum_of_nodes(BTNode *T, int &temp_max_sum) {
	//exit if T is NULL
	if (!T) return 0;
	
	//derive the maximum sum for the left subtree
	int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);
	
	//derive the maximum sum for the right subtree
	int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);
	
	//TODO: compare T->value, left_sum + T->value, and right_sum + T->value; store as max1
	int m = left_sum + T->value;
	if (right_sum + T->value > left_sum + T->value) {
		m = right_sum + T->value;
	}
	int max1 = T->value;
	if (m > T->value) {
		max1 = m;
	}
	
	//TODO: compare max1, left_sum + right_sum + T->value; store as max2
	int max2 = left_sum + right_sum + T->value;
	if (left_sum + right_sum + T->value < max1) {
		max2 = max1;
	}
	
	//TODO: update temp_max_sum with the new max
	if (max2 > temp_max_sum) {
		temp_max_sum = max2;
	}
	if (max1 > max2) {
		temp_max_sum = max1;
	}
	
	//TODO: return max1
	return max1;
}

int find_max_sum_of_nodes(BTNode *T) {
	int temp_max_sum = INT_MIN;
	find_max_sum_of_nodes(T, temp_max_sum);
	return temp_max_sum;
}

int test1() {
	BTNode *root = new BTNode(5);
	root->left = new BTNode(6);
	root->left->left = new BTNode(15);
	root->left->right = new BTNode(10);
	root->left->right->right = new BTNode(-5);
	root->right = new BTNode(-15);
	root->right->left = new BTNode(-12);
	root->right->right = new BTNode(9);
	
	int a = find_max_sum_of_nodes(root);
	return a;
}

int test2() {
	BTNode *root = new BTNode(6);
	root->left = new BTNode(10);
	root->left->right = new BTNode(-5);
	root->left->right->right = new BTNode(4);
	root->right = new BTNode(4);
	root->right->right = new BTNode(-6);
	root->right->right->right = new BTNode(7);
	
	int a = find_max_sum_of_nodes(root);
	return a;
}

int test3() {
	BTNode *root = new BTNode(1);
	root->left = new BTNode(-3);
	root->left->left = new BTNode(4);
	root->left->right = new BTNode(5);
	root->left->right->left = new BTNode(7);
	root->right = new BTNode(-1);
	root->right->left = new BTNode(2);
	root->right->right = new BTNode(-2);
	root->right->right->right = new BTNode(3);
	
	int a = find_max_sum_of_nodes(root);
	return a;
}

int test4() {
	BTNode *root = new BTNode(5);
	root->left = new BTNode(3);
	root->left->left = new BTNode(-1);
	root->left->left->left = new BTNode(18);
	root->left->right = new BTNode(8);
	root->left->right->right = new BTNode(6);
	root->right = new BTNode(1);
	root->right->right = new BTNode(11);
	
	int a = find_max_sum_of_nodes(root);
	return a;
}

int main() {
	cout << "EXERCISE 1: TESTS\n\n";
	
	test01();
	test02();
	test03();
	
	cout << "\nEXERCISE 2: TESTS\n\n";
	
	cout << "TEST 1: TREE A\n";
	cout << "MAX: " << test1() << endl;
	
	cout << "TEST 2: TREE B\n";
	cout << "MAX: " << test2() << endl;
	
	cout << "TEST 3: TREE C\n";
	cout << "MAX: " << test3() << endl;
	
	cout << "TEST 4: TREE D\n";
	cout << "MAX: " << test4() << endl;
	
	
}
