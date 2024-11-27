//#pragma once
#include "Player.h"
Player::Player(Map* _map, int _x, int _y){
    gameMap = _map;
    playerLoc = gameMap->getTile(_x, _y);
    playerLoc->setPlayerTile();
    health = 100;
    gold = 0;
    attackPower = 5;
    inventory[0] = new Treasure(500, "Ruby", "Shiny! But also red");
    inventory[1] = new Treasure(750, "Diamond", "Shiny! But also clear");
    inventory[2] = new Treasure(5, "Wood", "Can be used to craft items");
    inventory[3] = new Treasure(3, "Tar", "Useless");
    inventory[4] = new Treasure(20, "Hatchet", "Can be used to cut down trees");
    
}
Player::Player(Map* _map, std::string filePath) {
    gameMap = _map;
    Load(filePath);
}
Tile* Player::GetLoc(){
    return playerLoc;
}
void Player::Move(int deltaX, int deltaY){
    Tile* nextTile = gameMap->getTile(playerLoc->getX() + deltaX, playerLoc->getY() + deltaY);
    if (nextTile->getType() != "Wall"){
        playerLoc->setPlayerTile();
        playerLoc = nextTile;
        playerLoc->setPlayerTile();
    }
}
void Player::Save(std::string filePath){
    std::ofstream outputFile(filePath);
    if(!outputFile.is_open())
        throw PlayerFileReadError("unable to create file: " + filePath);
    std::stringstream outSS;
    outSS << playerLoc->getX() << std::endl;
    outSS << playerLoc->getY() << std::endl;
    outSS << health << std::endl;
    outSS << gold << std::endl;
    outSS << attackPower << std::endl;
    
    for (int i = 0; i < 5; ++i) {
        outSS << std::to_string(i) << "\t";
        outSS << inventory[i]->getGoldVal() << "\t";
        outSS << inventory[i]->getName() << "\t";
        outSS << inventory[i]->getDescription() << std::endl;
    }
    
    outputFile << outSS.str();
    outputFile.close();
    
}
void Player::Load(std::string filePath){
    std::ifstream inputFile(filePath);
    if(!inputFile.is_open())
        throw PlayerFileReadError("unable to open file: " + filePath);
    std::string line;
    std::stringstream inSS;
    int _x = 0;
    int _y = 0;
    int _health = 0;
    int _gold = 0;
    double _attackPower = 0.0;
    int _treasureIdx = 0;
    int _treasureGoldVal = 0;
    std::string _treasureName = "";
    std::string _treasureDescription = "";
    int i = 0;
    
    while (getline(inputFile, line)) {
        inSS.clear();
        inSS.str(line);
        switch (i) {
            case 0:
                inSS >> _x;
                ++i;
                break;
            case 1:
                inSS >> _y;
                ++i;
                break;
            case 2:
                inSS >> _health;
                ++i;
                break;
            case 3:
                inSS >> _gold;
                ++i;
                break;
            case 4:
                inSS >> _attackPower;
                ++i;
                break;
            
            default:
                inSS >> _treasureIdx;
                inSS >> _treasureGoldVal;
                inSS >> _treasureName;
                inSS << ignore
                getline(inSS, _treasureDescription);
//                inSS >> std::noskipws >> _treasureDescription >> std:: skipws;
                inventory[_treasureIdx] = new Treasure(_treasureGoldVal, _treasureName, _treasureDescription);
                ++i;
                break;
        }
    }
    
    playerLoc = gameMap->getTile(_x, _y);
    playerLoc->setPlayerTile();
    health = _health;
    gold = _gold;
    attackPower = _attackPower;    
}
//Player::Player(){
//    gameMap = nullptr;
//    playerLoc = nullptr;
//    health = 100;
//    gold = 0;
//    attackPower = 5;
//}
