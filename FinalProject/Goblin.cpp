//#pragma once
#include "Goblin.h"
#include "Player.h"

Goblin::Goblin(int _health, double _attackPower, double _treasureChance):Enemy(_health, _attackPower, _treasureChance){}
std::string Goblin::GetType() {
    return "Goblin";
}
Goblin::~Goblin(){}
