//
// Created by skc32 on 12/4/2022.
//

#include "Splay.h"

Splay::Splay() { // default constructor
    root = nullptr;
}

Splay::~Splay() { // destructor
    deleteRecur(root);
}

void Splay::deleteRecur(Splay::Node *node) { // destructor helper function
    if(node != nullptr){
        deleteRecur(node->left);
        deleteRecur(node->right);
        node->username = "";
        node->password = "";
        node->followers = 0;
        delete node;
    }
}

Splay::Node *Splay::insert(Splay::Node *node, const string& username, const string& password, unsigned int followers) { // insert node
    if(node == nullptr){
        Node* newNode = new Node();
        newNode->username = username;
        newNode->password = password;
        newNode->followers = followers;
        newNode->left = nullptr;
        newNode->right = nullptr;
        if(root == nullptr) root = newNode;
        return newNode;
    }

    if(username < node->username) node->left = insert(node->left, username, password, followers);
    else if(username > node->username) node->right = insert(node->right, username, password, followers);
    else return node;

    root = splay(root, username);

    return node;
}

Splay::Node *Splay::remove(Splay::Node *node, const string& username) { // remove node
    Node* remove = search(username);
    Node* temp;
    if(remove == nullptr) return nullptr;

    root = splay(root, remove->username);

    if(root->left == nullptr){
        temp = root;
        root = root->right;
    }
    else{
        temp = root;
        node = splay(root->left, remove->username);
        root = node;
        root->right = temp->right;
    }

    delete temp;

    return root;
}

Splay::Node *Splay::search(const string& username) { // search by username. returns node if found, else nullptr
    Node* node = root;
    while(node != nullptr){
        if(username == node->username){
            root = splay(root, username); // splays when node is accessed
            return node;
        }
        else if(username > node->username && node->right != nullptr) node = node->right;
        else if(username < node->username && node->left != nullptr) node = node->left;
        else break;
    }
    return nullptr;
}

Splay::Node *Splay::splay(Splay::Node *r, string username) { // brings most recently accessed node to the top
    if(r == nullptr || r->username == username) {
        return r;
    }

    if(username < r->username){ // node is in left subtree
        if(r->left == nullptr) return r;

        if(username < r->left->username){ // Left Left Case
            r->left->left = splay(r->left->left, username);
            r = rightRot(r); // first rot
        }
        else if(username > r->left->username){ // Left Right Case
            r->left->right = splay(r->left->right, username);

            if(r->left->right != nullptr) r->left = leftRot(r->left); // first rot
        }

        if(r->left == nullptr) return r; // second rot
        else return rightRot(r);
    }
    else{ // node is in right subtree
        if(r->right == nullptr) return r;

        if(username < r->right->username){ // Right Left Case
            r->right->left = splay(root->right->left, username);

            if(r->right->left != nullptr) r->right = rightRot(r->right); // first rot
        }
        else if(username > r->right->username){
            r->right->right = splay(r->right->right, username);
            r = leftRot(r); // first rot
        }
        if(r->right == nullptr) return r;
        else leftRot(r); // second rot
    }
}

Splay::Node *Splay::getRoot() {
    return root;
}

Splay::Node *Splay::rightRot(Splay::Node *node) { // right rotation
    if(node == root){
        root = node->left;
    }
    Node* n1 = node->left;
    Node* n2 = n1->right;
    n1->right = node;
    node->left = n2;
    return n1;
}

Splay::Node *Splay::leftRot(Splay::Node *node) { // left rotation
    if(node == root){
        root = node->right;
    }
    Node* n1 = node->right;
    Node* n2 = n1->left;
    n1->left = node;
    node->right = n2;
    return n1;
}





