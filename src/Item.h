#define ITEM_TYPE_CONSUMABLE 0
#define ITEM_TYPE_WEAPON 1

class Inventory;

class Item {

    public:
        
        int type;
        std::string name;
        int stackCount;

        Inventory *inventory;

        virtual void use(){std::cout << "Item base class" << std::endl;};


};