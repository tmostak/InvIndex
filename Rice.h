#ifndef RICE_H
#define RICE_H

#include <vector>
#include <cstddef>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

class Rice {

    private:
        std::vector <unsigned char> encodedData;
        unsigned int prevValue;
        int remainderBits;
        int offset;
        void writeChunkToMem();
        void writeQ(const int q); 
        void writeR(const int r);
        inline void writeBit(const bool bit) {
            if (bit)
                encodedData.back() |= 1 << offset; // turn offset bit on 
            incOffset();
        }
        inline void incOffset() {
            offset++;
            if (offset == 8) {
                encodedData.push_back(0);
                offset = 0;
            }
        }

    public:
        inline int determineM(const float prob) { // will return appropriate rice M - must be power of 2
           return(pow(2,int(log2(-1.0/(log2(1.0-prob))))));
        }
            

        inline int determineMByProb(const unsigned int *data, const size_t len) { // actually get prob - assumes data is sorted
            unsigned int range = data[len-1] - data[0];
            float prob = len / float(range);
            return determineM(prob);
        }

        int determineMByMedian(const unsigned int *data, const size_t len); 
        Rice();
        size_t size();
        int riceEncode (const unsigned int *data, const size_t len, const int M = -1, const bool findMedianDelta = true);
};

#endif
