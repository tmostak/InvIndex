#include <iostream>
#include "Docs.h"
#include "Rice.h"

using namespace std;
int main() {
    Docs docs("samplebins.dat");
    unsigned int numDocs = docs.getNumDocs();
    unsigned int unCompBits = 0;
    unsigned int compBits = 0;
    unsigned int numItems = 0;
    for (int i = 0; i != numDocs; ++i) {
        unsigned int *data;
        size_t dataSize;
        docs.getDoc(i, data, dataSize);
        if (dataSize > 1) { // doc 41762 is one with all empty tweets
            
            Rice rice;
            int status = rice.riceEncode(data, dataSize); // will find median by default
            if (status == 0) {
                unsigned int riceBits = rice.size();
                unsigned int origBits =dataSize * 32;

                float compRatio = origBits / float(riceBits);
                if (compRatio > 1.0) {
                    compBits += riceBits + 4;
                    unCompBits += origBits;
                    numItems += dataSize;
                }
            }
        }
    }
    float finalRatio = unCompBits / float(compBits);
    cout << "Total items: " << numItems << endl;
    cout << "Final Size: " << compBits << " " << finalRatio << endl;
    cout << "Reverse ratio: " << 1.0 / finalRatio << endl; 
}
