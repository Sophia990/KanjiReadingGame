#pragma once

#include <SFML/Graphics.hpp>
#include "iostream"
#include "sstream"

class Textbox {
public:
    explicit Textbox(
            int characterSize,
            sf::Color colour,
            const sf::Font& font) : textbox(font) {
        textbox.setCharacterSize(characterSize);
        textbox.setFillColor(colour);
        textbox.setString("_");
        textbox.setOrigin(textbox.getLocalBounds().getCenter());
    }

    void setPosition(sf::Vector2f point);
    void setLimit(int lim);
    void drawTextbox(sf::RenderWindow &window);
    void clearText();
    sf::String handleTypedOn(const sf::Event& input);
private:
    sf::Text textbox;
    sf::String text;
    int limit = 0;

    sf::String getText();
    sf::String handleInput(std::uint32_t unicodeTyped);
};
