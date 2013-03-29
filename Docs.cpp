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
    char *memBlock;
    ifstream::pos_type fileSize;

    fileSize = inFile.tellg(); // in bytes
    memBlock = new unsigned int [fileSize / 4];



    inFile.seekg(0,ios::beg);
    inFile.read(rawMem,fileSize);
    numDocs = rawMem [0];
    offsets = (unsigned int *) memBlock + sizeof(unsigned int);
    data = (unsigned int *) memBlock + sizeof(unsigned int *) * (numDocs + 1);

    inFile.close();
}

void Docs::printData() {
    cout << "# Docs: " << numDocs << endl;
    for (int i = 0; i != 10; i++) {
        cout << offsets[i] << endl;
    }
    for (int i = 0; i != 10; i++) {
        cout << *(data+i) << endl;
    }
}

Docs::~Docs() {
    delete [] data;
}

