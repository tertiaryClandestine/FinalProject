#pragma once
#include "Enemy.h"
//#include "Utils.h"

class Skeleton : public Enemy {
private:
    
public:
    Skeleton(int = 10, double = 2.0, double = 1);
    std::string GetType();
    ~Skeleton();
};
