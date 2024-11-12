#include <iostream>
#include <sstream>
#include <string>
#include "Map.h"
#include "Player.h"

void DisplayMenu() {
    // std::ostringstream outSS;
    std::cout << "------------------------TitleMenu------------------------" << std::endl;
    std::cout << "----------------------1. Continue------------------------" << std::endl;
    std::cout << "------------------------2. Load--------------------------" << std::endl;
    std::cout << "------------------------3. New---------------------------" << std::endl;
    std::cout << "------------------------4. Quit--------------------------" << std::endl;
//    std::cout << outSS;
}


int main(int argc, const char * argv[]) {
    
    // std::cout << "\033[1;31mbold red text\033[0m\n";
    // std::cout << "\033[5mBlink" << std::endl;
//    DisplayMenu();
    Map* gameMap = nullptr;
    try {
        gameMap->loadMap("/Users/joshuaortmann/cosc1437/Projects/FinalProject/FinalProject/data/map.txt");
    }
    catch (MapFileReadError e) {
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    catch (TileInitializationError e) {
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
////    
//    int pos_x = 48;
//    int pos_y = 1;
  
    Player pl(gameMap, 48, 1);
    
//    std::cout << "\033[42m" << "testText" << "\033[0m" << std::endl;
//    std::cout << "\033[7m" << "testText2" << std::endl;
    
    gameMap->draw(pl.getLoc());
    std::cout << std::endl << std::endl << std::endl;
    char directionInput;
    std::cout << "Movement options: a=left, w=up, s=down, d=right" << std::endl;
    std::cout << "pl.x: " << pl.getLoc()->getX() << std::endl;
    std::cout << "pl.y: " << pl.getLoc()->getY() << std::endl;
    std::cin >> directionInput;
    while (directionInput != 'q') {
        switch (directionInput) {
            case 'w':
                pl.move(-1, 0);
                break;
            case 's':
                pl.move(1, 0);
                break;
            case 'd':
                pl.move(0, 1);
                break;
            case 'a':
                pl.move(0, -1);
                break;
            default:
                break;
        }
//        pl.move(gameMap.getTile(pos_x, pos_y));
        gameMap->draw(pl.getLoc());
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "Movement options: a=left, w=up, s=down, d=right" << std::endl;
        std::cout << "pl.x: " << pl.getLoc()->getX() << std::endl;
        std::cout << "pl.y: " << pl.getLoc()->getY() << std::endl;
        std::cin >> directionInput;
    }
    
}
