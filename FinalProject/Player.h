#pragma once
#include "Map.h"
//#include "Tile.h"


class Player {
private:
    char tileSymbol;
//    std::string previousTileFormat;
    Map* gameMap;
    Tile* playerLoc;
    int health;
    int gold;
    double attackPower;
    
public:
    Player(Map* _map, int, int);
//    ~Player();
    void move(int, int);
    Tile* getLoc();
};
