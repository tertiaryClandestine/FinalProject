//#pragma once
#include "Skeleton.h"
#include "Player.h"

Skeleton::Skeleton(int _health, double _attackPower):Enemy(_health, _attackPower){
    
}

int Skeleton::Attack(Player* pl){
//    std::cout << "skeleton attack" << std::endl;
    return pl->TakeDamage(GetAttackPower());
}
int Skeleton::TakeDamage(int damage) {
//    std::cout << "skeleton damaged" << std::endl;
    int newHealth = GetHealth() - damage >= 0 ? GetHealth() - damage: 0;
    int result = GetHealth() - newHealth;
    SetHealth(newHealth);
    return result;
}
Skeleton::~Skeleton(){}
