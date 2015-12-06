//
// Z�beyr Furkan Ery�lmaz
// 09.12.2015
// 21202676 CS202-01
//

#include <iostream>

using namespace std;

#ifndef ASSIGNMENT_4_FREQAVL_H
#define ASSIGNMENT_4_FREQAVL_H

class TreeNode {

    TreeNode();
    TreeNode(string newWord);

private:
    string item;
    int count;
    TreeNode *leftChildPtr, *rightChildPtr;

    friend class freqAVL;
};

class freqAVL {

private:
    TreeNode *root;

public:
    freqAVL();
    ~freqAVL();

    int getBalance( TreeNode *node);
    int getHeight( TreeNode *node);
    void rotateRight( TreeNode *node);
    void rotateLeft( TreeNode *node);
    void balance(TreeNode *node);

    void addWord(string newWord, TreeNode *node);
    void generateTree();
    void printHeight();
    void printTotalWordCount();
    void printWordFrequencies();
    void printMostFrequent();
    void printLeastFrequent();
    void printStandartDeviation();

};


#endif //ASSIGNMENT_4_FREQAVL_H
