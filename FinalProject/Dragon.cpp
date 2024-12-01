//#pragma once
#include "Dragon.h"
#include "Player.h"

Dragon::Dragon(int _health, double _attackPower, double _treasureChance):Enemy(_health, _attackPower, _treasureChance){}
std::string Dragon::GetType() {
    return "Dragon";
}
Dragon::~Dragon(){}
