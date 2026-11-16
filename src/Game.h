#pragma once

#include "Button.h"
#include "FallingWordList.h"
#include "Textbox.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <string>

class Game {
public:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void run();

private:
    enum class State { StartMenu, Playing, GameOver };

    void processEvents();
    void update();
    void render();
    void startGame();
    void resetGame();

    sf::RenderWindow window;
    const sf::Vector2f windowSize;
    const sf::Vector2f centre;
    const float bottomLineYCoordinate;

    sf::Font font;
    sf::SoundBuffer correctBuffer;
    sf::SoundBuffer incorrectBuffer;
    sf::Sound correctSound;
    sf::Sound incorrectSound;
    sf::Music music;

    sf::Clock fallClock;
    sf::Clock dropClock;

    std::mt19937 randomNumberGenerator;
    std::uniform_real_distribution<float> xDist;

    WordList wordList;
    FallingWordList fallingWordList;

    Textbox answerText;
    std::array<sf::Vertex, 2> bottomLine;
    sf::Text pointsText;
    sf::Text livesText;

    sf::Text titleText;
    Button startButton;
    sf::Text gameOverText;
    sf::Text finalPointsText;
    Button returnToMenuButton;

    int points;
    int lives;
    State state;
};