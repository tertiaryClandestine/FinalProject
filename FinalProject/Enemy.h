#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Player.h"
#include "Utils.h"

//class Player;
/*
 Base class for Dragon, Goblin, Skeleton, Spider, and Zombie enemies
 */

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
    
    //When an enemy dies in GameSession.Combat, loot is generated based on the enemy's treasureChance value
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
    
    //Return the damage value so the calling function can include it in its prompt to the user
    int Attack(Player* pl) {
        return pl->TakeDamage(GetAttackPower());
    }
    
    //Inflict damage upto the amount remaining. Don't want negative health values ;)
    int TakeDamage(int damage) {
        int newHealth = GetHealth() - damage >= 0 ? GetHealth() - damage: 0;
        int result = GetHealth() - newHealth;
        SetHealth(newHealth);
        return result;
    }
    

};
