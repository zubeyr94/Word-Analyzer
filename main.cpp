//
// Zübeyr Furkan Eryýlmaz
// 09.12.2015
// 21202676 CS202-01
//

#include <iostream>
#include <fstream>
#include "freqAVL.h"

using namespace std;

int main() {

    freqAVL avl;

    avl.generateTree("Dubliners.txt");
    avl.printWordFrequencies();

}