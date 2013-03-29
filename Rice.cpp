#include "Rice.h"
#include <iostream> 
using namespace std;

Rice::Rice(): prevValue(0), offset(0) {
    encodedData.push_back(0);
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
    
int Rice::determineMByMedian(const unsigned int *data, const size_t len) { // this is best when we aren't sure if data is randomly distributed
    float median;
    vector <unsigned int> diffs(len);
    diffs[0] = data[0]; 
    for (unsigned int d = 1; d != len; d++)
        diffs[d] = data[d] - data[d-1];
    std::sort(diffs.begin(),diffs.end());
    int index = (len-1)/2;
    if (len % 2 == 1) // if odd
        median = diffs[(len-1)/2];
    else // even
        median = (diffs[(len-1)/2] + diffs[len/2]) / 2.0;

    return determineM(1.0/median);
}

int Rice::riceEncode (const unsigned int *data, const size_t len, const int M, bool findMedianDelta) {
    int m;
    if (M < 0) {
        if (findMedianDelta)
            m = determineMByMedian(data, len);
        else
            m = determineMByProb(data, len);
    }
    else 
        m = M;

    if (m > 1)  {
        remainderBits = log2(m);
        encodedData.reserve(len*0.6); // just a rough rule of thumb
        // to do this fast we should prereserve a good guess on what encoded length
        // will be based on len and M
        for (size_t i = 0; i != len; ++i) {
            int diff = data[i] - prevValue;
            int q = diff / m; // quotient
            int r = diff - q*m; // remainder (faster than modulo?)
            // Now write out quotient in unary (q-length string of 1s and then 0)
            writeQ(q);
            writeR(r);
            prevValue = data[i];
        }
        return 0;
    }
    else
        return 1; // we didn't encode it
}

