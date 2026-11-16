#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
    Button(const sf::String& buttonText,
           sf::Vector2f buttonSize,
           unsigned int charSize,
           sf::Color backgroundColour,
           sf::Color textColour,
           const sf::Font& font)
        : text(font) {
        button.setSize(buttonSize);
        button.setFillColor(backgroundColour);

        text.setString(buttonText);
        text.setCharacterSize(charSize);
        text.setFillColor(textColour);
    }

    void setPosition(sf::Vector2f point);
    bool isMouseOver(const sf::RenderWindow& window) const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape button;
    sf::Text text;
};
