//#pragma once
#include "Map.h"

Map::Map(std::string filePath){
    for (int row = 0; row < 50; ++row){
        for (int col = 0; col < 50; ++col){
            tiles[row][col] = nullptr;
        }
    }
    Load(filePath);
}
Map::~Map(){
    
}
Tile* Map::getTile(int x, int y){
    return tiles[x][y];
}

//Load mapfile into memory
void Map::Load(std::string filePath){
    std::ifstream inputFile(filePath);
    std::string line;
    std::stringstream inSS;
    inSS >> std::noskipws;
    Tile *tile;
    char chTile;
    int row = 0;
    int col = 0;

    if (!inputFile.is_open())
        throw MapFileReadError("unable to open file: " + filePath);
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
    inputFile.close();

}
//Save map state to memory
void Map::Save(std::string filePath){
    std::ofstream outputFile(filePath);
//    std::string line;
    std::stringstream outSS;
    int row = 0;
    int col = 0;
    
    Tile* playerTile = nullptr;
    
    if(!outputFile.is_open())
        throw MapFileReadError("unable to create file: " + filePath);
    for (row = 0; row < 50; ++row){
        for (col = 0; col < 50; ++col) {
            if (tiles[row][col]->getSymbol() == '!'){
                playerTile = tiles[row][col];
                tiles[row][col]->setPlayerTile();
            }
            outSS << tiles[row][col]->getSymbol();
        }
        outSS << std::endl;
    }
    outputFile << outSS.str();
    outputFile.close();
    playerTile->setPlayerTile();
    
}
//Draw the map to screen based on the input tile (usually the player tile)
void Map::Draw(Tile* tile) {
    int x = tile->getX();
    int y = tile->getY();
    std::stringstream outSS;
    
    int minRowsToDraw = 10;
    int minColsToDraw = 30;
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
            outSS << tiles[row][col]->getFormatting() << tiles[row][col]->getSymbol() << "\033[0m";
//            std::cout << tiles[row][col]->getFormatting() << tiles[row][col]->getSymbol() << "\033[0m";
        }
        outSS << std::endl;
    }
    std::cout << outSS.str();
}
