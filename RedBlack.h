//
// Created by benev on 12/4/2022.
//

#ifndef DSAPROJECT3_REDBLACK_H
#define DSAPROJECT3_REDBLACK_H
#include <string>
using namespace std;

class RedBlack {
private:
    class Node;
    Node* root = nullptr;
public:
    RedBlack();
    ~RedBlack();
    Node* insert(const string& username, const string& password, unsigned int followers);
    Node* insertHelper(Node* node, const string& username, const string& password, unsigned int followers);
    Node * remove(const string& username);
    Node* removeHelper(Node* node, const string& username);
    Node* search(const string& username);
    Node* searchRecur(Node* node, const string& username);
    Node* findParent(string & username);
    void deleteRecur(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);
    Node* balance(Node* node);
};

class RedBlack:: Node{
public:
    string username;
    string password;
    unsigned int followers;
    Node* left;
    Node* right;
    bool red;
    Node();
    Node(string cUsername, string cPassword, int cFollowers, bool cRed);
};

#endif //DSAPROJECT3_REDBLACK_H
