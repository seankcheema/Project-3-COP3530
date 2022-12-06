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
    root = insertHelper(root, username, password, followers);


}
RedBlack:: Node* RedBlack::insertHelper(Node *node, const string &username, const string &password,
                                        unsigned int followers) {
    if (node == nullptr){
        Node* newNode = new Node();
        newNode->username = username;
        newNode->password = password;
        newNode->followers = followers;
        newNode->left = nullptr;
        newNode->right = nullptr;
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
    root = removeHelper(root, username);

}
RedBlack::Node *RedBlack::removeHelper(Node *node, const string &username) {
    Node * remove = search(root, username);
    Node* temp;
    if (remove == nullptr){
        return nullptr;
    }

    if (remove->left != nullptr && remove->right != nullptr){
        temp = node->right;
        while(temp->left != nullptr){
            temp = temp->left;
        }
        remove->username = temp->username;
        remove->password = temp->password;
        remove->followers = temp->followers;
        remove->right = removeHelper(node->right, temp->username);
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
        remove = nullptr;
    }
    balance(node);
    return node;
}

RedBlack::Node *RedBlack::search(Node* node, const string &username) {
    if(node->username == username){
        return node;
    }
    else if(username > node->username){
        node = search(node->right, username);
    }
    else if(username < node->username){
        node = search(node->left, username);
    }
    else {
        return nullptr;
    }

}

RedBlack::Node *RedBlack::leftRotate(Node *node) {
    Node* parent = node->right;
    Node* newChild = node->right->left;
    parent->left = node;
    node->right = newChild;
    balance(node);
}

RedBlack::Node* RedBlack::rightRotate(Node *node) {
    Node* parent = node->left;
    Node* newChild = node->left->right;
    parent->left = node;
    node->right = newChild;
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
    while((parent->red) && node != root){
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
}