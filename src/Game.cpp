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
    
    Entity entity;
    initEntity(&entity);


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
            case SDL_MOUSEBUTTONDOWN:
                mouseButtonDown = event.button.button;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS) {
                    player.inventory.selected++;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS) {
                    player.inventory.selected--;
                } else {
                    break;
                }

                //std::cout << player.inventory.selected << " " << player.inventory.slots.at(player.inventory.selected).item.name << std::endl;
                break;
        }
    }

    mouseState = SDL_GetMouseState(&mousePos.x, &mousePos.y);


    if (keyState[SDL_SCANCODE_ESCAPE]) {
        running = false;
    }


}

void Game::render() {
    
    SDL_SetRenderDrawColor(renderer, 66, 135, 245, 255);
    SDL_RenderClear(renderer);


    //Will replace all this with textures
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (auto entity : entities) {
        
        if (!entity->render){continue;}


        SDL_Rect rect;   
        
        rect.x = entity->pos.x;
        rect.y = entity->pos.y;

        rect.w = entity->size.x;
        rect.h = entity->size.y;

        SDL_RenderFillRect(renderer, &rect);
    }



    SDL_RenderPresent(renderer);
}

void Game::update() {
    
    
    if (mouseButtonDown > 0) {
        switch (mouseButtonDown) {
            case 1:
                
                Item *item = player.inventory.slots.at(player.inventory.selected).item;
                std::cout << "Item type: " << item->type << std::endl;

                /*
                switch (item.type) {
                    case ITEM_TYPE_CONSUMABLE: {
                        Consumable *consumable = static_cast<Consumable*>(&item);
                        consumable->use();
                    } break;
                    case ITEM_TYPE_WEAPON: {
                        Weapon *weapon = static_cast<Weapon*>(&item);
                        weapon->use();
                    } break;
                }*/

                item->use();

                std::cout << player.health << std::endl;
                
                
                break;   
        }

        mouseButtonDown = 0;
    }
    


    for (auto entity : entities) {
        
        /* THIS IS HOW TO CAST
        if (entity->type == ENTITY_TYPE_PLAYER) {
            Player *localPlayer = static_cast<Player*>(entity);
        }
        */
        entity->update();
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
    Weapon *item = new Weapon(&entities);
    
    item->name = "Weapon";
    item->stackCount = 1;
    item->inventory = &player.inventory;

    Inventory::Slot slot;
    slot.count = 1;
    slot.item = item;

    player.inventory.slots.emplace_back(slot);

    HealthPotion *item1 = new HealthPotion();
    
    item1->name = "health";
    item1->stackCount = 1;
    item1->inventory = &player.inventory;

    item->damage = 10;
    item->damageRadius = 50;

    Inventory::Slot slot1;
    slot1.count = 1;
    slot1.item = item1;

    player.inventory.slots.emplace_back(slot1);

    //Test//


    entities.emplace_back(&player);
}

//Test function
void Game::initEntity(Entity *entity) {
    
    entity->health = 10.0f;
    
    entity->pos.x = 500;
    entity->pos.y = 500;
    
    entity->size.x = 100;
    entity->size.y = 100;
    
    entity->speed.x = 50;
    entity->speed.y = 50;

    entity->render = true;



    entities.emplace_back(entity);

}




