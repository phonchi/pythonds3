#include <iostream>
#include <cstdlib>
using namespace std;

//creates a binary tree, allows you to insert nodes
// and access those nodes.
class BinaryTree {

    private:
    char key;
    BinaryTree *leftChild;  // reference other instances of the binary tree the BinaryTree class
    BinaryTree *rightChild; // reference other instances of the binary tree the BinaryTree class

    public: //constructor function expects to get some kind of object to store in the root
    BinaryTree(char rootObj){
        this->key = rootObj;
        this->leftChild = NULL;
        this->rightChild = NULL;
    }

    void insertLeft(char newNode){ // Handles insertion if there is no left child simply adds a node to the tree.
        if (this->leftChild == NULL){
        this->leftChild = new BinaryTree(newNode);
        }
        else { // handles insertion if there is a left child pushes the existing child down one level in the tree.
        BinaryTree *t = new BinaryTree(newNode);
        t->leftChild = this->leftChild;
        this->leftChild = t;
        }
    }

    void insertRight(char newNode){
        if (this->rightChild == NULL){
        this->rightChild = new BinaryTree(newNode);
        }
        else {
        BinaryTree *t = new BinaryTree(newNode);
        t->rightChild = this->rightChild;
        this->rightChild = t;
        }
    }

    BinaryTree *getRightChild(){ // accessor method
        return this->rightChild;
    }

    BinaryTree *getLeftChild(){ // accessor method
        return this->leftChild;
    }

    void setRootVal(char obj){ // accessor method
        this->key = obj;
    }

    char getRootVal(){ // accessor method
        return this->key;
    }
};