#include "FallingWordList.h"

void FallingWordList::dropWord(std::uniform_real_distribution<float> &xDist,
                                        std::uniform_int_distribution<int> &wordDist,
                                        std::mt19937 &randomNumberGenerator,
                                        const sf::Font &font,
                                        const WordList &wordList) {
    Word newWord = wordList.tempWordArray[wordDist(randomNumberGenerator)];
    sf::Vector2f position = {xDist(randomNumberGenerator), 0.f};
    fallingWordList.emplace_back(newWord.getKanji(),
                                 newWord.getKana(),
                                 newWord.getRomaji(),
                                          font,
                                          position);
}

void FallingWordList::update(float dt, float speed, float bottomLine, const sf::String& answer) {
    for (auto word = fallingWordList.begin(); word != fallingWordList.end(); ) {
        word->fall(dt, speed, bottomLine);
        if (!answer.isEmpty() && (answer == word->getKana() || answer == word->getRomaji())) {
            word->destroy(true);
        }
        if (word->getShouldDestroy()) {
            word = fallingWordList.erase(word);
        }
        else {
            ++word;
        }
    }
}