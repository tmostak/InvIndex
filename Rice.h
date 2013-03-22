#ifndef RICE_H
#define RICE_H

class Rice {

    private:
        vector <unsigned char> encodedData;
        unsigned int prevValue;
        int remainderBits;
        //unsigned char v;
        int offset;
        //size_t len;
        void Rice::writeChunkToMem();
        void writeQ(const int q); 
        inline void writeBit(const bool bit) {
            if (bit)
                encodedData.back() |= 1 << offset; // turn offset bit on 
            incOffset();
        }

            
        inline void Rice::incOffset() {
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
            

        inline int determineM(const unsigned int *data, const size_t len) { // actually get prob - assumes data is sorted
            unsigned int range = data[len-1] - data[0];
            float prob = float(range) / len;
            return determineM(prob);
        }
        
        Rice();
        size_t size();
        void riceEncode (const unsigned int *data, const size_t len, vector <unsigned char> &output, int &M = -1);
};










}

