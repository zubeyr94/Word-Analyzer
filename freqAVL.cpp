//
// Zübeyr Furkan Eryýlmaz
// 09.12.2015
// 21202676 CS202-01
//

#include "freqAVL.h"
#include <cstdio>
#include <fstream>
#include "limits.h"
#include "math.h"

TreeNode::TreeNode()
{
    this->count = 0;
    this->item = "";
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

void freqAVL::rotateRight( TreeNode* &node)
{
    TreeNode *temp = node->leftChildPtr;
    node->leftChildPtr = temp->rightChildPtr;
    temp->rightChildPtr = node;

    node = temp;
    temp = NULL;
}

void freqAVL::rotateLeft( TreeNode* &node)
{
    TreeNode *temp = node->rightChildPtr;
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

void freqAVL::findWordCount( TreeNode *node, int &count)
{
    if(node != NULL)
    {
        findWordCount(node->leftChildPtr, count);
        count++;
        findWordCount(node->rightChildPtr, count);
    }
}

void freqAVL::findMostFrequent( TreeNode* node, string &item, int &count)
{
    if(node != NULL)
    {
        findMostFrequent(node->leftChildPtr, item, count);

        if (node->count > count)
        {
            count = node->count;
            item = node -> item;
        }

        findMostFrequent(node->rightChildPtr, item, count);
    }
}

void freqAVL::findLeastFrequent( TreeNode* node, string &item, int &count)
{
    if(node != NULL)
    {
        findLeastFrequent(node->leftChildPtr, item, count);

        if (node->count < count)
        {
            count = node->count;
            item = node -> item;
        }

        findLeastFrequent(node->rightChildPtr, item, count);
    }
}

void freqAVL::printInorder( TreeNode* node, ofstream &file)
{
    if( node != NULL)
    {
        printInorder(node->leftChildPtr, file);
        file << (node->item) << " " << (node->count) << "\n";
        printInorder(node->rightChildPtr, file);
    }

}

void freqAVL::totalFrequence(TreeNode* node, double &total)
{
    if( node != NULL)
    {
        totalFrequence(node->leftChildPtr, total);
        total = total + node->count;
        totalFrequence(node->rightChildPtr, total);
    }
}

void freqAVL::calculateSquareofDifferences(TreeNode* node, double average, double &squareDiff)
{
    if( node != NULL)
    {
        calculateSquareofDifferences(node->leftChildPtr, average, squareDiff);
        squareDiff = squareDiff + (average - node->count) * (average - node->count);
        calculateSquareofDifferences(node->rightChildPtr, average, squareDiff);
    }
}

void freqAVL::addWord(string newWord, TreeNode *node)
{
    if( node == NULL)
    {
        node = new TreeNode(newWord);
    }

    else
    {
        if ( newWord.compare(node->item) > 0)
        {
            addWord(newWord,node->rightChildPtr);
            balance(node);
        }

        else if( newWord.compare(node->item) == 0)
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

void freqAVL::generateTree(string fileName)
{
    //Read from file and add to tree one by one
    ifstream file;
    file.open(fileName.c_str());

    string word;
    bool strStarted;

    while (file >> word)
    {
        strStarted = false;
        int start = -1;
        int end = -1;

        for (int i = 0; i < word.length(); i++)
        {
            word[i] = tolower(word[i]);
        }

        for (int i = 0; i < word.length(); i++) // 65 90 97 122
        {
            if ( word[i] >= 97 && word[i] <= 122 && !strStarted)
            {
                strStarted = true;
                start = i;
            }

            else if( word[i] < 97 && word[i] > 122 && strStarted)
            {
                strStarted = false;
                end = i;

                addWord(word.substr(start,end),root);
            }
        }
    }
}

void freqAVL::printHeight()
{
    ofstream file;
    file.open ("statistics.txt");
    file << "Tree Height: " << getHeight(root) << "\n";
    file.close();
}

void freqAVL::printTotalWordCount()
{
    int count = 0;
    findWordCount( root, count);

    ofstream file;
    file.open ("statistics.txt");
    file << "Total Word Count: " << count << "\n";
    file.close();
}

void freqAVL::printWordFrequencies()
{
    ofstream file;
    file.open ("wordfreqs.txt");
    printInorder(root,file);
    file.close();
}

void freqAVL::printMostFrequent()
{
    int count = 0;
    string item = "";
    findMostFrequent( root, item, count);

    ofstream file;
    file.open ("statistics.txt");
    file << "Most Frequent: " << item << " " << count << "\n";
    file.close();
}

void freqAVL::printLeastFrequent()
{
    int count = INT_MAX;
    string item = "";
    findLeastFrequent( root, item, count);

    ofstream file;
    file.open ("statistics.txt");
    file << "Least Frequent: " << item << " " << count << "\n";
    file.close();
}

void freqAVL::printStandartDeviation()
{
    int count = 0;
    findWordCount( root, count);

    double total = 0;
    totalFrequence(root, total);

    double average = total/count;
    double squareDiff = 0;
    calculateSquareofDifferences(root, average, squareDiff);

    ofstream file;
    file.open ("statistics.txt");
    file << "Standart Deviation: " << (sqrt(squareDiff/count)) << "\n";
    file.close();
}