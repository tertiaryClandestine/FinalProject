//#pragma once
#include "GameSession.h"
#include <filesystem>
#include "Skeleton.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include "Utils.h"

const std::string PATH_SAVEDATA = "savedata";

bool GameSession::SlotExists(int slotID){
    namespace fs = std::filesystem;
    std::string slotPath = PATH_SAVEDATA + "/" + std::to_string(slotID);
    
    const fs::path slot{slotPath};
    
    return utils::FSO_Exists(slot);
}
GameSession::GameSession(){
    namespace fs = std::filesystem;
    const fs::path savedata{PATH_SAVEDATA};
    
    fs::create_directory(savedata);
    
    map = nullptr;
    player = nullptr;
    saveSlot = 1;
    
}
void GameSession::New(std::string filePath){
    try {
        map = new Map(filePath);
    }
    catch (MapFileReadError e) {
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    catch (TileInitializationError e) {
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    player = new Player(map, 48, 1);
    std::cout << "Select the save slot (between 1 and 5) for this new game: ";
    std::cin >> saveSlot;
}
void GameSession::Save(int slotID){
    if (map == nullptr || player == nullptr){
        throw InvalidSaveState("No active gamesession available to save");
    }
    std::string slotDir = PATH_SAVEDATA + "/" + std::to_string(slotID);
    if (!SlotExists(slotID)) {
        std::filesystem::create_directory(slotDir);
    }
    try {
        map->Save(slotDir + "/map.txt");
        player->Save(slotDir + "/player.txt");
    }
    catch (MapFileReadError e){
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    catch (PlayerFileReadError e){
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
}
void GameSession::Load(int slotID){
    delete map;
    delete player;
    map = nullptr;
    player = nullptr;
    saveSlot = slotID;
    
    std::string slotDir = PATH_SAVEDATA + "/" + std::to_string(slotID);
    if (!SlotExists(slotID)) {
    }
    try {
        map = new Map(slotDir + "/map.txt");
        player = new Player(map, slotDir + "/player.txt");
    }
    catch (MapFileReadError e){
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    catch (PlayerFileReadError e){
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
}
Player* GameSession::GetPlayer(){
    return player;
}
Map* GameSession::GetMap(){
    return map;
}
void GameSession::Play(){
    char directionInput = ' ';
    Tile* prior;
    Tile* current;
    std::string line;
    while (true) {
        std::cout << "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
        map->Draw(player->GetLoc());
        player->Status();
        prior = player->GetLoc();
        std::cout << "Movement options: a=left, w=up, s=down, d=right...x=exit" << std::endl;
        std::cin >> line;
        directionInput = line[0];
        switch (directionInput) {
            case 'w':
                player->Move(-1, 0);
                break;
            case 's':
                player->Move(1, 0);
                break;
            case 'd':
                player->Move(0, 1);
                break;
            case 'a':
                player->Move(0, -1);
                break;
            case 'x':
                Save(saveSlot);
                break;
            default:
                break;
        }
        if (directionInput == 'x') {
            break;
        }
        current = player->GetLoc();
        if (current != prior) {
            current->setPlayerTile();
            switch (current->getSymbol()) {
                case 't':
                    Combat();
                    break;
                    
                default:
                    break;
            }
            current->setPlayerTile();
        }
        
    }
}
int GameSession::DisplaySlots(){
    namespace fs = std::filesystem;
    const fs::path savedata{PATH_SAVEDATA};
    
    Player* tmpPlayer;
    int selection = 0;
    std::cout << "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
    for (int i = 1; i < 6; ++i){
        if (SlotExists(i)) {
            tmpPlayer = new Player(PATH_SAVEDATA + "/" + std::to_string(i) + "/player.txt");
            std::cout << "SlotID: " << i << std::endl;
            tmpPlayer->Status();
            delete tmpPlayer;
            tmpPlayer = nullptr;
            std::cout << "------------------------" << std::endl;
        } else {
            if (i == 1){
                std::cout << "No save slots" << std::endl;
                break;
            }
        }
    }
    std::cout << "Pick the slot to load by the SlotID (-1 goes back to prior menu): ";
    std::cin >> selection;
    return selection;

}
void GameSession::Combat(){
    std::vector<Enemy*> NPCs;
    std::srand(std::time(0));
    int randomNum = std::rand() % 3;
    switch (randomNum) {
        case 0:
            NPCs.push_back(new Skeleton(10, 3));
            break;
        case 1:
            NPCs.push_back(new Skeleton(12, 2));
            break;
        case 2:
            NPCs.push_back(new Skeleton(8, 4));
            break;
    }
    std::cout << "You encounter a skeleton with " << NPCs.at(0)->GetHealth() << " HP and " << NPCs.at(0) ->GetAttackPower() << " AP" << std::endl;
    utils::PromptUserToContinue();
    
    int turnCounter = 0;
    do {
        if (turnCounter % 2 == 0){
            utils::PrintTextWithDelay("You attack the enemy, dealing ", 60);
            utils::PrintTextWithDelay(std::to_string(player->Attack(NPCs.at(0))), 60);
        } else {
            utils::PrintTextWithDelay("The enemy attacks you, dealing ", 60);
            utils::PrintTextWithDelay(std::to_string(NPCs.at(0)->Attack(player)),60);
        }
        utils::PrintTextWithDelay(" damage.\r\n", 60);
        if (NPCs.at(0)->GetHealth() == 0){
            utils::PrintTextWithDelay("Enemy defeated, returning to map... ", 60);
            utils::PromptUserToContinue();
            delete NPCs.at(0);
            NPCs.at(0) = nullptr;
            break;
        }
        ++turnCounter;
    } while (utils::PromptUserToContinue() && player->GetHealth() > 0 && NPCs.at(0)->GetHealth() > 0);



}
