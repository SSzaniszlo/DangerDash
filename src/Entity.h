#define ENTITY_TYPE_DEFAULT 0
#define ENTITY_TYPE_PLAYER 1


class Entity {
    public:

        int type = ENTITY_TYPE_DEFAULT;

        vector2 pos;
        vector2 size;
        vector2 speed;

        float health;
        bool render;


        virtual void move(float deltaTime){};

        virtual ~Entity(){};

};