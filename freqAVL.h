//
// Zübeyr Furkan Eryýlmaz
// 09.12.2015
// 21202676 CS202-01
//

#include <iostream>

using namespace std;

class TreeNode {

private:
    string item;
    int count;
    TreeNode *leftChildPtr, *rightChildPtr;

    friend class freqAVL;
};

#ifndef ASSIGNMENT_4_FREQAVL_H
#define ASSIGNMENT_4_FREQAVL_H


class freqAVL {

private:
    TreeNode *root;


public:
    freqAVL();
    ~freqAVL();

    void addWord();
    void generateTree();
    void printHeight();
    void printTotalWordCount();
    void printWordFrequencies();
    void printMostFrequent();
    void printLeastFrequent();
    void printStandartDeviation();

};


#endif //ASSIGNMENT_4_FREQAVL_H
