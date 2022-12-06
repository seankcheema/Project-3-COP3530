#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include "Splay.h"
#include "RedBlack.h"

int main() {
    int numCommand, cmd, count = 0;
    unsigned int followers;
    string line, tempNum, username, password;
    ifstream dataset("100dataset.txt");
    getline(dataset, tempNum);
    numCommand = stoi(tempNum);
    tempNum = "";
    vector<string> usernames;
    vector<string> passwords;
    vector<unsigned int> followerVec;

    Splay splayTree;
    RedBlack redBlackTree;

    for(int i = 0; i<numCommand; i++){ // iterate through commands
        getline(dataset, line);
        tempNum = "";
        for(char c : line){ // iterate through line for user, pass, and follow
            if(c == ' ' || c == '\0' || c == '\n'){
                count++;
                continue;
            }
            if(count == 0) {
                username += c;
            }
            else if(count == 1){
                password += c;
            }
            else{
                tempNum += c;
            }
        }

        followers = stoi(tempNum);
        usernames.push_back(username);
        passwords.push_back(password);
        followerVec.push_back(followers);
        username = "";
        password = "";
        tempNum = "";
        count = 0;
        //cout << i << "\n";
    }
    cout << "after for loop ";
    chrono::time_point<chrono::system_clock> start, end;

    start = chrono::system_clock::now();
    for(int i = 0; i<usernames.size(); i++){
        splayTree.insert(usernames.at(i), passwords.at(i), followerVec.at(i));
    }
    end = chrono::system_clock::now();
    cout <<"\nSplay Tree initial insertion time: " << (end-start).count() << "\n";

    start = chrono::system_clock::now();
    for(int i = 0; i<usernames.size(); i++){
        redBlackTree.insert(usernames.at(i), passwords.at(i), followerVec.at(i));
    }
    end = chrono::system_clock::now();
    cout <<"Red-Black Tree initial insertion time: " << (end-start).count() << "\n";



    bool stayInLoop = true;
    while(stayInLoop){
        cout << "\nCommands: \n1) Insert\n2) Remove\n3) Search\n4) Exit Program\n";
        int cmd2;
        cin >> cmd2;

        switch(cmd2){
            case 1:
                cout << "\n-----INSERT-----\n";
                cout << "Username: ";
                cin >> username;
                cout << "\nPassword: ";
                cin >> password;
                cout << "\nFollowers: ";
                cin >> followers;

                start = chrono::system_clock::now();
                splayTree.insert(username, password, followers);
                end = chrono::system_clock::now();
                cout <<"Splay Tree individual insertion time: " << (end-start).count() << "\n";

                cout << "\n" << splayTree.getRoot()->username << " has been inserted!\n";

                cout <<"Splay Tree individual insertion time: " << (end-start).count() << "\n";

                start = chrono::system_clock::now();
                redBlackTree.insert(username, password, followers);
                end = chrono::system_clock::now();
                cout <<"Red-Black Tree individual insertion time: " << (end-start).count() << "\n";
                break;
            case 2:
                cout << "\n-----REMOVE-----\n";
                cout << "Username: ";
                cin >> username;

                start = chrono::system_clock::now();
                splayTree.remove(username); // returns null or node (not sure what we want to do with this as far as printing)
                end = chrono::system_clock::now();
                cout <<"Splay Tree removal time: " << (end-start).count() << "\n";

                start = chrono::system_clock::now();
                redBlackTree.remove(username);
                end = chrono::system_clock::now();
                cout <<"Red-Black Tree removal time: " << (end-start).count() << "\n";
                break;
            case 3:
                cout << "\n-----SEARCH-----\n";
                cout << "Username: ";
                cin >> username;

                start = chrono::system_clock::now();
                if(splayTree.search(username) == nullptr) cout << "\nNot found\n"; // returns null or node (not sure what we want to do with this as far as printing)
                end = chrono::system_clock::now();
                cout <<"Splay Tree search time: " << (end-start).count() << "\n";

                start = chrono::system_clock::now();
                if(redBlackTree.search(username) == nullptr) cout << "\nNot found\n";
                end = chrono::system_clock::now();
                cout <<"Red-Black Tree search time: " << (end-start).count() << "\n";
                break;
            case 4:
                cout << "\nGoodbye!";
                stayInLoop = false;
                break;
        }

    }
    return 0;
}
