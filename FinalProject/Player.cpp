//#pragma once
#include "Player.h"
#include "Enemy.h"
//When starting a new game, this constructor is used
Player::Player(Map* _map, int _x, int _y){
    gameMap = _map;
    playerLoc = gameMap->getTile(_x, _y);
    playerLoc->setPlayerTile();
    health = 100;
    gold = 0;
    attackPower = 5;
    inventoryCount = 0;
}
//when loading a game from file, this constructor is used
Player::Player(Map* _map, std::string filePath) {
    gameMap = _map;
    Load(filePath);
}
Player::Player(std::string filePath) {
//    gameMap = _map;
    Load(filePath);
}
//Return the current map location tile the player is at
Tile* Player::GetLoc(){
    return playerLoc;
}
//Move the player to a new tile, unless that tile is a wall
void Player::Move(int deltaX, int deltaY){
    Tile* nextTile = gameMap->getTile(playerLoc->getX() + deltaX, playerLoc->getY() + deltaY);
    if (nextTile->getType() != "Wall"){
        playerLoc->setPlayerTile();
        playerLoc = nextTile;
        playerLoc->setPlayerTile();
    }
}
//Save the current state of player object to file
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
        outSS << inventory[i].getGoldVal() << "\t";
        outSS << inventory[i].getName() << "\t";
        outSS << inventory[i].getDescription() << std::endl;
    }
    
    outputFile << outSS.str();
    outputFile.close();
    
}
//Load the player state from file
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
                inventory[_treasureIdx] = Treasure(_treasureGoldVal, _treasureName, _treasureDescription);
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
std::string Player::Status(){
    std::stringstream outSS;
    outSS << "HP: " << health << "/100" << std::endl;
    outSS << std::fixed << std::setprecision(0);
    outSS << "AP: " << attackPower << std::endl;
    outSS << "GP: " << gold << std::endl;
    return outSS.str();
}
int Player::TakeDamage(int damage){
    int newHealth = GetHealth() - damage >= 0 ? GetHealth() - damage: 0;
    int damageSustained = GetHealth() - newHealth;
    SetHealth(newHealth);
    return damageSustained;
}
int Player::Attack(Enemy* enemy){
    return enemy->TakeDamage(GetAttackPower());
}
int Player::GetHealth(){
    return health;
}
int Player::GetAttackPower(){
    double AP = attackPower;
    AP = AP + 0.5 - (AP < 0);
    return (int)AP;
}
void Player::SetHealth(int _health){
    if (_health > 100) {
        health = 100;
    } else if (_health < 0) {
        health = 0;
    } else {
        health = _health;
    }
    
}
//logic for picking up loot, or modifying player attributes accordingly
void Player::PickupLoot(Treasure loot){
    if (loot.getName() == "Health Potion (50)") {
        utils::PrintTextWithDelay("You drink the potion, restoring up to 50 HP\r\n", 30);
        SetHealth(GetHealth() + 50);
        utils::PrintTextWithDelay("Your new HP is " + std::to_string(GetHealth()) + "\r\n", 30);
        return;
    } else if (loot.getName() == "Health Potion (10)") {
        utils::PrintTextWithDelay("You drink the potion, restoring up to 10 HP\r\n", 30);
        SetHealth(GetHealth() + 10);
        utils::PrintTextWithDelay("Your new HP is " + std::to_string(GetHealth()) + "\r\n", 30);
        return;
    } else if (loot.getName() == "AP up (2)") {
        utils::PrintTextWithDelay("Your AP is increased by 2\r\n", 30);
        SetAttackPower(GetAttackPower() + 2);
        utils::PrintTextWithDelay("Your AP is now: " + std::to_string(GetAttackPower()) + "\r\n", 30);
        return;
    } else if (loot.getName() == "AP up (1)") {
        utils::PrintTextWithDelay("Your AP is increased by 1\r\n", 30);
        SetAttackPower(GetAttackPower() + 1);
        utils::PrintTextWithDelay("Your AP is now: " + std::to_string(GetAttackPower()) + "\r\n", 30);
        return;
    }
    if (inventoryCount < 50) {
        inventory[inventoryCount] = loot;
        ++inventoryCount;
        utils::PrintTextWithDelay("Your gold increases by ", 30);
        utils::PrintTextWithDelay(std::to_string(loot.getGoldVal()), 30);
        utils::PrintTextWithDelay(" for a new total gold of ", 30);
        gold += loot.getGoldVal();
        utils::PrintTextWithDelay(std::to_string(gold) + "\r\n", 30);
    }
}
void Player::SetAttackPower(double _attackPower) {
    attackPower = _attackPower;
}
int Player::GetGold(){
    return gold;
}
