class Inventory {
    
    
    public:
        
        struct Slot {
            int count;
            Item item;
        };
        
        Entity owner;
        std::vector<Slot> slots;
};