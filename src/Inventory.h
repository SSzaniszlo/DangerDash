class Item;

class Inventory {
    
    
    public:
        
        int selected;
        int maxSize;

        struct Slot {
            int count;
            Item *item;
        };
        
        Entity *owner;
        std::vector<Slot> slots;
    
};