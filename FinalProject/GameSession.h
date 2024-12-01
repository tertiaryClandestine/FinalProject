#pragma once
#include "Map.h"
#include "Player.h"


class InvalidSaveState{
private:
    std::string message;
public:
    InvalidSaveState(std::string m):message(m) {}
    std::string getMessage() { return message; }
};

class GameSession {
private:
    std::string saveSlotPath;
    Player* player;
    Map* map;
    bool SlotExists(int);
    int saveSlot;
    
    
public:
    GameSession();
    void New(std::string filePath = "gamedata/map.txt");
    void Save(int);
    void Load(int);
    void Delete(int);
    Player* GetPlayer();
    Map* GetMap();
    void Play();
    void Combat();
//    void Treasure();
    int DisplaySlots();
};
