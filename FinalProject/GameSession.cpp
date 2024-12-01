#pragma once
#include "GameSession.h"
#include <filesystem>
#include "Skeleton.h"
#include "Dragon.h"
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
        
        prior = player->GetLoc();
        std::cout << player->Status();
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
                utils::PrintTextWithDelay("Saving", 30);
                utils::PrintTextWithDelay("...", 500);
                Save(saveSlot);
                utils::PrintTextWithDelay(" Saved!\r\n", 45);
                utils::PromptUserToContinue();
                
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
            
//            std::cout << "rndVal" << rndVal;
            switch (current->getSymbol()) {
                case 'v':
                case 'w':
                case 't':
                    if (utils::RandVal() < current->getEnemyChance() * 100) {
                        Combat();
                    }
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
            std::cout << tmpPlayer->Status();
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
    
    int randomNum = std::rand() % 3;
    switch (randomNum) {
        case 0:
            NPCs.push_back(new Dragon());
            break;
        case 1:
            NPCs.push_back(new Skeleton());
            break;
        case 2:
            NPCs.push_back(new Skeleton(8, 4));
            break;
    }
    std::cout << "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
    std::cout << "You encounter a " << NPCs.at(0)->GetType() << " with " << NPCs.at(0)->GetHealth() << " HP and " << NPCs.at(0) ->GetAttackPower() << " AP" << std::endl;
    std::cout << "Your current status: " << std::endl << player->Status() << std::endl;
    utils::PromptUserToContinue();
    
    int turnCounter = 0;
    int inputSelection = 0;
    do {
        if (turnCounter % 2 == 0){
            utils::PrintTextWithDelay("Your turn. Choose: 1. Attack, 2. Block, 3. Run away\r\n", 30);
            inputSelection = 0;
            while (inputSelection < 1 || inputSelection > 3) {
                std::cin >> inputSelection;
                switch (inputSelection) {
                    case 1:
                        utils::PrintTextWithDelay("You attack the enemy, dealing ", 30);
                        utils::PrintTextWithDelay(std::to_string(player->Attack(NPCs.at(0))), 30);
                        utils::PrintTextWithDelay(" damage.\r\n", 30);
                        break;
                    case 2:
                        utils::PrintTextWithDelay("You prepare a defensive stance... \r\n", 30);
                        break;
                    case 3:
                        utils::PrintTextWithDelay("You run away successfully, returning to map... \r\n", 30);
                        utils::PromptUserToContinue();
                        break;
                    default:
                        break;
                }
            }
        } else {
            utils::PrintTextWithDelay("The enemy attacks you, dealing ", 30);
            if (inputSelection != 2) {
                utils::PrintTextWithDelay(std::to_string(NPCs.at(0)->Attack(player)), 30);
            } else {
                utils::PrintTextWithDelay(std::to_string(0), 30);
            }
            utils::PrintTextWithDelay(" damage.\r\n", 30);
        }
        
        if (NPCs.at(0)->GetHealth() == 0){
            Treasure* monsterLoot = NPCs.at(0)->Loot();
            utils::PrintTextWithDelay("Enemy defeated, ", 30);
            if (monsterLoot != nullptr){
                utils::PrintTextWithDelay(NPCs.at(0)->GetType() + " dropped the following loot: \r\n", 30);
                monsterLoot->print();
                player->PickupLoot(*monsterLoot);
            }
            utils::PrintTextWithDelay("returning to map... \r\n", 30);
            utils::PromptUserToContinue();
            player->GetLoc()->clearTile();
            break;
        }
        ++turnCounter;
    } while (/*(turnCounter % 2 == 1 || utils::PromptUserToContinue()) && */player->GetHealth() > 0 && NPCs.at(0)->GetHealth() > 0 && inputSelection != 3);
    delete NPCs.at(0);
    NPCs.at(0) = nullptr;
}
