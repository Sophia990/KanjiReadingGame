#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode::getDesktopMode(), "Kanji Reading Game" );

	// load font
	sf::Font font;
	if (!font.openFromFile("assets/fonts/NotoSansJP-Black.ttf")) std::cout << "Font not found\n";

    // make textbox for answer
	Textbox answerText(50, sf::Color::White, font);
	answerText.setPosition({(static_cast<float>(window.getSize().x) / 2.f) - 750,
							static_cast<float>(window.getSize().y) - 300.f});
	answerText.setLimit(50);

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
			if ( event->is<sf::Event::TextEntered>() )
				answerText.handleTypedOn(*event);
		}

		window.clear();
		answerText.drawTextbox(window);
		window.display();
	}
}
