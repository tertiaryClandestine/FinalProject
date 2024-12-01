#pragma once
#include "GameSession.h"
#include <filesystem>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "Utils.h"
#include "Skeleton.h"
#include "Dragon.h"
#include "Goblin.h"
#include "Zombie.h"
#include "Spider.h"
 
const std::string PATH_SAVEDATA = "savedata";

//Need to check if the save data slot is already generated from a previous game session
bool GameSession::SlotExists(int slotID){
    namespace fs = std::filesystem;
    std::string slotPath = PATH_SAVEDATA + "/" + std::to_string(slotID);
    
    const fs::path slot{slotPath};
    
    return utils::FSO_Exists(slot);
}
GameSession::GameSession(){
    namespace fs = std::filesystem;
    const fs::path savedata{PATH_SAVEDATA};
    
    //Create the savedata directory since it's unlikely to have been already there
    fs::create_directory(savedata);
    
    map = nullptr;
    player = nullptr;
    saveSlot = 1;
    
}
//Prompt the user for the slot they want to place their new game, and throw errors if the map file is unable to be read.
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
//Save the gamesession by saving the player state and the map state seperately, but in the same slotID direcetory under savedata
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
//Load the gamesession by loading the player state and map state seperately, but from the same slotID directory under savedata
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
//Main play session loop for game
//A sigle charactor represents the movement up,down,left, or right
//if the player->gold value >= 10000, they win
//if the player->health value == 0 then game over
//when prompting for the direction input, I was having issues where successive letters were being submitted at once
//so I take the getline() of the input, then only look at the character at index 0 to determine the direction

void GameSession::Play(){
    char directionInput = ' ';
    Tile* prior;
    Tile* current;
    std::string line;
    while (player->GetHealth() > 0) {
        if (player->GetGold() >= 10000) {
            utils::PrintTextWithDelay("Congratulations! You've achieved the gold amount needed to clear this dungeon. \r\nYou can continue playing for more gold, or save and exit.\r\n", 60);
            utils::PromptUserToContinue();
        }
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
        //tile interaction logic
        //if tile is grass, tall grass, or an enemy tile, roll the chance of enemy and determine if combat is initiated
        //if player health reaches 0, then game over
        //if tile is treasure, then add that loot to player inventory, otherwise modify player attributes accordingly
        //if tile is lava, player takes damage
        current = player->GetLoc();
        if (current != prior) {
            current->setPlayerTile();
            Treasure* loot = nullptr;
            switch (current->getSymbol()) {
                case 'v':
                case 'w':
                case 't':
                    if (utils::RandVal() < current->getEnemyChance() * 100) {
                        Combat();
                        if (player->GetHealth() == 0) {
                            utils::PrintTextWithDelay("Your HP reached 0. Game over... \r\n", 30);
                            utils::PromptUserToContinue();
                            return;
                        }
                    }
                    break;
                case 'x':
                    loot = new Treasure();
                    if (loot != nullptr){
                        utils::PrintTextWithDelay("Treasure discovered!\r\n", 30);
                        loot->print();
                        player->PickupLoot(*loot);
                        delete loot;
                        loot = nullptr;
                        current->clearTile();
                        utils::PromptUserToContinue();
                    }
                    break;
                case 'l':
                    utils::PrintTextWithDelay("You step into lava, sustaining 10 damage\r\n", 30);
                    player->TakeDamage(10);
                    if (player->GetHealth() == 0){
                        utils::PrintTextWithDelay("Your HP reached 0. Game over... \r\n", 30);
                        utils::PromptUserToContinue();
                        return;
                    }
                    utils::PrintTextWithDelay("Your new HP is now: ", 30);
                    utils::PrintTextWithDelay(std::to_string(player->GetHealth()) + "\r\n", 30);
                    current->clearTile();
                    utils::PromptUserToContinue();
                    break;
                default:
                    break;
            }
            current->setPlayerTile();
        }
    }
}
//Display save slots to choose to load from
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
//turn based combat
//a random enemy is selected
//player goes first, and can choose to attack, block the next enemy attack, or run away
//if the enemy is defeated, loot is dropped and information about that loot is presented

void GameSession::Combat(){
    std::vector<Enemy*> NPCs;
    
    int randomNum = std::rand() % 5;
    switch (randomNum) {
        case 0:
            NPCs.push_back(new Dragon());
            break;
        case 1:
            NPCs.push_back(new Skeleton());
            break;
        case 2:
            NPCs.push_back(new Goblin());
            break;
        case 3:
            NPCs.push_back(new Spider());
            break;
        case 4:
            NPCs.push_back(new Zombie());
            break;
    }
    std::cout << "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
    std::cout << "You encounter a " << NPCs.at(0)->GetType() << " with " << NPCs.at(0)->GetHealth() << " HP and " << NPCs.at(0) ->GetAttackPower() << " AP" << std::endl;
    std::cout << "Your current status: " << std::endl << player->Status() << std::endl;
    utils::PromptUserToContinue();
    
    int turnCounter = 0;
    char inputSelection = ' ';
    std::string inputLine;
    do {
        if (turnCounter % 2 == 0){
            utils::PrintTextWithDelay("Your turn. Choose: 1. Attack, 2. Block, 3. Run away\r\n", 30);
            inputSelection = ' ';
            while (inputSelection != '1' && inputSelection != '2' && inputSelection != '3') {
                std::cin >> inputLine;
                inputSelection = inputLine.at(0);
                switch (inputSelection) {
                    case '1':
                        utils::PrintTextWithDelay("You attack the enemy, dealing ", 30);
                        utils::PrintTextWithDelay(std::to_string(player->Attack(NPCs.at(0))), 30);
                        utils::PrintTextWithDelay(" damage.\r\n", 30);
                        break;
                    case '2':
                        utils::PrintTextWithDelay("You prepare a defensive stance... \r\n", 30);
                        break;
                    case '3':
                        utils::PrintTextWithDelay("You run away successfully, returning to map... \r\n", 30);
                        utils::PromptUserToContinue();
                        break;
                    default:
                        break;
                }
            }
        } else {
            utils::PrintTextWithDelay("The enemy attacks you, dealing ", 30);
            if (inputSelection != '2') {
                utils::PrintTextWithDelay(std::to_string(NPCs.at(0)->Attack(player)), 30);
            } else {
                utils::PrintTextWithDelay(std::to_string(0), 30);
            }
            utils::PrintTextWithDelay(" damage.\r\n", 30);
            if (player->GetHealth() == 0) {
                return;
            }
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
    } while (player->GetHealth() > 0 && NPCs.at(0)->GetHealth() > 0 && inputSelection != '3');
    delete NPCs.at(0);
    NPCs.at(0) = nullptr;
}
