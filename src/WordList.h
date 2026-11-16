#pragma once

#include "Word.h"
#include <cstddef>
#include <list>
#include <random>
#include <string>
#include <optional>
#include <vector>

class WordList {
public:
    bool readCSV(const std::string& filepath);
    void reset(std::mt19937& randomNumberGenerator);
    std::optional<Word> takeWord();

private:
    std::vector<Word> allWords;
    std::vector<Word> remainingWords;
};
