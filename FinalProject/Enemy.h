#include <cstdlib>
#include <ctime>

class Enemy {
private:
    int hitpoints;
    int attackPower;
    
public:
    Enemy(int _hitpoints, int _attackPower) {
        hitpoints = _hitpoints;
        attackPower = _attackPower;
    }
    virtual void attack() const = 0;
    int getHipoints();
    int getAttackPower();
};
