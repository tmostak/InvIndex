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
    for (int i = 0; i != numDocs - 1; ++i) {
        //docs.printDoc(i);
        unsigned int *data;
        size_t dataSize;


        docs.getDoc(i, data, dataSize);
        //cout << "Doc " << i << " " << dataSize << endl;
        //if (i == 41762)
        //    docs.printDoc(i);
        if (dataSize > 2 && i != 41762) {
            
            Rice rice;
            rice.riceEncode(data, dataSize);
            unsigned int riceBits = rice.size();
            unsigned int origBits =dataSize * 32;

            float compRatio = origBits / float(riceBits);
            if (compRatio > 1.0) {
                compBits += riceBits + 4;
                unCompBits += origBits;
                numItems += dataSize;
            }
            //cout << "Size: " << dataSize << " " << compRatio << endl;
        }
    }
    float finalRatio = unCompBits / float(compBits);
    cout << "Total items: " << numItems << endl;
    cout << "Final Size: " << compBits << " " << finalRatio << endl;
    cout << "Reverse ratio: " << 1.0 / finalRatio << endl; 
}
