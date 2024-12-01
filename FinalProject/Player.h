#pragma once
#include "Map.h"
#include "Treasure.h"
#include <iomanip>
#include "Utils.h"
//#include "Enemy.h"
//#include "Tile.h"



class PlayerFileReadError{
private:
    std::string message;
public:
    PlayerFileReadError(std::string m):message(m) {}
    std::string getMessage() { return message; }
};

class Enemy;
class Player {
private:
    Map* gameMap;
    Tile* playerLoc;
    Treasure inventory[50];
    int inventoryCount;
    int health;
    int gold;
    double attackPower;
    void Load(std::string);
    void SetHealth(int);
public:
//    Player();
    Player(Map* _map, int, int);
    Player(Map*, std::string);
    Player(std::string);
    int Attack(Enemy*);
    int TakeDamage(int);
    int GetHealth();
    int GetAttackPower();
    void SetAttackPower(double);
//    int GetGold();
    void PickupLoot(Treasure);
    
    Player();
    Tile* GetLoc();
//    ~Player();
    void Move(int, int);
    std::string Status();
    void Save(std::string);
};
