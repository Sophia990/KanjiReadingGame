#include "WordList.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

bool WordList::readCSV(const std::string& filepath) {
    std::ifstream fin;

    fin.open(filepath, std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Failed to load file: " << filepath << "\n";
        return false;
    }

    std::string line;
    std::getline(fin, line);

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string id, kanji, reading, romaji;
        std::getline(ss, id, ',');
        std::getline(ss, kanji, ',');
        std::getline(ss, reading, ',');
        std::getline(ss, romaji, ',');

        // skip words with no kanji by skipping rows with equal values in kanji and reading columns
        if (kanji != reading) {
            allWords.emplace_back(sf::String::fromUtf8(kanji.begin(), kanji.end()),
                                  sf::String::fromUtf8(reading.begin(), reading.end()),
                                  sf::String::fromUtf8(romaji.begin(), romaji.end()));
        }
    }

    return true;
}

void WordList::reset(std::mt19937& randomNumberGenerator) {
    remainingWords = allWords;
    std::shuffle(remainingWords.begin(), remainingWords.end(), randomNumberGenerator);
}

std::optional<Word> WordList::takeWord() {
    if (remainingWords.empty()) { return std::nullopt; }
    Word word = std::move(remainingWords.back());
    remainingWords.pop_back();
    return word;
}