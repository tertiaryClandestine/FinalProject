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
//    ~Player();
    void move(int, int);
    Tile* getLoc();
    void printStatus();
};
