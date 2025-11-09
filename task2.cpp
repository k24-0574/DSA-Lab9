#include <iostream>
using namespace std;

struct Node{
    int data, height;
    Node *left, *right;
    Node(int d) {
        data = d;
        height = 1;
        left = right = nullptr;
    }
};

class AVLTree{
    Node* root;

    int height(Node* node){
        return node ? node->height : 0;
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

    void inorder(Node* node){
        if (node==nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    AVLTree(){root = nullptr;}

    void insertValue(int data){
        root = insert(root, data);
    }

    void display(){
        inorder(root);
        cout << endl;
    }

    void rotateLeftAtRoot(){
        if (root)
            root = leftRotate(root);
    }
};

int main() {
    AVLTree t;
    t.insertValue(50);
    t.insertValue(30);
    t.insertValue(70);
    t.insertValue(20);
    t.insertValue(40);
    t.insertValue(60);
    t.insertValue(80);

    t.display();

    t.insertValue(55);
    cout << "After inserting 55: ";
    t.display();
    t.rotateLeftAtRoot();
    cout << "After left rotation on root: ";
    t.display();

    return 0;
}
