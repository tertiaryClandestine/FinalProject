#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Map.h"
#include "Player.h"
#include <filesystem>
#include "GameSession.h"

int DisplayMainMenu() {
    std::cout << "-------DungeonMaster-------" << std::endl;
    std::cout << "---------Main Menu---------" << std::endl;
//    if (!std::filesystem::is_empty("savedata")){
//        std::cout << "0. Continue" << std::endl;
//    }
    int selection;

    std::cout << "1. New" << std::endl;
    std::cout << "2. Load" << std::endl;
    std::cout << "3. Delete" << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << "Select from the above options by numerical entry:";
    std::cin >> selection;
    
    return selection;
}
int main(int argc, const char * argv[]) {
    
    GameSession gs;
    char inputSelection = ' ';
    
    while (inputSelection != 4) {
        inputSelection = DisplayMainMenu();
        switch (inputSelection) {
            case 1:
                gs.New();
                gs.Play();
                break;
            case 2:
//                gs.Load(<#int#>)
                break;
            case 3:
                break;
                
            default:
                break;
        }
    }
    
    
}
