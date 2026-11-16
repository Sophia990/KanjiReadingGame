#pragma once

#include <list>
#include <string>
#include <cstddef>
#include "Word.h"

class WordList {
public:
    bool readCSV(const std::string& filepath);
    [[nodiscard]] std::size_t getSize() const;

    std::list<Word> words;
};
