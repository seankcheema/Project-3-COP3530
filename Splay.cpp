//
// Created by skc32 on 12/4/2022.
//
#include <iostream>
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

Splay::Node *Splay::insert(const string& username, const string& password, unsigned int followers) { // insert node
    if(root == nullptr){
        root = new Node();
        root->username = username;
        root->password = password;
        root->followers = followers;
        root->right = nullptr;
        root->left = nullptr;
        return root;
    }

    root = splay(root, username);

    if(root->username == username) return root;

    Node* newNode = new Node();
    newNode->username = username;
    newNode->password = password;
    newNode->followers = followers;
    newNode->right = nullptr;
    newNode->left = nullptr;

    if(root->username > username){
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    }
    else{
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }

    root = newNode;
    return newNode;

}

Splay::Node *Splay::remove(const string& username) { // remove node
    Node* remove = search(username);
    Node *temp = nullptr;
    if(remove == nullptr) return nullptr;
    cout << "Removed " << username << " with password " << remove->password << " and followers " << remove->followers << ".\n";

    if(root->left == nullptr && root->right == nullptr){
        root = nullptr;
    }
    else if(root->left == nullptr){
        temp = root;
        root = root->right;
    }
    else {
        temp = root;
        Node* max = root->left;
        while(max->right != nullptr) max = max->right;
        max = splay(root->left, max->username);
        root = max;
        root->right = temp->right;
    }

    delete temp;

    return root;
}

Splay::Node *Splay::search(const string& username) { // search by username. returns node if found, else nullptr
    Node* node = root;
    while(node != nullptr){
        if(username == node->username){
            cout << "Found " << username << " with password " << node->password << " and followers " << node->followers << ".\n";
            root = splay(root, username); // splays when node is accessed
            return root;
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
            r->right->left = splay(r->right->left, username);

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
    node->left = n1->right;
    n1->right = node;
    return n1;
}

Splay::Node *Splay::leftRot(Splay::Node *node) { // left rotation
    if(node == root){
        root = node->right;
    }
    Node* n1 = node->right;
    node->right = n1->left;
    n1->left = node;
    return n1;
}





