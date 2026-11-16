#pragma once

#include "Word.h"
#include <cstddef>
#include <list>
#include <string>

class WordList {
public:
    bool readCSV(const std::string& filepath);
    [[nodiscard]] std::size_t getSize() const;

    std::list<Word> words;
};
