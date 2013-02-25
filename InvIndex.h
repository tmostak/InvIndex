#ifndef INVINDEX_H
#define INVINDEX_H

#include <boost/dynamic_bitset.hpp>

class InvIndex {
    
    private:
        struct WordInfo {
            boost::dynamic_bitset bitset;
            vector <int> overflow;
            boost::mutex mutex;
        };
        vector <WordInfo *> wordVec; // makes overhead of storing a lot of these neglibible

        boost::mutex vecMutex; // to resize vec
            
        //vector <boost::dynamic_bitset> bitsets;
        //vector <vector<int> > overflow;
        //vector <boost::mutex> wordMutexes;
        
    public:
        InvIndex(const size_t arraySize);
        insertDoc(int docId, const vector <int> &wordIds);
        insertDoc(int docId, const vector <string> words); // will need map to do this



    





};


#endif
