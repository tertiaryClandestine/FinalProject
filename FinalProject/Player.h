#pragma once
#include "Map.h"
#include "Treasure.h"
//#include "Tile.h"


class Player {
private:
    Map* gameMap;
    Tile* playerLoc;
    Treasure* inventory[50];
    int health;
    int gold;
    double attackPower;
    
public:
    Player(Map* _map, int, int);
    Player();
    Tile* GetLoc();
//    ~Player();
    void Move(int, int);
    void Status();
    void Save();
};
