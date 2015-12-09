//
// Zübeyr Furkan Eryýlmaz
// 09.12.2015
// 21202676 CS202-01
// Assignment 4
//

#include <iostream>
#include "freqAVL.h"

using namespace std;

int main( int argc, char* argv[]) {

    freqAVL avl;

    avl.generateTree(argv[1]);

    avl.printWordFrequencies();

    avl.printTotalWordCount();
    avl.printHeight();
    avl.printMostFrequent();
    avl.printLeastFrequent();
    avl.printStandartDeviation();

}