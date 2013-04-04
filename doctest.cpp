#include <iostream>
#include "Docs.h"
#include "Rice.h"

using namespace std;
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout <<"Usage: " << argv[0] << " <file-to-be-compressed1> <file-to-be-compressed2>...\n";
    }
    else {
        cout << endl; 
        for (int d = 1; d != argc; ++d) {
            Docs docs(argv[d]);
            unsigned int numDocs = docs.getNumDocs();
            docs.sortDocs();
            unsigned int unCompBits = 0;
            unsigned int compBits = 0;
            unsigned int numItems = 0;
            for (int i = 0; i != numDocs; ++i) {
                unsigned int *data;
                size_t dataSize;
                docs.getDoc(i, data, dataSize);
                //for (int s = 0; s != dataSize; s++)
                //    cout << data[s] << endl;
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
            cout << argv[d] << ": " << endl;
            cout << "Num docs: " << numDocs << endl;
            cout << "Total items: " << numItems << endl;
            cout << "Original size: " << numItems*4 << endl;
            cout << "Final Size: " << compBits / 8 << endl;
            cout << "Compression ratio: "<< finalRatio << endl;
            cout << "Size compressed/original: " << 1.0 / finalRatio << endl; 
            cout << "-------------------------------------------" << endl << endl;
        }
    }
}
