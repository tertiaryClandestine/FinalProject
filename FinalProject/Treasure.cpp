#include "Treasure.h"

Treasure::Treasure(){
    goldVal = 0;
    name = "";
    description = "";
}

Treasure::Treasure(int _goldVal, std::string _name, std::string _description){
    goldVal = _goldVal;
    name = _name;
    description = _description;
}

int Treasure::getGoldVal() {
    return goldVal;
}

std::string Treasure::getName() {
    return name;
}

std::string Treasure::getDescription() {
    return description;
}
