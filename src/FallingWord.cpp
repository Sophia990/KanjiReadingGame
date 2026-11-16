#include "FallingWord.h"

void FallingWord::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(text, states); }

void FallingWord::fall(float dt, float speed) {
    position.y += speed * dt;
    text.setPosition(position);
}

bool FallingWord::hasReachedBottom(float bottomY) const { return position.y >= bottomY; }

// accept answer in kana (japanese phonetic syllabaries) or romaji (transliteration of japanese into latin alphabet)
bool FallingWord::matches(const sf::String& answer) const { return (answer == getKana() || answer == getRomaji()); }
