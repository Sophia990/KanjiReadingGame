#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "FallingWord.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode::getDesktopMode(), "Kanji Reading Game" );

	// load font
	sf::Font font;
	if (!font.openFromFile("assets/fonts/NotoSansJP-Black.ttf")) std::cout << "Font not found\n";

    // make textbox for answer
	Textbox answerText(50, sf::Color::White, font);
	answerText.setPosition({(static_cast<float>(window.getSize().x) / 2.f),
							static_cast<float>(window.getSize().y) - 300.f});
	answerText.setLimit(50);

	// for randomness
	std::random_device rd;
	std::mt19937 randomNumberGenerator(rd());
	std::uniform_real_distribution<float> xDist(100.f, static_cast<float>(window.getSize().x) - 100);

	// temporarily make word to test drawing a word
	sf::Vector2f position = {xDist(randomNumberGenerator), 0.f};
	FallingWord testWord(U"漢字", U"かんじ", U"kanji", font, position);

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
		testWord.drawWord(window);
		window.display();
	}
}
