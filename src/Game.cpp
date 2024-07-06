#include "Game.h"


struct settings {
    int width = 800;
    int height = 800;
    const char *title = "DangerDash";
};


bool Game::init() {
    

    struct settings s;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {  
        SDL_Log("Unable to init SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(s.title, 0, 0, s.width, s.height, 0);

    if (!window) {
        SDL_Log("Unable to init window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        SDL_Log("Unable to init renderer: %s", SDL_GetError());
        return false;
    }

    keyState = SDL_GetKeyboardState(NULL);

    return true;
}


void Game::start() {
    
    initPlayer();

    entities.emplace_back(&player);

    running = true;
    
    while (running) {
        
        deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
        ticksCount = SDL_GetTicks();


        input();
        update();
        render();
    }

}


void Game::input() {
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
        }
    }

    mouseState = SDL_GetMouseState(&mousePos.x, &mousePos.y);

    std::cout << "Mouse pos x: " << mousePos.x << " y: " << mousePos.y << std::endl;

    if (mouseState & SDL_BUTTON_LMASK) {
        std::cout << "mouse 1 pressed" << std::endl;
    }

    if (mouseState & SDL_BUTTON_RMASK) {
        std::cout << "mouse 2 pressed" << std::endl;
    }

    if (keyState[SDL_SCANCODE_ESCAPE]) {
        running = false;
    }


}

void Game::render() {
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);
    SDL_RenderClear(renderer);

    if (player.render) {
        
        SDL_Rect rect;   
        
        rect.x = player.pos.x;
        rect.y = player.pos.y;

        rect.w = player.size.x;
        rect.h = player.size.y;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        
    }

    SDL_RenderPresent(renderer);
}

void Game::update() {
    
    for (auto entity : entities) {
        
        /* THIS IS HOW TO CAST
        if (entity->type == ENTITY_TYPE_PLAYER) {
            Player *localPlayer = static_cast<Player*>(entity);
        }
        */

        

        entity->move(deltaTime);

    }
}


void Game::initPlayer() {
    
    player = Player();

    player.health = 10.0f;
    player.size.x = 10;
    player.size.y = 10;
    player.pos.x = 100;
    player.pos.y = 100;
    player.speed.x = 50;
    player.speed.y = 50;

    player.render = true;
    player.keyState = keyState;

    player.inventory.maxSize = 10;
    player.inventory.owner = &player;
    player.inventory.selected = 0;

    //Test//
    Item item;
    
    item.name = "hello";
    
    item.stackCount = 2;

    Inventory::Slot slot;
    slot.count = 2;
    slot.item = item;

    player.inventory.slots.emplace_back(slot);
    //Test//
}





