//#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
//#include "Player.h"

class Player;

class Enemy {
private:
    int health;
    double attackPower;
    
public:
    Enemy(int _health, double _attackPower) {
        health = _health;
        attackPower = _attackPower;
    }
    int virtual Attack(Player*) = 0;
    int virtual TakeDamage(int) = 0;
    
    void SetHealth(int _health) { health = _health; };
    int GetHealth() { return health; }
    int GetAttackPower() {
        double AP = attackPower;
        AP = AP + 0.5 - (AP < 0);
        return (int)AP;
    }
    virtual ~Enemy() {};
};
