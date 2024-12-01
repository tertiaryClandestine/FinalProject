//#pragma once
#include "Treasure.h"
#include "Utils.h"

Treasure::Treasure(){
//    goldVal = 0;
//    name = "";
//    description = "";
    double rndVal = utils::RandVal();
    if (rndVal < 2) {
        goldVal = 5000;
        name = "Onyx";
        description = "Shiny, but black!";
    } else if (rndVal < 3) {
        goldVal = 0;
        name = "Health Potion (50)";
        description = "Restores 50 HP";
    } else if (rndVal < 10) {
        goldVal = 2500;
        name = "Diamond";
        description = "Shiny!";
    } else if (rndVal < 20){
        goldVal = 2000;
        name = "Ruby";
        description = "Shiny, but red!";
    } else if (rndVal < 30) {
        goldVal = 1500;
        name = "Emerald";
        description = "Shiny, but green!";
    } else if (rndVal < 50) {
        goldVal = 1000;
        name = "Sapphire";
        description = "Shiny, but blue!";
    } else if (rndVal < 70) {
        goldVal = 0;
        name = "Health Potion (10)";
        description = "Restores 10 HP";
    } else {
        goldVal = 0;
        name = "Junk";
        description = "Who wants this anyway?";
    }
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
void Treasure::print() {
    std::cout << "Gold Val: " << getGoldVal() << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Description: " << getDescription() << std::endl;
}
