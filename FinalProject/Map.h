#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include "Tile.h"

class MapFileReadError{
private:
    std::string message;
public:
    MapFileReadError(std::string m):message(m) {}
    std::string getMessage() { return message; }
};
class TileInitializationError{
private:
    std::string message;
public:
    TileInitializationError(std::string m):message(m) {}
    std::string getMessage() { return message; }
};

class Map {
private:
    Tile* tiles[50][50];
public:
    Map();
    void loadMap(std::string);
    void draw(Tile*);
    Tile* getTile(int,int);
    ~Map();
};
