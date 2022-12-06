//
// Created by benev on 12/4/2022.
//
#include "RedBlack.h"

RedBlack::Node::Node() {
    username = "";
    password = "";
    followers = 0;
    left = nullptr;
    right = nullptr;
    red = false;
}
RedBlack::Node::Node(string cUsername, string cPassword, int cFollowers, bool cRed) {
    username = cUsername;
    password = cPassword;
    followers = cFollowers;
    left = nullptr;
    right = nullptr;
    red = false;
}
RedBlack:: Node* RedBlack::insert(const string &username, const string &password, unsigned int followers) {
    return insertHelper(root, username, password, followers);
}
RedBlack:: Node* RedBlack::insertHelper(Node *node, const string &username, const string &password, unsigned int followers) {
    if (node == nullptr){
        Node* newNode = new Node();
        newNode->username = username;
        newNode->password = password;
        newNode->followers = followers;
        newNode->left = nullptr;
        newNode->right = nullptr;
        if(root == nullptr) root = newNode;
        node = newNode;
    }
    else if (username < node->username){
        node->left = insertHelper(node->left,username,password,followers);
    }
    else if(username > node->username) {
        node->right = insertHelper(node->right, username, password, followers);
    }
    balance(node);

    return node;


}
RedBlack::Node* RedBlack::remove(const string &username) {
    return removeHelper(root, username);
}
RedBlack::Node *RedBlack::removeHelper(Node *node, const string &username) {
    Node * remove = search(username);
    Node* temp;
    if (remove == nullptr){
        return nullptr;
    }
    else if(node == nullptr){
        return nullptr;
    }
    else if (remove->left != nullptr && remove->right != nullptr){
        temp = remove->right;
        while(temp->left != nullptr){
            temp = temp->left;
        }
        remove->username = temp->username;
        remove->password = temp->password;
        remove->followers = temp->followers;
    }
    else if(remove->left != nullptr){
        remove->username = remove->left->username;
        remove->followers = remove->left->followers;
        remove->password = remove->left->password;
        delete remove->left;
        remove->left = nullptr;
    }
    else if(remove->right != nullptr){
        remove->username = remove->right->username;
        remove->followers = remove->right->followers;
        remove->password = remove->right->password;
        delete remove->right;
        remove->right = nullptr;
    }
    else{
        delete remove;
    }
    balance(node);
    return node;
}

RedBlack::Node *RedBlack::search(const string &username) {
    return searchRecur(root, username);
}

RedBlack::Node *RedBlack::searchRecur(Node* node, const string &username) {
    if(node->username == username){
        return node;
    }
    else if(username > node->username && node->right != nullptr){
        node = searchRecur(node->right, username);
    }
    else if(username < node->username && node->left != nullptr){
        node = searchRecur(node->left, username);
    }
    else {
        return nullptr;
    }

    return node;

}

RedBlack::Node *RedBlack::leftRotate(Node *node) {
    Node* parent = node->right;
    Node* newChild = node->right->left;
    parent->left = node;
    node->right = newChild;
    balance(node);
    return parent;
}

RedBlack::Node* RedBlack::rightRotate(Node *node) {
    Node* parent = node->left;
    Node* newChild = node->left->right;
    parent->left = node;
    node->right = newChild;
    return parent;
}

RedBlack:: Node* RedBlack::findParent(string &username) {
    if (root == nullptr){
        return nullptr;
    }
    Node* child = root;
    Node* parent = root;
    while(true){
        if (child == nullptr){
            return nullptr;
        }
        else if (child->username == username){
            return parent;
        }
        else{
            parent = child;
            if (child->username > username){
                child = child->left;
            }
            else{
                child = child->right;
            }
        }


    }
}

RedBlack::Node* RedBlack::balance(Node *node) {
    Node* parent = findParent(node->username);
    while(parent != nullptr && (parent->red) && node != root){
        Node* grandParent = findParent(parent->username);
        Node* uncle;
        if (parent == grandParent->right){
            uncle =grandParent->left;
            // if the uncle is red
            if (uncle->red) {
                uncle->red = false;
                parent->red = false;
                grandParent->red = true;
                node = grandParent;
            }
            else if (node == parent->right){
                node = parent;
                leftRotate(node);
            }
            parent = findParent(node->username);
            grandParent = findParent(parent->username);
            parent->red = false;
            grandParent->red = true;
            rightRotate(grandParent);
        }
        else{
            uncle = grandParent->right;
            if (uncle->red) {
                uncle->red = false;
                parent->red = false;
                grandParent->red = true;
                node = grandParent;
            }
            else if (node == parent->left){
                node = parent;
                rightRotate(node);
            }
            parent = findParent(node->username);
            grandParent = findParent(parent->username);
            parent->red = false;
            grandParent->red = true;
            leftRotate(grandParent);
        }
    }
    root->red = false;
    return node;
}

RedBlack::RedBlack() {
    root = nullptr;
}

RedBlack::~RedBlack() {
    deleteRecur(root);
}

void RedBlack::deleteRecur(RedBlack::Node *node) {
    if(node != nullptr){
        deleteRecur(node->left);
        deleteRecur(node->right);
        node->username = "";
        node->password = "";
        node->followers = 0;
        node->red = false;
        delete node;
    }
}

