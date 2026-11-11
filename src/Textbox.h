#ifndef CMAKESFMLPROJECT_TEXTBOX_H
#define CMAKESFMLPROJECT_TEXTBOX_H

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
    }

    void setPosition(sf::Vector2f point);
    void setLimit(int lim);
    void drawTextbox(sf::RenderWindow &window);
    void handleTypedOn(const sf::Event& input);
private:
    sf::Text textbox;
    sf::String text;
    int limit = 0;

    sf::String getText();
    void handleInput(std::uint32_t unicodeTyped);
};

#endif //CMAKESFMLPROJECT_TEXTBOX_H
