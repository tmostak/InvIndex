#include <iostream>
#include "Rice.h"
#include <stdlib.h> // to generate random numbers
#include <ctime> // to seed random number generator

using namespace std;

inline float genRandFloat() { // generates rand float between 0.0 and 1.0, inclusive
    return (float)rand()/(float)RAND_MAX;
}

void genRandVec(const unsigned int maxRange, const float p, vector <unsigned int> &data) {
    data.reserve(int(maxRange * p + maxRange * 0.02)); // reserve the amount of space we expect to need up front (plus a little more to be safe)
    // p is probability of success in Bernouilli trial
    for (size_t i = 0; i != maxRange; i++) {
        if (p < genRandFloat()) // success
            data.push_back(i);
    }
}

int main () {
    srand (time (NULL) ):
    const unsigned int vecMax = 1000000;
   
    for (float p = 0.001; p != 0.05; p += 0.001) {
        vector <unsigned int> data;
        genRandVec(vecMax, p, data);
        Rice rice;
        rice.riceEncode(&data[0], data.size()); 
        int riceBits = rice.size();
        int origBits = data.size() * 32.0
        float ratio = origBits / float(riceBits);

        cout << p << ": " << riceBits << " " << origBits << " " << ratio <<   endl;
    }
}
