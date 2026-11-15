#pragma once

#include <list>
#include <string>
#include "Word.h"

class WordList {
public:
    bool readCSV(const std::string& filepath);
    [[nodiscard]] int getSize() const;

    std::list<Word> wordList;
};
