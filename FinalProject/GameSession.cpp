#include "GameSession.h"
#include <filesystem>

const std::string PATH_SAVEDATA = "savedata";

// sourced and customized from: https://en.cppreference.com/w/cpp/filesystem/exists
bool fso_exists(const std::filesystem::path& p, std::filesystem::file_status s = std::filesystem::file_status{})
{
    return std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p);
}
bool GameSession::SlotExists(int slotID){
    namespace fs = std::filesystem;
    std::string slotPath = PATH_SAVEDATA + "/" + std::to_string(slotID);
    
    const fs::path slot{slotPath};
    
    return fso_exists(slot);
}
GameSession::GameSession(){
    namespace fs = std::filesystem;
    const fs::path savedata{PATH_SAVEDATA};
    
    fs::create_directory(savedata);
    
    map = nullptr;
    player = nullptr;
    
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
    
//    map = new Map(
    std::string slotDir = PATH_SAVEDATA + "/" + std::to_string(slotID);
    if (!SlotExists(slotID)) {
        std::filesystem::create_directory(slotDir);
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
