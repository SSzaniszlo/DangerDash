class Player : public Entity {
    public:
        
        int type = ENTITY_TYPE_PLAYER;

        void move(float deltaTime) override {
            
            if (keyState[SDL_SCANCODE_W]) {
                this->pos.y -= deltaTime * this->speed.y;
            }

            if (keyState[SDL_SCANCODE_A]) {
                this->pos.x -= deltaTime * this->speed.x;
            }

            if (keyState[SDL_SCANCODE_S]) {
                this->pos.y += deltaTime * this->speed.y;
            }

            if (keyState[SDL_SCANCODE_D]) {
                this->pos.x += deltaTime * this->speed.x;
            }


        };


        const Uint8* keyState;

        Inventory inventory;

        

};
