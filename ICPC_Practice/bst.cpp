
#include <iostream>

using namespace std;

struct Node {

    int val;
    Node* left;
    Node* right;
};

int insertIntoTree(Node* node, int targetVal, int currDepth) {
         
    //needs to go left
    if (targetVal < node->val){
        if (node->left == NULL){
            Node* newNode = new Node;
            newNode->val = targetVal;
            node->left = newNode;
            return currDepth + 1;
        }
        else {
            return insertIntoTree(node->left, targetVal, currDepth + 1);
        }
    }
    //needs to go right
    else {
        if (node->right == NULL){
            Node* newNode = new Node;
            newNode->val = targetVal;
            node->right = newNode;
            return currDepth + 1;
        }
        else {
            return insertIntoTree(node->right, targetVal, currDepth + 1);
        }

    }

}

int main() {

    int N;
    cin >> N;

    int C = 0;

    Node* root = new Node;
    int value;
    cin >> value;
    root->val = value;
    cout << 0 << endl;
    
    for(int i = 0; i < N - 1; i++) {
        int val;
        cin >> val;
        C += insertIntoTree(root, val, 0);
        cout << C << endl;
    }
    return 0;
}