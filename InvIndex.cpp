#include "InvIndex.h"

InvIndex::InvIndex(const size_t arraySize) {
    wordVec.resize(arraySize); // should we restore arraySize
}
    

InvIndex::~InvIndex() {
    for (vector<WordInfo *>::wordVecIt = wordVec.begin(); wordVecIt != wordVec.end(); ++wordVecIt) {
        delete *wordVecIt;
    }
}
    
InvIndex::insertDoc(int docId, const vector <int> &wordIds) {
    for (vector <int>::wordIt = wordIds.begin(); wordIt != wordIds.end(); ++wordIt) {
        boost::lock_guard<boost::mutex> wordLock (wordVec[*wordIt].mutex);
        if (wordVec[*wordIt] == 0) // if null pointer
            wordVec[*wordIt] = new WordInfo; 
        wordVec[*wordIt] -> overflow.push_back(docId);
    }
}




    }
    

        int wordId = *wordIt; // will this save a few pointer dereferences
        boost::lock_guard<boost::mutex> wordLock(utexes[wordMutexes[wordId];
    }
        
    
    
