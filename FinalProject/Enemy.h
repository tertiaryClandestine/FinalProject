#include <cstdlib>
#include <ctime>
#include "Player.h"

class Enemy {
private:
    int hitpoints;
    double attackPower;
    
public:
    Enemy(int _hitpoints, int _attackPower) {
        hitpoints = _hitpoints;
        attackPower = _attackPower;
    }
    virtual void attack(Player*) const = 0;
    int getHipoints() { return hitpoints; }
    double getAttackPower() { return attackPower; }
};
