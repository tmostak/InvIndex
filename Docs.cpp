#include "Docs.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

Docs::Docs(const string &_fileName): fileName(_fileName){
    readFile();
}

int Docs::readFile() {
    ifstream inFile (fileName.c_str(), ios::in|ios::binary|ios::ate);
    if (!inFile.is_open())
        return 1;
    ifstream::pos_type fileSize;

    fileSize = inFile.tellg(); // in bytes
    rawMem = new unsigned int [fileSize / sizeof(unsigned int)];
    inFile.seekg(0,ios::beg);
    inFile.read((char *) rawMem,fileSize);
    numDocs = rawMem [0];
    offsets = rawMem + 1;
    data = rawMem + (numDocs + 1);

    //offsets = (unsigned int *) memBlock + sizeof(unsigned int);
    //data = (unsigned int *) memBlock + sizeof(unsigned int *) * (numDocs + 1);

    inFile.close();
}

void Docs::printDoc(const unsigned int docNum) {
    for (unsigned int featureNum = offsets[docNum]; featureNum != offsets[docNum+1]; featureNum++) {
        cout << data[featureNum] << " ";
        cout << endl;
    }
}

void Docs::getDoc(const unsigned int docNum, unsigned int * &dataPtr, size_t &dataSize) {
    dataPtr = data + offsets[docNum];
    dataSize = offsets[docNum + 1] - offsets[docNum]; 
}
    
Docs::~Docs() {
    delete [] rawMem;
}

