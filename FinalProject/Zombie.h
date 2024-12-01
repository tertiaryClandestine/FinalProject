#pragma once
#include "Enemy.h"
//#include "Utils.h"

class Zombie : public Enemy {
private:
    
public:
    Zombie(int = 5, double = 1.0, double = 1);
    std::string GetType();
    ~Zombie();
};
