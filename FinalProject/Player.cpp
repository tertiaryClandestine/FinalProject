//#pragma once
#include "Player.h"
Player::Player(Map* _map, int _x, int _y){
    gameMap = _map;
    playerLoc = gameMap->getTile(_x, _y);
    playerLoc->setPlayerTile();
    health = 100;
    gold = 0;
    attackPower = 5;
}
Tile* Player::getLoc(){
    return playerLoc;
}
void Player::move(int deltaX, int deltaY){
    Tile* nextTile = gameMap->getTile(playerLoc->getX() + deltaX, playerLoc->getY() + deltaY);
    if (nextTile->getType() != "Wall"){
        playerLoc->setPlayerTile();
        playerLoc = nextTile;
        playerLoc->setPlayerTile();
    }
    
}
Player::Player(){
    gameMap = nullptr;
    playerLoc = nullptr;
    health = 100;
    gold = 0;
    attackPower = 5;
}
