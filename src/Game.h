#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>

#include "Structs.h"

#include "Entity.h"

#include "Item.h"
#include "Inventory.h"

#include "Consumable.h"
#include "Weapon.h"

#include "Player.h"




class Game {
    public:
        bool init();
        void start();
    private:
        
        void input();
        void render();
        void update();

        void initPlayer();
        void initEntity(Entity *entity);

        Player player;

        std::vector<Entity*> entities;

        const Uint8* keyState;
        Uint32 mouseState;
        
        vector2Int mousePos;

        int mouseButtonDown = 0;

        Uint32 ticksCount;
        float deltaTime;


        bool running;
        SDL_Window *window;
        SDL_Renderer *renderer;
};