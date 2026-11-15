#pragma once

#include <list>
#include "Word.h"

class WordList {
public:
    bool readCSV(const std::string& filepath);
    [[nodiscard]] int getSize() const;

    std::list<Word> wordList;
};
