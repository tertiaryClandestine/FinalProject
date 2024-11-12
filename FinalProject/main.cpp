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
    
    Map gameMap;
    try {
        gameMap.loadMap("/Users/joshuaortmann/cosc1437/Projects/FinalProject/FinalProject/data/map.txt");
    }
    catch (MapFileReadError e) {
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    catch (TileInitializationError e) {
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
  
    Player pl(&gameMap, 48, 1);
    
    gameMap.draw(pl.getLoc());
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
        gameMap.draw(pl.getLoc());
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "Movement options: a=left, w=up, s=down, d=right" << std::endl;
        std::cout << "pl.x: " << pl.getLoc()->getX() << std::endl;
        std::cout << "pl.y: " << pl.getLoc()->getY() << std::endl;
        std::cin >> directionInput;
    }
    
}
