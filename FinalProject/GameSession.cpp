#include "GameSession.h"
#include <filesystem>

bool fso_exists(const std::filesystem::path& p, std::filesystem::file_status s = std::filesystem::file_status{})
{
    return std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p);
}
bool GameSession::SlotExists(int slotID){
    namespace fs = std::filesystem;
    
    const fs::path slot{"savedata/" + std::to_string(slotID)};
    
    return fso_exists(slot);
}
GameSession::GameSession(){
    namespace fs = std::filesystem;
    
    const fs::path savedata{"savedata"};
    fs::create_directory(savedata);
    
    map = nullptr;
    player = nullptr;
    
}
void GameSession::New(){
//    Map map;
    try {
        map = new Map();
//            map->loadMap("gamedata/map.txt");
    }
    catch (MapFileReadError e) {
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    catch (TileInitializationError e) {
        std::cout << "Error Message: " << e.getMessage() << std::endl;
    }
    player = new Player(map, 48, 1);
//    Player player(&map, 48, 1);
}
void GameSession::Save(int saveSlot){
    if (map == nullptr || player == nullptr){
        throw InvalidSaveState("No active gamesession available to save");
    }
    if (!SlotExists(saveSlot)) {
        std::filesystem::create_directory("savedata/" + std::to_string(saveSlot));
    }
}


