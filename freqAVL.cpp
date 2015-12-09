//
// Zübeyr Furkan Eryýlmaz
// 09.12.2015
// 21202676 CS202-01
// Assignment 4
//

#include "freqAVL.h"
#include "math.h"
#include <string.h>
#include <climits>

TreeNode::TreeNode()
{
    this->count = 0;
    this->item = "";
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
}

TreeNode::TreeNode(string newWord)
{
    this->count = 1;
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
{//Return height difference between right and left sub tree
    return getHeight(node->rightChildPtr) - getHeight(node->leftChildPtr);
}

int freqAVL::getHeight( TreeNode *node)
{//Return height
    if ( node != NULL)
    {
        return 1 + max(getHeight(node->leftChildPtr),getHeight(node->rightChildPtr));
    }

    return 0;
}

void freqAVL::rotateRight( TreeNode* &node)
{//Rotate AVL tree to right
    TreeNode *temp = node->leftChildPtr;
    node->leftChildPtr = temp->rightChildPtr;
    temp->rightChildPtr = node;

    node = temp;
    temp = NULL;
}

void freqAVL::rotateLeft( TreeNode* &node)
{//Rotate AVL tree to left
    TreeNode *temp = node->rightChildPtr;
    node->rightChildPtr = temp->leftChildPtr;
    temp->leftChildPtr = node;

    node = temp;
    temp = NULL;
}

void freqAVL::balance(TreeNode* &node)
{//Balance the AVL tree
 //Check balance factors of all nodes from leaf to root
 //and balance the tree accordingly
    if (getBalance(node) > 1)
    {
        if (getBalance(node->rightChildPtr) < 0)
        {
            rotateRight(node->rightChildPtr);
            rotateLeft(node);
        }
        else
        {
            rotateLeft(node);
        }
    }

    else if (getBalance(node) < -1) {

        if (getBalance(node->leftChildPtr) > 0)
        {
            rotateLeft(node->leftChildPtr);
            rotateRight(node);
        }
        else
        {
            rotateRight(node);
        }

    }

}

void freqAVL::findWordCount( TreeNode *node, long long &count)
{//Count word with an inorder traversal
    if(node != NULL)
    {
        findWordCount(node->leftChildPtr, count);
        count++;
        findWordCount(node->rightChildPtr, count);
    }
}

void freqAVL::findMostFrequent( TreeNode* node, string &item, int &count)
{//While inorder traversaling it compares and finds the most frequent word
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
{//While inorder traversaling it compares and finds the least frequent word
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
{//While inorder traversaling it prints the words and their frequencies
    if( node != NULL)
    {
        printInorder(node->leftChildPtr, file);
        file << (node->item) << " " << (node->count) << "\n";
        printInorder(node->rightChildPtr, file);
    }

}

void freqAVL::totalFrequence(TreeNode* node, double &total)
{//While inorder traversaling sum all the frequencies of the words
    if( node != NULL)
    {
        totalFrequence(node->leftChildPtr, total);
        total = total + node->count;
        totalFrequence(node->rightChildPtr, total);
    }
}

void freqAVL::calculateSquareofDifferences(TreeNode* node, double average, double &squareDiff)
{//While inorder traversaling it calculates sum of square of difference between average and each words frequency.
    if( node != NULL)
    {
        calculateSquareofDifferences(node->leftChildPtr, average, squareDiff);
        squareDiff = squareDiff + (average - node->count) * (average - node->count);
        calculateSquareofDifferences(node->rightChildPtr, average, squareDiff);
    }
}

void freqAVL::addWord(string newWord, TreeNode* &node)
{//Add given word to the AVL
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
            addWord(newWord,node->leftChildPtr);
            balance(node);
        }

    }


}

void freqAVL::generateTree(string fileName)
{//Read from file and add to tree one by one
    ifstream file;
    file.open(fileName.c_str());

    string words;
    bool strStarted;

    while (file >> words)
    {

        strStarted = false;
        int start = -1;
        int end = -1;

        //Change non-alphabetic characters with spaces and if it is a alphabetic character make it lowercase
        for (int i = 0; i < words.length(); i++)
        {

            if (isalpha(words[i]))
            {

                words[i] = tolower(words[i]);

            }

            else
            {
                words[i] = ' ';
            }
        }

        //Split the word according to spaces and add them to AVL
        char* newWord;

        char* wordsChar = new char[words.length() + 1];
        strcpy(wordsChar,words.c_str());

        newWord = strtok(wordsChar," ");
        while (newWord != NULL)
        {
            addWord(newWord,root);
            newWord = strtok (NULL, " ");
        }

    }
}

// These functions write the calculated data to the text files
void freqAVL::printHeight()
{
    ofstream file;
    file.open ("statistics.txt",file.app);
    file << "Tree Height: " << getHeight(root) << "\n";
    file.close();
}

void freqAVL::printTotalWordCount()
{
    long long count = 0;
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
    file.open ("statistics.txt",file.app);
    file << "Most Frequent: " << item << " " << count << "\n";
    file.close();
}

void freqAVL::printLeastFrequent()
{
    int count = INT_MAX;
    string item = "";
    findLeastFrequent( root, item, count);

    ofstream file;
    file.open ("statistics.txt",file.app);
    file << "Least Frequent: " << item << " " << count << "\n";
    file.close();
}

void freqAVL::printStandartDeviation()
{
    long long count = 0;
    findWordCount( root, count);

    double total = 0;
    totalFrequence(root, total);

    double average = total/count;
    double squareDiff = 0;
    calculateSquareofDifferences(root, average, squareDiff);

    ofstream file;
    file.open ("statistics.txt",file.app);
    file << "Standart Deviation: " << (sqrt(squareDiff/count)) << "\n";
    file.close();
}