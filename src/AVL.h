
// C++ Program to print binary tree in 2D
#include <bits/stdc++.h>
#include <cctype>
using namespace std;
#define COUNT 10

// Created by Domenica Simbana on 10/2/2023.

#ifndef DSAPROJECT1_AVL_H
#define DSAPROJECT1_AVL_H

#endif //DSAPROJECT1_AVL_H


#include <string>
#include <iostream>
#include <vector>

using namespace std;


//creates a class for the nodes
class Node{
    string name;
    string UFid;
    Node* left;
    Node* right;

public:
    //getters
    string getName(){
        return name;
    }
    string getID(){
        return UFid;
    }
    Node* getRight(){
        return right;
    }
    Node* getLeft(){
        return left;
    }
    //setters
    void setRight(Node* node){
        right=node;
    }
    void setLeft(Node* node){
        left=node;
    }

    //constructs
    Node(){
        name="";
        UFid="";
        left=nullptr;
        right=nullptr;
    }
    Node(string nameStudent,string ID){
        name=nameStudent;
        UFid=ID;
        left=nullptr;
        right=nullptr;
    }
};

//creates a class for the binary tree as a whole
class AVLTree{
private:
    //the root of our tree
    Node* root;
    //keeps number of nodes in storage in order for the print traversals to identify the last node
    int numNodes;
    int copyNumNodes;
    //This code was derived from the code provided to us on Replit for Programming Quiz 4
    Node* InsertHelper(Node* node, string name, string UFid){
        if (node == nullptr){
            if(UFid.size()==8){
                int beforeCount=numNodes;
                node = new Node(name,UFid);
                numNodes++;
                copyNumNodes++;
                if(numNodes==beforeCount+1){
                    cout<<"successful"<<endl;
                }
                return node;
            }
            else{
                cout<<"unsuccessful"<<endl;
                return node;
            }
        }
        if (stoi(node->getID())== stoi(UFid) || UFid.size()!=8){
            cout<<"unsuccessful"<<endl;
            return node;
        }
        if (stoi(node->getID())> stoi(UFid)){
            node->setLeft(InsertHelper(node->getLeft(),name, UFid));
        }
        else{
            node->setRight(InsertHelper(node->getRight(),name, UFid));
        }
        node= AVLtreeConvert(node);
        return node;
    };

    //Code for rotateLeft, rotateRight, and rotateLeftRight were derived from the
    //Stepik question 5.1b
    Node* rotateLeft(Node *node)
    {
        Node* newRoot = node->getRight();
        node->setRight(newRoot->getLeft());
        newRoot->setLeft(node);
        return newRoot;
    }

    Node* rotateRight(Node *node)
    {
        Node* newRoot = node->getLeft();
        node->setLeft(newRoot->getRight());
        newRoot->setRight(node);
        return newRoot;

    }

    Node* rotateLeftRight(Node *node)
    {
        //your code here
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);

    }

    //It is the opposite of rotateLeftRight function
    Node* rotateRightLeft(Node *node)
    {
        //your code here
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    //the height of the tree which was derived from Steptik
    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return 1+ max(height(node->getLeft()),height(node->getRight()));
    }

    //Create a balanced tree
    Node* AVLtreeConvert(Node* node){
        int leftH= height(node->getLeft());
        int rightH= height(node->getRight());
        if(leftH-rightH==2){
            leftH= height(node->getLeft()->getLeft());
            rightH=height(node->getLeft()->getRight());
            if (leftH-rightH==1){
                return rotateRight(node);
            }
            else if(leftH-rightH==-1){
                return rotateLeftRight(node);
            }


        }
        else if(leftH-rightH==-2){
            leftH= height(node->getRight()->getLeft());
            rightH= height(node->getRight()->getRight());
            if (leftH-rightH==1){
                return rotateRightLeft(node);
            }
            else if(leftH-rightH==-1){
                return rotateLeft(node);
            }

        }
        return node;
    };

    //in order traversal that creates a vector filled of nodes// referenced 5.1c Balanced Trees from Spetik
    void inorderT(Node* node, vector<Node*>& nodeVec){
        if(node==nullptr){
            return;
        }
        inorderT(node->getLeft(),nodeVec);
        nodeVec.push_back(node);
        inorderT(node->getRight(),nodeVec);
    }


public:
    //constructors
    AVLTree(){
        root=nullptr;
        numNodes=0;
        copyNumNodes=0;
    }

    //getter for root
    Node* getRoot(){
        return root;
    }

    AVLTree(Node* root){
        this->root=root;
        numNodes=1;
        copyNumNodes=1;
    }

    int getHeight(){
        if(numNodes==0){
            return 0;
        }
        return height(root);
    }

    //level of tree
    void printLevelCount(){
        cout<<height(root)<<endl;
    }

    //insert a node into a binary tree// format seen on project overview video was used for inspiration on insert function
    //structure
    void Insert( string name, string UFid){
        //decide whether the name fits the qualifications
        //implemented find_first_not_of by learning from the example on cplusplus.com
        if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ")== string::npos){
            root= InsertHelper(root,name,UFid);
        }
        else{
            cout<<"unsuccessful"<<endl;
        }
    };

    //delete node based on the ID
    void removeID(string ID){
        //create a vector of nodes depending on the in order
        vector<Node*> vectorIn;
        inorderT(root,vectorIn);
        //create a node for the foundID and one for the parent of found ID

        Node* foundID=nullptr;
        Node* parentOfFound=nullptr;
        //finds the node for the foundID
        for(int i=0; i<int(vectorIn.size());i++){
            if(vectorIn[i]->getID()==ID){
                foundID=vectorIn[i];
                break;
            }
        }

        //finds the node for the parent of the found ID
        if(foundID!=nullptr && foundID!=root){
            //finds the parents of the found ID
            for(int i=0; i<int(vectorIn.size());i++){
                if(vectorIn[i]->getLeft()!=nullptr){
                    if((vectorIn[i]->getLeft()->getID())==ID){
                        parentOfFound=vectorIn[i];
                        break;
                    }
                }
                if(vectorIn[i]->getRight()!=nullptr){
                    if(vectorIn[i]->getRight()->getID()==ID){
                        parentOfFound=vectorIn[i];
                        break;
                    }
                }
            }
        }
        // if the ID was found
        if(foundID!=nullptr){
            // if it has one child
            if (foundID->getLeft()==nullptr && foundID->getRight()==nullptr){
                delete foundID;
                //what happens if it deletes the root and it was the only one
                if(foundID==root){
                    root=nullptr;
                }
                //compares the values of the IDs to see whether
                if(parentOfFound!= nullptr){
                    if(stoi(parentOfFound->getID())>stoi(ID)){
                        parentOfFound->setLeft(nullptr);
                    }
                    if(stoi(parentOfFound->getID())<stoi(ID)){
                        parentOfFound->setRight(nullptr);
                    }
                }
                numNodes--;
                copyNumNodes--;
                cout<<"successful"<<endl;
            }

                // if its child is on left
            else if (foundID->getRight()==nullptr){
                Node* replaceNode= foundID->getLeft();
                if(foundID==root){
                    root=replaceNode;
                }
                if(parentOfFound!= nullptr){
                    if(stoi(parentOfFound->getID())>stoi(foundID->getID())){
                        parentOfFound->setLeft(replaceNode);
                    }
                    if(stoi(parentOfFound->getID())<stoi(foundID->getID())){
                        parentOfFound->setRight(replaceNode);
                    }
                }
                delete foundID;
                numNodes--;
                copyNumNodes--;
                cout<<"successful"<<endl;
            }

                //if it has a child on the right
            else if(foundID->getLeft()==nullptr){
                Node* replaceNode= foundID->getRight();
                if(foundID==root){
                    root=replaceNode;
                }
                if(parentOfFound!= nullptr){
                    if(stoi(parentOfFound->getID())>stoi(foundID->getID())){
                        parentOfFound->setLeft(replaceNode);
                    }
                    if(stoi(parentOfFound->getID())<stoi(foundID->getID())){
                        parentOfFound->setRight(replaceNode);
                    }
                }
                delete foundID;
                numNodes--;
                copyNumNodes--;
                cout<<"successful"<<endl;
            }

                //if it has 2 children (successor method)
            else if(foundID->getLeft()!=nullptr && foundID->getRight()!=nullptr){
                //gets the least ID from the in order successor
                Node* parentReplace=foundID;
                Node* replaceNode= foundID->getRight();
                while(replaceNode->getLeft()!=nullptr){
                    parentReplace=replaceNode;
                    replaceNode=replaceNode->getLeft();
                }
                if(replaceNode==foundID->getRight()){
                    replaceNode->setLeft(foundID->getLeft());
                    if(foundID==root){
                        root=replaceNode;
                    }
                    delete foundID;
                }
                else{
                    replaceNode->setRight(foundID->getRight());
                    replaceNode->setLeft(foundID->getLeft());
                    parentReplace->setLeft(nullptr);
                    if(foundID==root){
                        root=replaceNode;
                    }
                }
                if(parentOfFound!=nullptr){
                    if(stoi(parentOfFound->getID())>stoi(foundID->getID())){
                        parentOfFound->setLeft(replaceNode);
                    }
                    if(stoi(parentOfFound->getID())<stoi(foundID->getID())){
                        parentOfFound->setRight(replaceNode);
                    }
                }
                numNodes--;
                copyNumNodes--;
                cout<<"successful"<<endl;
            }
        }
        else{
            cout<<"unsuccessful"<<endl;
        }

    };

    //remove N element in the in order form
    void removeInorder(int n){
        vector<Node*> inorderList;
        inorderT(root, inorderList);
        if(n<int(inorderList.size())){
            removeID(inorderList[n]->getID());
        }
        else{
            cout<<"unsuccessful"<<endl;
        }
    }

    //traverse to find ID
    void searchID(Node* node, string ID){
        vector<Node*> inorderList;
        Node* foundID=nullptr;
        inorderT(root, inorderList);
        for(int i=0; i<int(inorderList.size());i++){
            if(inorderList[i]->getID()==ID){
                cout<<inorderList[i]->getName()<<endl;
                foundID=inorderList[i];
                break;
            }
        }
        if(foundID==nullptr){
            cout<<"unsuccessful"<<endl;
        }
    };


    //traverse to find Name (how to print unsuccessful when there are multiple names that are the same
    void searchName(Node* node, string name){
        vector<Node*> inorderList;
        Node* foundID=nullptr;
        inorderT(root, inorderList);
        if(inorderList.size()!=0){
            for(int i=0; i<int(inorderList.size());i++){
                if(inorderList[i]->getName()==name){
                    cout<<inorderList[i]->getID()<<endl;
                    foundID=inorderList[i];
                }
            }
            if(foundID==nullptr){
                cout<<"unsuccessful"<<endl;
            }
        }
        else{
            cout<<"unsuccessful"<<endl;
        }

    };

    //in order
    void printInorder(Node* node) {
        if(copyNumNodes==0){
            cout<<""<<endl;
        }
        if (node == nullptr)
            return;
        printInorder(node->getLeft());
        if (copyNumNodes != 1) {
            cout << node->getName() << ", ";
            copyNumNodes--;
        } else {
            cout << node->getName()<<endl;
            copyNumNodes=numNodes;
        }
        printInorder(node->getRight());
    }

    //pre order
    void printPreorder(Node* node) {
        if(copyNumNodes==0){
            cout<<""<<endl;
        }
        if (node == nullptr)
            return;
        if (copyNumNodes != 1) {
            cout << node->getName() << ", ";
            copyNumNodes--;
        } else {
            cout << node->getName()<<endl;
            copyNumNodes=numNodes;
        }
        printPreorder(node->getLeft());
        printPreorder(node->getRight());
    }

    //postorder
    void printPostorder(Node* node) {
        if(copyNumNodes==0){
            cout<<""<<endl;
        }
        if (node == nullptr)
            return;
        printPostorder(node->getLeft());
        printPostorder(node->getRight());
        if (copyNumNodes != 1) {
            cout << node->getName() << ", ";
            copyNumNodes--;
        } else {
            cout << node->getName()<<endl;
            copyNumNodes=numNodes;
        }
    }
};
