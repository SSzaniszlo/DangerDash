class Weapon : public Item {
    public:
        
        Weapon(std::vector<Entity*> *ePtr) {
            entities = ePtr;
            type = ITEM_TYPE_WEAPON;
        }

        std::vector<Entity*> *entities;
        
        float damageRadius;
        float damage;

        void use() override {
            
            Entity *owner = inventory->owner;

            //Starting at index 1 to avoid player
            for (int i = 1; i < entities->size(); i++) {
                
                if (fabs(entities->at(i)->pos.x - owner->pos.x) > damageRadius){continue;}
                if (fabs(entities->at(i)->pos.y - owner->pos.y) > damageRadius){continue;}

                entities->at(i)->health -= damage;

            }     
        }

};

class Sword : public Weapon {

};