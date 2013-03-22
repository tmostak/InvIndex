#include "Rice.h"

Rice::Rice(): prevValue(0), v(0), offset(0) {};


void Rice::writeChunkToMem() {
    encodedData.push_back(v);
    offset = 0;
}


size_t Rice::size() {
    return (encodedData.size() - 1)  * 8 + offset; 
}


void Rice::writeQ(const int q) {
    for (int i = 0; i != q; ++i)
        writeBit(true);
    writeBit(false);
}

void Rice::writeR(const int r) {
    for (int b = remainderBits - 1; b >= 0; --b) 
        writeBit(r & (1 << b)); // will determine if bit in r is 0 or 1 and write accordingly
}
    

void Rice::riceEncode (const unsigned int *data, const size_t len, vector <unsigned char> &output, int &M) {
    if (M < 0)
        M = determineM(data, len);
    remainderBits = log2(M) - 1;
    for (size_t i = 0; i != len; ++i) {
        int diff = data[i] - prevValue;
        int q = diff / M; // quotient
        int r = diff - q*M; // remainder (faster than modulo?)
        // Now write out quotient in unary (q-length string of 1s and then 0)
        writeQ(q);
        writeR(r);
        prevValue = data[i];
    }
}

