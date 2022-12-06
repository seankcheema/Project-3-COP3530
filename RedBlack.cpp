//
// Created by benev on 12/4/2022.
//
#include "RedBlack.h"

// default constructor
RedBlack::Node::Node() {
    username = "";
    password = "";
    followers = 0;
    left = nullptr;
    right = nullptr;
    // bool for color
    red = false;
}
// constructor for node with qualifications
RedBlack::Node::Node(string cUsername, string cPassword, int cFollowers, bool cRed) {
    username = cUsername;
    password = cPassword;
    followers = cFollowers;
    left = nullptr;
    right = nullptr;
    red = false;
}
// insert method
RedBlack:: Node* RedBlack::insert(const string &username, const string &password, unsigned int followers) {
    return insertHelper(root, username, password, followers);
}
// insert helper, recursively inserts node
RedBlack:: Node* RedBlack::insertHelper(Node *node, const string &username, const string &password, unsigned int followers) {
    // if current node is empty, inserts
    if (node == nullptr){
        Node* newNode = new Node();
        newNode->username = username;
        newNode->password = password;
        newNode->followers = followers;
        newNode->left = nullptr;
        newNode->right = nullptr;
        // if node is root, inserts at root
        if(root == nullptr) root = newNode;
        node = newNode;
    }
        // else if node username is less than username inserted, inserts to left
    else if (username < node->username){
        node->left = insertHelper(node->left,username,password,followers);
    }
        // else inserts to right
    else if(username > node->username) {
        node->right = insertHelper(node->right, username, password, followers);
    }
    // balances red black nodes
    balance(node);
    //returns final node
    return node;


}

// remove method
RedBlack::Node* RedBlack::remove(const string &username) {
    return removeHelper(root, username);
}

//remove recursive helper method
RedBlack::Node *RedBlack::removeHelper(Node *node, const string &username) {
    // node set by the search method
    Node * remove = search(username);
    Node* temp;
    // if node is not found, return null
    if (remove == nullptr){
        return nullptr;
    }
        // else if root is null return null
    else if(node == nullptr){
        return nullptr;
    }
        // else if username is found and node has two children
    else if (remove->left != nullptr && remove->right != nullptr){
        temp = remove->right;
        // inorder successor
        while(temp->left != nullptr){
            temp = temp->left;
        }
        // set node to inorder successor
        remove->username = temp->username;
        remove->password = temp->password;
        remove->followers = temp->followers;
    }
        // else if node has one left child
    else if(remove->left != nullptr){
        // change node to left and delete node
        remove->username = remove->left->username;
        remove->followers = remove->left->followers;
        remove->password = remove->left->password;
        delete remove->left;
        remove->left = nullptr;
    }
        // else right child, same but reversed
    else if(remove->right != nullptr){
        remove->username = remove->right->username;
        remove->followers = remove->right->followers;
        remove->password = remove->right->password;
        delete remove->right;
        remove->right = nullptr;
    }
        // else no children, deletes node
    else{
        delete remove;
    }
    // balances tree
    balance(node);
    // returns node
    return node;
}
// search method
RedBlack::Node *RedBlack::search(const string &username) {
    return searchRecur(root, username);
}
// search recursive helper
RedBlack::Node *RedBlack::searchRecur(Node* node, const string &username) {
    // if username is found , returns node
    if(node->username == username){
        return node;
    }
        // else searches to right is username is greater than current node
    else if(username > node->username && node->right != nullptr){
        node = searchRecur(node->right, username);
    }
        // else searches left
    else if(username < node->username && node->left != nullptr){
        node = searchRecur(node->left, username);
    }
        // else it is not found, returns nullptr
    else {
        return nullptr;
    }

    return node;

}
// rotates left
RedBlack::Node *RedBlack::leftRotate(Node *node) {
    Node* parent = node->right;
    Node* newChild = node->right->left;
    parent->left = node;
    node->right = newChild;
    return parent;
}
// rotates right
RedBlack::Node* RedBlack::rightRotate(Node *node) {
    Node* parent = node->left;
    Node* newChild = node->left->right;
    parent->left = node;
    node->right = newChild;
    return parent;
}
// finds parent for balancing
RedBlack:: Node* RedBlack::findParent(string &username) {
    // if root is null, returns null
    if (root == nullptr){
        return nullptr;
    }
    // otherwise iterates
    Node* child = root;
    Node* parent = root;
    while(true){
        // if child becomes null, return null
        if (child == nullptr){
            return nullptr;
        }
            // else if username is found, returns parent
        else if (child->username == username){
            return parent;
        }
            // else parent is set to child, child is moved based on direction of BST
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

// balancing method
RedBlack::Node* RedBlack::balance(Node *node) {
    // finds parent
    Node* parent = findParent(node->username);
    // while parent is red and node is not root
    while(parent != nullptr && (parent->red) && node != root){
        // find grandparent
        Node* grandParent = findParent(parent->username);
        Node* uncle;
        // if parent is a right child of grandparent
        if (parent == grandParent->right){
            // uncle node set to other node
            uncle =grandParent->left;
            // if the uncle is red
            if (uncle->red) {
                // sets uncle to black, parent to black, and grandparent to red
                uncle->red = false;
                parent->red = false;
                grandParent->red = true;
                node = grandParent;
            }
                // else if the node is a right child
            else if (node == parent->right){
                // node becomes parent, then is rotated left
                node = parent;
                leftRotate(node);
            }
            // parent is set back to initial parent
            parent = findParent(node->username);
            // grandparent set back to initial grandparent
            grandParent = findParent(parent->username);
            // parent set to black
            parent->red = false;
            // grandparent set to red
            grandParent->red = true;
            // grandparent rotated right
            rightRotate(grandParent);
        }
            // else parent is a left child, same process but reversed
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
    // root is made sure that it is black
    root->red = false;
    // returns node
    return node;
}

RedBlack::RedBlack() {
    root = nullptr;
}
// destructor
RedBlack::~RedBlack() {
    deleteRecur(root);
}
// recursive method for destructor
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