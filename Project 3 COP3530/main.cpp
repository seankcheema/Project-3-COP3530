#include <iostream>
#include "Splay.h"

int main() {
    int numCommand, cmd, count = 0;
    unsigned int followers;
    string line, tempNum, username, password;
    getline(cin, tempNum);
    numCommand = stoi(tempNum);
    tempNum = "";

    Splay splayTree;
    // RED BLACK TREE OBJECT

    for(int i = 0; i<numCommand; i++){ // iterate through commands
        getline(cin, line);
        for(char i : line){ // iterate through line for user, pass, and follow
            if(i == ' '){
                count++;
                continue;
            }
            if(count == 0) {
                username += i;
            }
            if(count == 1){
                password += i;
            }
            else{
                tempNum += i;
            }
        }
        followers = stoi(tempNum);
        splayTree.insert(splayTree.getRoot(), username, password, followers);
        // RED BLACK TREE INSERT
        username = "";
        password = "";
        tempNum = "";
    }
    bool stayInLoop = true;
    while(stayInLoop){
        cout << "\nCommands: \n1) Insert\n2) Remove\n3) Search\n4) Exit Program\n";
        cin >> cmd;
        switch(cmd){
            case 1:
                cout << "\n-----INSERT-----\n";
                cout << "Username: ";
                cin >> username;
                cout << "\nPassword: ";
                cin >> password;
                cout << "\nFollowers: ";
                cin >> followers;
                splayTree.insert(splayTree.getRoot(), username, password, followers);
                // RED BLACK TREE INSERT
                break;

            case 2:
                cout << "\n-----REMOVE-----\n";
                cout << "Username: ";
                cin >> username;
                splayTree.remove(splayTree.getRoot(), username); // returns null or node (not sure what we want to do with this as far as printing)
                // RED BLACK TREE SEARCH
                break;
            case 3:
                cout << "\n-----SEARCH-----\n";
                cout << "Username: ";
                cin >> username;
                splayTree.search(username); // returns null or node (not sure what we want to do with this as far as printing)
                // RED BLACK TREE SEARCH
                break;
            case 4:
                cout << "\nGoodbye!";
                stayInLoop = false;
                break;
        }
    }
    return 0;
}
