//#pragma once
#include "Player.h"
Player::Player(Map* _map, int _x, int _y){
    gameMap = _map;
    playerLoc = gameMap->getTile(_x, _y);
    playerLoc->setPlayerTile();
}
Tile* Player::getLoc(){
    return playerLoc;
}
void Player::move(int deltaX, int deltaY){
    if (gameMap->getTile(playerLoc->getX() + deltaX, playerLoc->getY() + deltaY)->getType() != "Wall"){
        playerLoc->setPlayerTile();
        playerLoc = gameMap->getTile(playerLoc->getX() + deltaX, playerLoc->getY() + deltaY);
        playerLoc->setPlayerTile();
    }
    
}
