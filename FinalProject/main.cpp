//#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Map.h"
#include "Player.h"
#include <filesystem>
#include "GameSession.h"

int DisplayMainMenu() {
    std::cout << "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
    std::cout << "╔═════════════════════════╗" << std::endl;
    std::cout << "║──────DungeonMaster──────║" << std::endl;
    std::cout << "║────────Main Menu────────║" << std::endl;
    std::cout << "╠═════════════════════════╣" << std::endl;
//    if (!std::filesystem::is_empty("savedata")){
//        std::cout << "0. Continue" << std::endl;
//    }
    int selection;

    std::cout << "║     ─══─ 1. New  ─══─   ║" << std::endl;
    std::cout << "║     ─══─ 2. Load ─══─   ║" << std::endl;
//    std::cout << "║--      3. Delete     -║" << std::endl;
    std::cout << "║     ─══─ 3. Quit ─══─   ║" << std::endl;
    std::cout << "╚═════════════════════════╝" << std::endl;
    std::cout << "Select from the above options by numerical entry:";
    std::cin >> selection;
    
    return selection;
}
int main(int argc, const char * argv[]) {
    
    std::srand(std::time(0));
    GameSession gs;
    int inputSelection = 0;
    
    while (inputSelection != 3) {
        inputSelection = DisplayMainMenu();
        switch (inputSelection) {
            case 1:
                gs.New();
                utils::PrintTextWithDelay("Starting new game... \r\n", 30);
                utils::PrintTextWithDelay("Traverse the dungeon, defeating enemies and collecting treasure... \r\n", 30);
                utils::PrintTextWithDelay("Collect 10,000 gold worth of treasure to win while fighting monsters and staying alive... \r\n", 30);
                utils::PrintTextWithDelay("Good luck!\r\n", 30);
                utils::PromptUserToContinue();
                gs.Play();
                break;
            case 2:
                inputSelection = gs.DisplaySlots();
                if (inputSelection != -1){
                    gs.Load(inputSelection);
                    gs.Play();
                    gs.Save(inputSelection);
                }
                inputSelection = 2;
                break;
//            case 3:
//                break;
                
            default:
                break;
        }
    }
    
    
}
