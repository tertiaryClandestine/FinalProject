#pragma once
#include "Enemy.h"
//#include "Utils.h"

class Goblin : public Enemy {
private:
    
public:
    Goblin(int = 12, double = 3.0, double = 1);
    std::string GetType();
    ~Goblin();
};
