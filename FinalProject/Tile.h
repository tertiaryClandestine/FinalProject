#pragma once
#include <string>
#include <cstdlib>
#include <ctime>

class Tile {
    /*
    x = Treasure
    v = Grass -- 5% chance of enemy
    w = Tall grass -- 10% chance of enemy
    @ = Wall
    t = Enemy
    l = Lava
    ! = Player spawn
      = Empty space -- 1% chance of enemy
    */
private:
    char symbol;
    std::string type;
    std::string formatting;
    bool isPlayerTile;
    bool treasure;
    int treasureVal;
    double enemyChance;
    int x;
    int y;
    void setType(const char&);
    void setSymbol(const char&);
    void setFormatting(std::string);
    
    
    // Treasure treasure;
    
public:
    Tile(const char&, int, int);
    bool operator==(Tile&);
    char getSymbol();
    int getX();
    int getY();
    void clearTile();
    std::string getFormatting();
    void setPlayerTile();
    std::string getType();
    double getEnemyChance();
    ~Tile();
    
};
