#pragma once
#include "Enemy.h"
//#include "Utils.h"

class Spider : public Enemy {
private:
    
public:
    Spider(int = 12, double = 4.0, double = 1);
    std::string GetType();
    ~Spider();
};
