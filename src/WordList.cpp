#include "WordList.h"
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

        if (kanji != reading) {
            words.emplace_back(sf::String::fromUtf8(kanji.begin(), kanji.end()),
                               sf::String::fromUtf8(reading.begin(), reading.end()),
                               sf::String::fromUtf8(romaji.begin(), romaji.end()));
        }
    }

    return true;
}

std::size_t WordList::getSize() const { return words.size(); }