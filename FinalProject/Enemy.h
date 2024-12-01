#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Player.h"
#include "Utils.h"

//class Player;

class Enemy {
private:
    int health;
    double attackPower;
    double treasureChance;
    void SetHealth(int _health) { health = _health; }
    
public:
    Enemy(int _health, double _attackPower, double _treasureChance) {
        health = _health;
        attackPower = _attackPower;
        treasureChance = _treasureChance;
    }
    
    virtual ~Enemy() {};

    std::string virtual GetType() = 0;
    
    int GetHealth() { return health; }
    
    Treasure* Loot() {
        double rndVal = utils::RandVal();
        if (rndVal < treasureChance * 100) {
            return new Treasure();
        } else {
            return nullptr;
        }
    }
    
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
    

};
