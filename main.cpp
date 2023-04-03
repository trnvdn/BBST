#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

class BBST
{
private:
    Node* newNode(int data) {
        Node* node = new Node;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* node) {
        Node* leftChild = node->left;
        Node* rightChild = leftChild->right;
        leftChild->right = node;
        node->left = rightChild;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        leftChild->height = max(getHeight(leftChild->left), getHeight(leftChild->right)) + 1;
        return leftChild;
    }

    Node* rotateLeft(Node* node) {
        Node* rightChild = node->right;
        Node* leftChild = rightChild->left;
        rightChild->left = node;
        node->right = leftChild;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        rightChild->height = max(getHeight(rightChild->left), getHeight(rightChild->right)) + 1;
        return rightChild;
    }
    void preOrder(Node* root)
    {
        if (root != nullptr)
        {
            cout << root->data << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
    void inOrder(Node* root)
    {
        if (root != nullptr)
        {
            inOrder(root->left);
            cout << root->data << " ";
            inOrder(root->right);

        }
    }
    void postOrder(Node* root)
    {
        if (root != nullptr)
        {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->data << " ";
        }
    }
public:
    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return newNode(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        }
        else if (data > node->data) {
            node->right = insert(node->right, data);
        }
        else {
            return node;
        }
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalance(node);
        if (balance > 1 && data < node->left->data) {
            return rotateRight(node);
        }
        if (balance < -1 && data > node->right->data) {
            return rotateLeft(node);
        }
        if (balance > 1 && data > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && data < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* CopyBBST(Node* p)
    {
        if (p == NULL) {
            return NULL;
        }
        Node* newNode = p;
        newNode->height = p->height;
        newNode->left = CopyBBST(p->left);
        newNode->right = CopyBBST(p->right);
        return newNode;
    }

    void Print(Node* root)
    {
        cout<<"PreOrder:"<<endl;
        preOrder(root);
        cout<<endl;
        cout<<"InOrder:"<<endl;
        inOrder(root);
        cout<<endl;
        cout<<"PostOrder:"<<endl;
        postOrder(root);
        cout<<endl;
        cout<<endl;
        cout<<endl;
    }

};

int main() {
    BBST bbst;
    Node* root = nullptr;

    root = bbst.insert(root, 10);
    bbst.Print(root);
    root = bbst.insert(root, 20);
    bbst.Print(root);
    root = bbst.insert(root, 30);
    bbst.Print(root);
    root = bbst.insert(root, 40);
    bbst.Print(root);
    root = bbst.insert(root, 50);
    bbst.Print(root);
    root = bbst.insert(root, 25);
    bbst.Print(root);

    Node* copy = root;

    cout<<"Copy"<<endl;
    copy = bbst.CopyBBST(root);
    bbst.Print(copy);
    return 0;
}