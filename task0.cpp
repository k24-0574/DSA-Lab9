#include <iostream>
using namespace std;

struct Node{
    Node* left, *right;
    int data, height;
    Node(int d){
        height = 1;
        data = d;
        right = left = nullptr;
    }
};

class Tree{
    Node* root;

    public:
    Tree(){root = nullptr; }

    private:
    Node* insert(Node* node, int data){
        if (node == nullptr) return new Node(data);
        if(data > node->data) node->right = insert(node->right, data);
        if(data < node->data) node->left = insert(node->left, data);
        node->height = 1+ max(height(node->left), height(node->right));

        return node;
    }
    int height(Node* node){
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(Node* node){
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* y){
       Node* x = y->left;
       Node* T2 = x->right;
        x->right = y;
        y->left = T2;

        y->height= 1+max(height(y->left), height(y->right));
        x->height=1+ max(height(x->left), height(x->right));
        return x;
    }
    Node* leftRotate(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;

        x->height= 1+max(height(x->left), height(x->right));
        y->height=1+ max(height(y->left), height(y->right));
        return y;
    }

    Node* bstTOavlFUNC(Node*node){
        if(node == nullptr) return node;
        node->left = bstTOavlFUNC(node->left);
        node->right = bstTOavlFUNC(node->right);
        node->height = 1+ max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        //left left
        if (balance>1 && balanceFactor(node->left) >= 0)
            return rightRotate(node);
        //right right
        if (balance < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node);
        //left right
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        //right left
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    void InorderTransversal(Node *node){
        if(node==nullptr ) return;

        InorderTransversal(node->left);
        cout<<node->data<<" ";
        InorderTransversal(node->right);
    }
    public:
    void insertBSTNODE(int data){
        root = insert(root, data);
    }

    void BSTtoAVL(){
        root =bstTOavlFUNC(root);
    }
    void inorder(){
        InorderTransversal(root);
    }
    
};

int main(){
    //As BST trees can become skewed and operaton(delete, search, insert, transversal) time complexity can become O(n)
    //AVL trees balance out the trees so the operation time complexity remains O(log(n)) 

    Tree A;
    A.insertBSTNODE(10);
    A.insertBSTNODE(16);
    A.insertBSTNODE(12);
    A.insertBSTNODE(18);
    A.inorder();
    cout<<endl;
    A.BSTtoAVL();
    A.inorder();

    return 0;
}
