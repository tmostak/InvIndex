#include <iostream>
#include "Rice.h"
#include <stdlib.h> // to generate random numbers
#include <ctime> // to seed random number generator
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;

inline float genRandFloat() { // generates rand float between 0.0 and 1.0, inclusive
    return (float)rand()/(float)RAND_MAX;
}

void genRandVec(const unsigned int maxRange, const float p, vector <unsigned int> &data) {
    data.reserve(int(maxRange * p + maxRange * 0.02)); // reserve the amount of space we expect to need up front (plus a little more to be safe)
    // p is probability of success in Bernouilli trial
    for (size_t i = 0; i != maxRange; i++) {
        if (genRandFloat() < p) // success
            data.push_back(i);
    }
}

int main () {
    ofstream outFile ("rice_results_full_tiny.csv");
    srand (time (NULL) );
    const unsigned int vecMax = 10000000;
    const int numTrials = 10;
   
    for (float p = 0.00001; p <= 0.0001; p += 0.00001) {
        float compression = 0.0;
        float bitCompression = 0.0;
        for (int i = 0; i != numTrials; i++) {
            vector <unsigned int> data;
            genRandVec(vecMax, p, data);
            Rice rice;
            rice.riceEncode(&data[0], data.size()); 
            int riceBits = rice.size();
            //int riceBits = 1000;
            int origBits = data.size() * 32.0;
            float ratio = origBits / float(riceBits);
            float bitRatio = vecMax / float(riceBits);
            compression += ratio;
            bitCompression += bitRatio;
        }
        compression /= numTrials;
        bitCompression /= numTrials;
        outFile << boost::lexical_cast<string>(p) << "," << boost::lexical_cast<string>(compression) << "," << boost::lexical_cast <string> (bitCompression) << endl;
        //cout << p << "," << compression << endl;
        //cout << p << ": " << riceBits << " " << origBits << " " << ratio << endl;
    }
    outFile.close();
}
