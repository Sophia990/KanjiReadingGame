#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <cstdlib>
#include <optional>
#include <string>
#include "Textbox.h"
#include "WordList.h"
#include "FallingWordList.h"
#include "Button.h"

enum GameState {
	START_MENU,
	GAME,
	GAME_OVER
};

int main()
{
    sf::RenderWindow window( sf::VideoMode::getDesktopMode(), "It's Raining Kanji" );

    window.display();
    window.clear();

    enum GameState gameState = START_MENU;

	const float BOTTOM_LINE_Y_COORDINATE = static_cast<float>(window.getSize().y) - 400.f;

	// filepaths
	const std::string fontPath = "assets/fonts/NotoSansJP-Black.ttf";
	const std::string correctSoundPath = "assets/audio/correct.wav";
	const std::string incorrectSoundPath = "assets/audio/incorrect.wav";
	const std::string musicPath = "assets/audio/music.ogg";
	const std::string csvPath = "assets/vocab/vocab-n5.csv";

	// points and lives
	int points = 0;
	int lives = 5;

	// load font
	sf::Font font;
	if (!font.openFromFile(fontPath)) {
		std::cerr << "Failed to load font: " << fontPath << "\n";
		return EXIT_FAILURE;
	}

	// for sound effects
	sf::SoundBuffer correctBuffer;
	sf::SoundBuffer incorrectBuffer;
	if (!correctBuffer.loadFromFile(correctSoundPath))
		std::cerr << "Failed to load sound: " << correctSoundPath << "\n";
	if (!incorrectBuffer.loadFromFile(incorrectSoundPath))
		std::cerr << "Failed to load sound: " << incorrectSoundPath << "\n";
	sf::Sound correctSound(correctBuffer);
	sf::Sound incorrectSound(incorrectBuffer);

	// for music
	sf::Music music;
	if (!music.openFromFile(musicPath))
		std::cerr << "Failed to load music: " << musicPath << "\n";
	music.setLooping(true);

	// for words falling on screen
	sf::Clock fallClock;
	const float fallSpeed = 30.f;

	// for spawning words at a time interval
	sf::Clock dropClock;
	const float dropInterval = 2.f;

    // make textbox for answer
	Textbox answerText(50, sf::Color::White, font);
	answerText.setPosition({(static_cast<float>(window.getSize().x) / 2.f),
							static_cast<float>(window.getSize().y) - 200.f});
	answerText.setLimit(50);

	// make bottom line
	std::array bottomLine = {
			sf::Vertex{sf::Vector2f(0.f, BOTTOM_LINE_Y_COORDINATE)},
			sf::Vertex{sf::Vector2f(static_cast<float>(window.getSize().x), BOTTOM_LINE_Y_COORDINATE)}
	};

	// make points text
	sf::Text pointsText(font);
	pointsText.setString("Points: " + std::to_string(points));
	pointsText.setCharacterSize(50);
	pointsText.setFillColor(sf::Color::White);
    pointsText.setOrigin({pointsText.getLocalBounds().size.x, 0.f});
    pointsText.setPosition({static_cast<float>(window.getSize().x) - 300.f, static_cast<float>(window.getSize().y) - 300.f});

	// make lives text
	sf::Text livesText(font);
	livesText.setString("Lives: " + std::to_string(lives));
	livesText.setCharacterSize(50);
	livesText.setFillColor(sf::Color::White);
    livesText.setPosition({300.f, static_cast<float>(window.getSize().y) - 300.f});

	// for randomness
	std::random_device rd;
	std::mt19937 randomNumberGenerator(rd());
	std::uniform_real_distribution<float> xDist(100.f, static_cast<float>(window.getSize().x) - 100);

	WordList wordList;
	if (!wordList.readCSV(csvPath)) return EXIT_FAILURE;

	FallingWordList fallingWordList;

	sf::String currentAnswer = "";

	// title text
	sf::Text titleText(font);
	titleText.setString("It's Raining Kanji");
	titleText.setCharacterSize(200);
	titleText.setFillColor(sf::Color::White);
	titleText.setOrigin(titleText.getLocalBounds().getCenter());
	titleText.setPosition({static_cast<float>(window.getSize().x) / 2.f, (static_cast<float>(window.getSize().y) / 2.f) - 150});

	// start button
	Button startButton("Start", {200, 100}, 30, sf::Color::Blue, sf::Color::White, font);
	startButton.setPosition({static_cast<float>(window.getSize().x) / 2.f, (static_cast<float>(window.getSize().y) / 2.f) + 150});

	// game over text
	sf::Text gameOverText(font);
	gameOverText.setString("Game Over!");
	gameOverText.setCharacterSize(200);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setOrigin(gameOverText.getLocalBounds().getCenter());
	gameOverText.setPosition({static_cast<float>(window.getSize().x) / 2.f, (static_cast<float>(window.getSize().y) / 2.f) - 300});

	// final points text
	sf::Text finalPointsText(font);
	finalPointsText.setString("Points: " + std::to_string(points));
	finalPointsText.setCharacterSize(200);
	finalPointsText.setFillColor(sf::Color::White);
	finalPointsText.setOrigin(finalPointsText.getLocalBounds().getCenter());
	finalPointsText.setPosition({static_cast<float>(window.getSize().x) / 2.f, (static_cast<float>(window.getSize().y) / 2.f)});

	// return to menu button
    Button returnToMenuButton("Return to Menu", {300, 100}, 30, sf::Color::Blue, sf::Color::White, font);
	returnToMenuButton.setPosition({static_cast<float>(window.getSize().x) / 2.f, (static_cast<float>(window.getSize().y) / 2.f) + 300});

	while ( window.isOpen() )
	{
		while ( window.isOpen() && gameState == START_MENU )
		{
			while ( const std::optional event = window.pollEvent() )
			{
				if ( event->is<sf::Event::Closed>() )
					window.close();
				if ( event->is<sf::Event::MouseButtonPressed>() )
					if (startButton.isMouseOver(window)) {
                        fallClock.restart();
                        dropClock.restart();
						music.play();
						gameState = GAME;
					}
			}

			window.clear();
			window.draw(titleText);
			startButton.drawButton(window);
			window.display();
		}

		while ( window.isOpen() && lives > 0 && gameState == GAME)
		{
			float dt = fallClock.restart().asSeconds();

			if (dropClock.getElapsedTime().asSeconds() >= dropInterval) {
				fallingWordList.dropWord(xDist, randomNumberGenerator, font, wordList);
				dropClock.restart();
			}

			fallingWordList.update(dt, fallSpeed, BOTTOM_LINE_Y_COORDINATE, currentAnswer, points, lives, correctSound, incorrectSound);
            currentAnswer = "";
			pointsText.setString("Points: " + std::to_string(points));
			livesText.setString("Lives: " + std::to_string(lives));

			while ( const std::optional event = window.pollEvent() )
			{
				if ( event->is<sf::Event::Closed>() )
					window.close();
				if ( event->is<sf::Event::TextEntered>() )
					currentAnswer = answerText.handleTypedOn(*event);
			}

			window.clear();
			answerText.drawTextbox(window);
			window.draw(pointsText);
			window.draw(livesText);
			window.draw(bottomLine.data(), bottomLine.size(), sf::PrimitiveType::Lines);
			fallingWordList.drawWords(window);
			window.display();
		}

		gameState = GAME_OVER;
		music.stop();

		while ( window.isOpen() && gameState == GAME_OVER ) {
			while ( const std::optional event = window.pollEvent() )
			{
				if ( event->is<sf::Event::Closed>() )
					window.close();
				if ( event->is<sf::Event::MouseButtonPressed>() )
					if (returnToMenuButton.isMouseOver(window)) {
						// reset game variables
						points = 0;
						lives = 5;
						answerText.clearText();
						currentAnswer = "";
						wordList.wordList.clear();
						if (!wordList.readCSV(csvPath)) return EXIT_FAILURE;
						fallingWordList.clearWords();
						gameState = START_MENU;
					}
			}

			window.clear();
			finalPointsText.setString("Points: " + std::to_string(points));
			finalPointsText.setOrigin(finalPointsText.getLocalBounds().getCenter());
			window.draw(gameOverText);
			window.draw(finalPointsText);
			returnToMenuButton.drawButton(window);
			window.display();
		}
	}
}
