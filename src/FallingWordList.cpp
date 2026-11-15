#include "FallingWordList.h"

namespace {
    sf::String toLowerAscii(sf::String text) {
        for (char32_t& c : text) {
            if (c >= U'A' && c <= U'Z') {
                c += U'a' - U'A';
            }
        }
        return text;
    }
}

void FallingWordList::dropWord(std::uniform_real_distribution<float> &xDist,
                                        std::mt19937 &randomNumberGenerator,
                                        const sf::Font &font,
                                        WordList &wordList) {
    if (wordList.wordList.empty()) {
        return;
    }
    std::uniform_int_distribution<int> wordDist(0, wordList.getSize() - 1);

    auto it = wordList.wordList.begin();
    advance(it, wordDist(randomNumberGenerator));
    Word newWord = *it;
    wordList.wordList.erase(it);

    sf::Vector2f position = {xDist(randomNumberGenerator), 0.f};
    fallingWordList.emplace_back(newWord.getKanji(),
                                 newWord.getKana(),
                                 newWord.getRomaji(),
                                          font,
                                          position);
}

void FallingWordList::update(float dt, float speed, float bottomLine, const sf::String& answer, int& points, int& lives, sf::Sound& correctSound, sf::Sound& incorrectSound) {
    const sf::String loweredAnswer = toLowerAscii(answer);
    for (auto word = fallingWordList.begin(); word != fallingWordList.end(); ) {
        word->fall(dt, speed, bottomLine, points, lives, correctSound, incorrectSound);
        if (!loweredAnswer.isEmpty() && (loweredAnswer == word->getKana() || loweredAnswer == word->getRomaji())) {
            word->destroy(true, points, lives, correctSound, incorrectSound);
        }
        if (word->getShouldDestroy()) {
            word = fallingWordList.erase(word);
        }
        else {
            ++word;
        }
    }
}

void FallingWordList::drawWords(sf::RenderWindow &window) {
    for (FallingWord& word : fallingWordList) {
        word.drawWord(window);
    }
}

void FallingWordList::clearWords() {
    fallingWordList.clear();
}
