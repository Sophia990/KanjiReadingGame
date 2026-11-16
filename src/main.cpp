#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <optional>

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
