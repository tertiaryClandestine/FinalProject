#pragma once
#include <string>
#include <cstdlib>
#include <ctime>

class Tile {
    /*
    x = Treasure
    v = Grass -- 25% chance of enemy
    w = Tall grass -- 40% chance of enemy
    @ = Wall
    t = Enemy
    l = Lava
    ! = Player spawn
      = Empty space -- 5% chance of enemy
    */
private:
    char symbol;
    std::string type;
    std::string formatting;
    bool isPlayerTile;
    bool treasure;
    int treasureVal;
    int enemyChance; //value is
    int x;
    int y;
    void setSymbol(const char&);
    void setType(const char&);
    void setFormatting(std::string);
    
    
    // Treasure treasure;
    
public:
    Tile(const char&, int, int);
    bool operator==(Tile&);
    char getSymbol();
    int getX();
    int getY();
    std::string getFormatting();
    void setPlayerTile();
    std::string getType();
    ~Tile();
    
};
