//#pragma once
#include "Map.h"

Map::Map(){
    for (int row = 0; row < 50; ++row){
        for (int col = 0; col < 50; ++col){
            tiles[row][col] = nullptr;
        }
    }
}
Map::~Map(){
    
}
Tile* Map::getTile(int x, int y){
    return tiles[x][y];
}


void Map::loadMap(std::string filePath){
    std::ifstream inputFile(filePath);
    std::string line;
    std::stringstream inSS;
    inSS >> std::noskipws;
    Tile *tile;
    char chTile;
    int row = 0;
    int col = 0;

    if (!inputFile.is_open()){
        throw MapFileReadError("unable to open file");
    } else {
        while (getline(inputFile, line)) {
            inSS.clear();
            inSS.str(line);
            while (inSS >> chTile) {
                tile = new Tile(chTile, row, col);
                if (tile == nullptr) {
                    throw TileInitializationError("error allocating tile pointer");
                }
                tiles[row][col] = tile;
                ++col;
            }
            col = 0;
            ++row;
        }
    }
    inputFile.close();

}
void Map::draw(Tile* tile) {
    int x = tile->getX();
    int y = tile->getY();
    
    int minRowsToDraw = 10;
    int minColsToDraw = 10;
    int startRow = 0;
    int startCol = 0;
    
    if (x <= minRowsToDraw / 2) {
        startRow = 0;
    } else if (x >= 50 - (minRowsToDraw /2)) {
        startRow = 50 - minRowsToDraw;
    } else {
        startRow = x - (minRowsToDraw / 2);
    }
    if (y <= minColsToDraw / 2) {
        startCol = 0;
    } else if (y >= 50 - (minColsToDraw /2)) {
        startCol = 50 - minColsToDraw;
    } else {
        startCol = y - (minColsToDraw / 2);
    }
    
    
    for (int row = startRow; row < startRow + minRowsToDraw; ++row) {
        for (int col = startCol; col < startCol + minColsToDraw; ++col) {
            std::cout << tiles[row][col]->getFormatting() << tiles[row][col]->getSymbol() << "\033[0m";
        }
        std::cout << std::endl;
    }
}