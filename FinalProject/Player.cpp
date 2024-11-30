//#pragma once
#include "Player.h"
Player::Player(Map* _map, int _x, int _y){
    gameMap = _map;
    playerLoc = gameMap->getTile(_x, _y);
    playerLoc->setPlayerTile();
    health = 100;
    gold = 0;
    attackPower = 5;
    inventoryCount = 0;
}
Player::Player(Map* _map, std::string filePath) {
    gameMap = _map;
    Load(filePath);
}
Player::Player(std::string filePath) {
//    gameMap = _map;
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
    if (nextTile->getType() == "Enemy") {
//        Combat();
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
    outSS << inventoryCount << std::endl;
    
    for (int i = 0; i < inventoryCount; ++i) {
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
    int _treasureCount = 0;
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
            case 5:
                inSS >> _treasureCount;
                ++i;
                break;
            
            default:
                inSS >> _treasureIdx;
                inSS >> _treasureGoldVal;
                inSS >> _treasureName;
//                inSS << ignore
                inSS.ignore();
                getline(inSS, _treasureDescription);
//                inSS >> std::noskipws >> _treasureDescription >> std:: skipws;
                inventory[_treasureIdx] = new Treasure(_treasureGoldVal, _treasureName, _treasureDescription);
                ++i;
                break;
        }
    }
    
    health = _health;
    gold = _gold;
    attackPower = _attackPower;
    inventoryCount = _treasureCount;
    
    if (gameMap != nullptr) {
        playerLoc = gameMap->getTile(_x, _y);
        playerLoc->setPlayerTile();
    }   

}
void Player::Status(){
    std::stringstream outSS;
    outSS << "Health: " << std::to_string(health) << "/100" << std::endl;
    outSS << std::fixed << std::setprecision(0);
    outSS << "Attack Power: " << std::to_string(attackPower) << std::endl;
    outSS << "Gold: " << std::to_string(gold) << std::endl;
    std::cout << outSS.str();
}
//Player::Player(){
//    gameMap = nullptr;
//    playerLoc = nullptr;
//    health = 100;
//    gold = 0;
//    attackPower = 5;
//}
