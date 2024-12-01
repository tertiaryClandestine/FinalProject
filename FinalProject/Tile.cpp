//#pragma once
#include "Tile.h"
    /*
    x = Treasure
    v = Grass -- 5% chance of enemy
    w = Tall grass -- 8% chance of enemy
    @ = Wall
    t = Enemy
    l = Lava
    ! = Player spawn
      = Empty space -- 1% chance of enemy
    */
Tile::Tile(const char& c, int _x, int _y) {
    enemyChance = 0;
    setSymbol(c);
    setType(c);
    x = _x;
    y = _y;
}
char Tile::getSymbol() {
    char result;
    if (isPlayerTile) {
        result = '!';
    } else {
        result = symbol;
    }
    return result;
}
std::string Tile::getFormatting(){
    std::string result;
    if (isPlayerTile) {
        result = "\033[7m";
    } else {
        result = formatting;
    }
    return result;
}
void Tile::setSymbol(const char& c = ' '){
    symbol = c;
}
void Tile::setType(const char& c = ' '){
    switch (c){
        case 'x':
            type = "Treasure";
            setFormatting("\033[8;103m");
            break;
        case 'v':
            type = "Grass";
            setFormatting("\033[8;102m");
            enemyChance = 0.07;
            break;
        case 'w':
            type = "Tall grass";
            setFormatting("\033[8;106m");
            enemyChance = 0.10;
            break;
        case '@':
            type = "Wall";
            setFormatting("\033[8;7m");
            break;
        case 't':
            type = "Enemy";
            setFormatting("\033[8;41m");
            enemyChance = 1;
            break;
        case 'l':
            type = "Lava";
            setFormatting("\033[8;105m");
            break;
        case ' ':
            type = "Empty space";
            setFormatting("\033[8;0m");
            enemyChance = 0.03;
            break;
//    case '!':
//        type = "Player";
//        setFormatting("\033[7m");
//        break;
    };
}
void Tile::setFormatting(std::string format = "\033[0m"){
    formatting = format;
}
int Tile::getX(){
    return x;
}
int Tile::getY(){
    return y;
}
void Tile::setPlayerTile(){
    isPlayerTile = !isPlayerTile;
}
std::string Tile::getType(){
    return type;
}
bool Tile::operator==( Tile& rhs){
    if (this->getX() == rhs.getX() && this->getY() == rhs.getY()) {
        return true;
    } else {
        return false;
    }
}
void Tile::clearTile(){
    if (symbol == 't' || symbol == 'x'){
        setType(' ');
        setSymbol(' ');
    }
}
double Tile::getEnemyChance() {
    return enemyChance;
}
