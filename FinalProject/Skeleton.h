#pragma once
#include "Enemy.h"
//#include "Utils.h"

class Skeleton : public Enemy {
private:
    
public:
    Skeleton(int, double);
//    int Attack(Player*);
    int TakeDamage(int);
    std::string GetType();
    ~Skeleton();
};
