#ifndef CMAKESFMLPROJECT_BUTTON_H
#define CMAKESFMLPROJECT_BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {

public:
    Button(const sf::String& buttonText,
           sf::Vector2f buttonSize,
           int charSize,
           sf::Color backgroundColour,
           sf::Color textColour,
           sf::Font &font) : text(font) {
        button.setSize(buttonSize);
        button.setFillColor(backgroundColour);

        text.setString(buttonText);
        text.setCharacterSize(charSize);
        text.setFillColor(textColour);
    }

    void setBackgroundColour(sf::Color colour);
    void setTextColour(sf::Color colour);
    void setPosition(sf::Vector2f point);
    void drawButton(sf::RenderWindow &window);
    bool isMouseOver(sf::RenderWindow &window);

private:
    sf::RectangleShape button;
    sf::Text text;
};


#endif //CMAKESFMLPROJECT_BUTTON_H
