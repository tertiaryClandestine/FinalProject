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
        description = "Shiny black gemstone";
    } else if (rndVal < 3) {
        goldVal = 0;
        name = "Health Potion (50)";
        description = "Restores 50 HP";
    } else if (rndVal < 5) {
        goldVal = 0;
        name = "AP up (2)";
        description = "Increases attack power by 2";
    } else if (rndVal < 7) {
        goldVal = 0;
        name = "AP up (1)";
        description = "Increases attack power by 1";
//    } else if (rndVal < 10) {
//        goldVal = 2500;
//        name = "Diamond";
//        description = "Shiny clear gemstone";
//    } else if (rndVal < 20){
//        goldVal = 2000;
//        name = "Ruby";
//        description = "Shiny red gemstone";
//    } else if (rndVal < 30) {
//        goldVal = 1500;
//        name = "Emerald";
//        description = "Shiny green gemstone";
    } else if (rndVal < 50) {
        goldVal = 0;
        name = "Health Potion (10)";
        description = "Restores 10 HP";
    } else if (rndVal < 70) {
        goldVal = 1000;
        name = "Sapphire";
        description = "Shiny blue gemstone";
    } else {
        goldVal = 500;
        name = "Opal";
        description = "Shiny multicolored gemstone";
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
