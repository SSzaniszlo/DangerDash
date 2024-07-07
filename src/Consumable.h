#define CONSUMABLE_ID_HEALTH_POTION 1


class Consumable : public Item {
    
    public:
    
        Consumable() {type = ITEM_TYPE_CONSUMABLE;}
        
        int id;

        void use() override {

            std::cout << "fuck u" << std::endl;
            
            Inventory::Slot slot = inventory->slots.at(inventory->selected);

            if (slot.count > 0) {
                slot.count--;
            }

            std::cout << slot.count << std::endl;

            effect();
            
        };
        
        virtual void effect(){};
     
};

class HealthPotion : public Consumable {
    void effect() override {
        inventory->owner->health += 10;
    }
};
