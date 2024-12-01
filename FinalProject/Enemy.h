//#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Player.h"

//class Player;

class Enemy {
private:
    int health;
    double attackPower;
    
public:
    Enemy(int _health, double _attackPower) {
        health = _health;
        attackPower = _attackPower;
    }

    std::string virtual GetType() = 0;
    
    void SetHealth(int _health) { health = _health; };
    int GetHealth() { return health; }
    int GetAttackPower() {
        double AP = attackPower;
        AP = AP + 0.5 - (AP < 0);
        return (int)AP;
    }
    int Attack(Player* pl) {
        return pl->TakeDamage(GetAttackPower());
    }
    int TakeDamage(int damage) {
        int newHealth = GetHealth() - damage >= 0 ? GetHealth() - damage: 0;
        int result = GetHealth() - newHealth;
        SetHealth(newHealth);
        return result;
    }
    virtual ~Enemy() {};
};
