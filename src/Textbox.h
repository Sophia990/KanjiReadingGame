#pragma once

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <cstdint>

class Textbox : public sf::Drawable {
public:
    Textbox(
            unsigned int characterSize,
            sf::Color colour,
            const sf::Font& font) : textbox(font) {
        textbox.setCharacterSize(characterSize);
        textbox.setFillColor(colour);
        textbox.setString("_");
        textbox.setOrigin(textbox.getLocalBounds().getCenter());
    }

    void setPosition(sf::Vector2f point);
    void setLimit(std::size_t lim);
    void clearText();
    sf::String handleTypedOn(const sf::Event& input);
private:
    sf::Text textbox;
    sf::String text;
    std::size_t limit = 0;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::String handleInput(char32_t unicodeTyped);
};
