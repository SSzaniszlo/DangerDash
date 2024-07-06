#include "Game.h"

int main() {
    
    Game game;
    
    if (game.init()) {
        game.start();
    }
}