#include <iostream>
using namespace std;
#include<vector>

struct Node{
    int data, height;
    Node *left, *right;
    Node(int d){
        data = d;
        height = 1;
        left = right = nullptr;
    }
};

class AVLTree{
    Node* root;

    int height(Node* node){
        if(node==nullptr) return 0;
        return node->height;
    }

    int balanceFactor(Node* node){
        if(node==nullptr) return 0;
        return height(node->left)-height(node->right);
    }

    Node* rightRotate(Node* y){
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    Node* leftRotate(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    Node* insert(Node* node, int data){
        if (!node) return new Node(data);

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        //left left
        if (balance >1 && data <node->left->data)
            return rightRotate(node);

        //right right
        if (balance< -1 && data> node->right->data)
            return leftRotate(node);

        //Left right
        if (balance>1 && data >node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //right Left
        if (balance <-1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node* node, vector<int>& arr) {
        if (!node) return;
        inorder(node->left, arr);
        arr.push_back(node->data);
        inorder(node->right, arr);
    }

public:
    AVLTree(){root = nullptr;}

    void insertValue(int data){
        root = insert(root, data);
    }

    void display(){
        vector<int> arr;
        inorder(root, arr);
        cout << endl;
    }
    void kthSmallest(int k) {
        vector<int> arr;
        inorder(root, arr);
        if (k <= 0 || k > arr.size()) {
            cout << "invalid" << endl;
            return;
        }
        cout<<k<<"th smallest: "<<arr[k-1]<<endl;
    }

    void kthLargest(int k) {
        vector<int> arr;
        inorder(root, arr);
        int n = arr.size();
        if (k <= 0 || k > n) {
            cout << "invalid"<<endl;
            return;
        }
        cout <<k<<"th largest: "<<arr[n-k]<<endl;
    }

    void printRootHeights() {
        if (!root) {
            cout << "Tree is empty!" << endl;
            return;
        }
        int leftH = height(root->left);
        int rightH = height(root->right);
        cout<<"Left height of root: "<<leftH<<endl;
        cout<<"Right height of root: "<<rightH<<endl;
    }
};

int main() {
    AVLTree t;
    t.insertValue(10);
    t.insertValue(5);
    t.insertValue(15);
    t.insertValue(3);
    t.insertValue(7);

    t.display();

    t.printRootHeights();
    t.kthLargest(3);
    t.kthSmallest(2);

    return 0;
}
