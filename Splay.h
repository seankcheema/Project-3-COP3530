#include <string>

using namespace std;

class Splay {
    struct Node{
        string username;
        string password;
        unsigned int followers;
        Node* left;
        Node* right;
    };

    Node* root;

public:
    Splay();
    ~Splay();
    Node* insert(const string& username, const string& password, unsigned int followers);
    Node* remove(const string& username);
    Node* search(const string& username);
    Node* splay(Node* root, string username);
    void deleteRecur(Node* node);
    Node* getRoot();
    Node* rightRot(Node* node);
    Node* leftRot(Node* node);

};

