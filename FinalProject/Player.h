#pragma once
#include "Map.h"
#include "Treasure.h"
//#include "Tile.h"

class PlayerFileReadError{
private:
    std::string message;
public:
    PlayerFileReadError(std::string m):message(m) {}
    std::string getMessage() { return message; }
};
class Player {
private:
    Map* gameMap;
    Tile* playerLoc;
    Treasure* inventory[50];
    int health;
    int gold;
    double attackPower;
    void Load(std::string);
public:
//    Player();
    Player(Map* _map, int, int);
    Player(Map*, std::string);
    
    Player();
    Tile* GetLoc();
//    ~Player();
    void Move(int, int);
    void Status();
    void Save(std::string);
    
    
};
