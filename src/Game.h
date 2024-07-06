#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>

#include "Structs.h"

#include "Entity.h"
#include "Item.h"
#include "Inventory.h"
#include "Player.h"

#include "Weapon.h"




class Game {
    public:
        bool init();
        void start();
    private:
        
        void input();
        void render();
        void update();

        void initPlayer();

        Player player;
        std::vector<Entity*> entities;

        const Uint8* keyState;
        Uint32 mouseState;
        
        vector2Int mousePos;


        Uint32 ticksCount;
        float deltaTime;

        bool running;
        SDL_Window *window;
        SDL_Renderer *renderer;
};