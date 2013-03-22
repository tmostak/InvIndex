#ifndef RUNLENENCODER_H
#define RUNLENENCODER_H

template <typename T> class RLIterator;

//typedef unsigned int index;
template <typename T> class RunLenEncoder {

    private:
        
        unsigned char *compressedData;
        size_t dataLen;
        T lastVal;

    public:

        friend class RLIterator <T>;
        typedef RLIterator <T > iterator;
        iterator begin() {return iterator (*this, 0);}
        iterator end() {return iterator (*this, 





                
                
            
            
            
            
        
            
        virtual void encode(T* data, size_t len) = 0;
        virtual void encodeElem(index elem) = 0; 
        void decodeAll
    

    

    
    

};


template <typename T> struct RLIterator {
    unsigned char *data;
    T prevSum;

    Iterator (const Iterator &iterator) {
        index = iterator.index;
        prevSum = iterator.prevSum;
    }
        



#endif




