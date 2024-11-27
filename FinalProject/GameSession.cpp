#include "GameSession.h"
#include <filesystem>

const std::string PATH_SAVEDATA = "savedata";

bool fso_exists(const std::filesystem::path& p, std::filesystem::file_status s = std::filesystem::file_status{})
{
    return std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p);
}
bool GameSession::SlotExists(int slotID){
    namespace fs = std::filesystem;
    
    const fs::path slot{PATH_SAVEDATA + "/" + std::to_string(slotID)};
    
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
void GameSession::Save(int saveSlot){
    if (map == nullptr || player == nullptr){
        throw InvalidSaveState("No active gamesession available to save");
    }
    if (!SlotExists(saveSlot)) {
        std::filesystem::create_directory(PATH_SAVEDATA + "/" + std::to_string(saveSlot));
    }
    try {
        map->Save(PATH_SAVEDATA + "/" + std::to_string(saveSlot) + "/map.txt");
    }
    catch (MapFileReadError e){
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
}
void GameSession::Load(int saveSlot){
    delete map;
    delete player;
    map = nullptr;
    player = nullptr;
    
//    map = new Map(
    if (!SlotExists(saveSlot)) {
        std::filesystem::create_directory(PATH_SAVEDATA + "/" + std::to_string(saveSlot));
    }
    try {
        map = new Map(PATH_SAVEDATA + "/" + std::to_string(saveSlot) + "/map.txt");
    }
    catch (MapFileReadError e){
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    
    
    
    /*
     load the data from the slot into memory
     */
}
Player* GameSession::GetPlayer(){
    return player;
}
Map* GameSession::GetMap(){
    return map;
}
