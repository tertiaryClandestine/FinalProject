//#pragma once
#include "Zombie.h"
#include "Player.h"

Zombie::Zombie(int _health, double _attackPower, double _treasureChance):Enemy(_health, _attackPower, _treasureChance){}
std::string Zombie::GetType() {
    return "Zombie";
}
Zombie::~Zombie(){}
