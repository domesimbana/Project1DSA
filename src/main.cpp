#include <iostream>
#include "AVL.h"

int main() {
    AVLTree tree;
    string numCommand;
    getline(cin,numCommand);
    for(int i=0; i<stoi(numCommand);i++){
        string command;
        getline(cin,command);

        if(command.find(' ')!= string::npos){
            string nameCommand=command.substr(0,command.find(' '));
            string wOcommand=command.substr(command.find(' ')+1);
            if(wOcommand.find(' ')!= string::npos){
                if(nameCommand=="insert"){
                    string name=wOcommand.substr(0,wOcommand.find(' '));
                    string wOName=wOcommand.substr(wOcommand.find(' ')+1);
                    string UFid=wOName;
                    if(name.substr(0,1)=="\"" && name.substr(name.size()-1,1)=="\""){
                        name= name.substr(1,name.size()-2);
                        tree.Insert(name,UFid);
                    }
                    else{
                        cout<<"unsuccessful"<<endl;
                    }
                }
                else{
                    cout<<"unsuccessful"<<endl;
                }
            }
            else{
                string nameCommand=command.substr(0,command.find(' '));
                string wOcommand=command.substr(command.find(' ')+1);
                if(nameCommand=="remove"){
                    tree.removeID(wOcommand);
                }
                else if(nameCommand=="removeInorder"){
                    tree.removeInorder(stoi(wOcommand));
                }
                else if(nameCommand=="search"){
                    if(wOcommand.substr(0,1)=="\"" && wOcommand.substr(wOcommand.size()-1,1)=="\""){
                        string name= wOcommand.substr(1,wOcommand.size()-2);
                        tree.searchName(tree.getRoot(),name);
                    }
                    else{
                        tree.searchID(tree.getRoot(),wOcommand);
                    }

                }
                else{
                    cout<<"unsuccessful"<<endl;
                }
            }

        }
        else {
            if(command=="printInorder"){
                tree.printInorder(tree.getRoot());
            }
            else if(command=="printPostorder"){
                tree.printPostorder(tree.getRoot());
            }
            else if(command=="printPreorder"){
                tree.printPreorder(tree.getRoot());
            }
            else if(command=="printLevelCount"){
                tree.printLevelCount();
            }
            else{
                cout<<"unsuccessful"<<endl;
            }
        }
    }
    return 0;
}