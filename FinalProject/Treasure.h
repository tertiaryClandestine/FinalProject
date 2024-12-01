#pragma once
#include <string>
class Treasure {
private:
    int goldVal;
    std::string name;
    std::string description;
public:
    Treasure();
    Treasure(int, std::string, std::string);
    
    int getGoldVal();
    std::string getName();
    std::string getDescription();
};

