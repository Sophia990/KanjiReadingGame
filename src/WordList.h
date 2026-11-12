#ifndef CMAKESFMLPROJECT_WORDLIST_H
#define CMAKESFMLPROJECT_WORDLIST_H

#include <list>
#include "Word.h"

class WordList {
public:
    void readCSV(const std::string& filepath);
    int getSize();

    std::list<Word> wordList;
};


#endif //CMAKESFMLPROJECT_WORDLIST_H
