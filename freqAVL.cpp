//
// Zübeyr Furkan Eryýlmaz
// 09.12.2015
// 21202676 CS202-01
//

#include "freqAVL.h"

TreeNode::TreeNode()
{
    this->count = 0;
    this->item = "-";
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
}

TreeNode::TreeNode(string newWord)
{
    this->count = 0;
    this->item = newWord;
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
}

freqAVL::freqAVL()
{
    root = NULL;
}

freqAVL::~freqAVL()
{

}

int freqAVL::getBalance( TreeNode *node)
{
    return getHeight(node->rightChildPtr) - getHeight(node->leftChildPtr);
}

int freqAVL::getHeight( TreeNode *node)
{
    if ( node != NULL)
    {
        return 1 + max(getHeight(node->leftChildPtr),getHeight(node->rightChildPtr));
    }

    return 0;
}

void freqAVL::rotateRight( TreeNode *node)
{
    temp = node->leftChildPtr;
    node->leftChildPtr = temp->rightChildPtr;
    temp->rightChildPtr = node;

    node = temp;
    temp = NULL;
}

void freqAVL::rotateLeft( TreeNode *node)
{
    temp = node->rightChildPtr;
    node->rightChildPtr = temp->leftChildPtr;
    temp->leftChildPtr = node;

    node = temp;
    temp = NULL;
}

void freqAVL::balance(TreeNode *node)
{
    if (getBalance(node) > 1)
    {
        if (getBalance(node->rightChildPtr) < 0)
        {
            rotateRight(node->rightChildPtr);
            rotateLeft(node);
        }
        else
        {
            rotateRight(node);
        }
    }

    else if (getBalance(node) < -1) {
        if (getBalance(node->leftChildPtr) > 0) {
            rotateLeft(node->leftChildPtr);
            rotateRight(node);
        }
        else {
            rotateLeft(node);
        }
    }

}

void freqAVL::addWord(string newWord, TreeNode node)
{
    if( node == NULL)
    {
        node = new Treenode(newWord);
    }

    else
    {
        if ( newWord.compare(node->item) > 0)
        {
            addWord(newWord,node->rightChildPtr);
            balance(node);
        }

        else if( newWord.compare(node->item) = 0)
        {
            node->count++;
        }

        else
        {
            addWord(newWord,node->rightChildPtr);
            balance(node);
        }

    }


}

void freqAVL::generateTree()
{
    
}

void freqAVL::printHeight()
{

}

void freqAVL::printTotalWordCount()
{

}

void freqAVL::printWordFrequencies()
{

}

void freqAVL::printMostFrequent()
{

}

void freqAVL::printLeastFrequent()
{

}

void freqAVL::printStandartDeviation()
{

}