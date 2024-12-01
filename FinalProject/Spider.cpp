//#pragma once
#include "Spider.h"
#include "Player.h"

Spider::Spider(int _health, double _attackPower, double _treasureChance):Enemy(_health, _attackPower, _treasureChance){}
std::string Spider::GetType() {
    return "Spider";
}
Spider::~Spider(){}
