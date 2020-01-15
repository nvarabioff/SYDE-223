#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int new_key) : key(new_key), left(NULL), right(NULL) {}
};

BSTNode* sort(int start, int end, vector<int> vector_d) {
    if (start > end)
        return NULL;
    
    int mid = (start + end) / 2;
    
    BSTNode* Node = new BSTNode(vector_d[mid]);
    Node->left = sort(start, mid - 1, vector_d);
    Node->right = sort(mid + 1, end, vector_d);
    
    return Node;
}

BSTNode* create_minimal_BST(vector<int> vector_c, int length) {
    return sort(0, length-1, vector_c);
}

void print(BSTNode* N) {
    queue<BSTNode*> B;
    
    if (N) B.push(N);
    cout << "Start Breadth-First Traversal:" << endl;
    while (!B.empty()) {
        BSTNode *cur = B.front();
        cout << cur->key << " "; // visit the current node
        if (cur->left) B.push(cur->left); // enqueue left
        if (cur->right) B.push(cur->right); // enqueue right
        B.pop();
    }
    cout << endl;
}

int main () {
    int v[] = {1,3,5,7,9,11,13};
    vector<int> my_vec (v, v + sizeof(v) / sizeof(int));
    BSTNode* B = create_minimal_BST(my_vec, 7);
    print(B);
    return 0;
}

/* ANOTHER OPTION FOR int main() if this does not compile
int main () {
    vector<int> my_vec = {1,2,3,4,5,6,7};
    BSTNode* B = create_minimal_BST(my_vec, 7);
    print(B);
    return 0;
}
*/
