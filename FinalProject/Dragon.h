#pragma once
#include "Enemy.h"
//#include "Utils.h"

class Dragon : public Enemy {
private:
    
public:
    Dragon(int = 15, double = 7.0, double = 1);
    std::string GetType();
    ~Dragon();
};
