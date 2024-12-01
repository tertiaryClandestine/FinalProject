//#pragma once
#include "Skeleton.h"
#include "Player.h"

Skeleton::Skeleton(int _health, double _attackPower, double _treasureChance):Enemy(_health, _attackPower, _treasureChance){}
std::string Skeleton::GetType() {
    return "Skeleton";
}
Skeleton::~Skeleton(){}
