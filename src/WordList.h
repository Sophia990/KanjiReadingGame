#pragma once

#include <list>
#include "Word.h"

class WordList {
public:
    void readCSV(const std::string& filepath);
    int getSize();

    std::list<Word> wordList;
};
