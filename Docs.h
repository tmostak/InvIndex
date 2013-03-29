#ifndef DOCS_H
#define DOCS_H

#include <string>
#include <vector>

class Docs {

    private:
        std::string fileName;
        unsigned int *rawMem;
        unsigned int numDocs;
        unsigned int *offsets;
        unsigned int *data; 
        int readFile();
    public:
        Docs(const std::string &_fileName);
        ~Docs();
        void printData();
};
        


#endif
