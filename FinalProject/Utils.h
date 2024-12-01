//
//  utils.h
//  FinalProject
//
//  Created by Joshua Ortmann on 2024-11-30.
//
#pragma once
#include <cstdlib>
#include <ctime>
#include <thread>
#include <filesystem>
#include <iostream>

//A collection of utility functions to supplement other functionality
//PrintTextWithDelay allows text to be shown to the user in a slower pace, creating a dramatic effect
//PromptUserToContinue Allows for pauses so the user can read the screen
//FSO_Exists helper function for checking if a folder or file exists
//RandVal generates a random value from 0 to 99 for various randomization needs

namespace utils {
    inline void PrintTextWithDelay(std::string input, int ms) {
        int stringLength = input.length();
        for (int i = 0; i < stringLength; ++i) {
            std::cout << input.at(i);
            std::cout.flush();
            std::this_thread::sleep_for (std::chrono::milliseconds(ms));
        }
    }
    inline bool PromptUserToContinue(){
        char dummyCin = ' ';
        while (dummyCin != 'c'){
//            PrintTextWithDelay("Press 'c' to continue\r\n", 60);
            std::cout << "Press 'c' to continue" << std::endl;
            std::cin >> dummyCin;
        }
        return true;
        
    }
    // sourced and customized from: https://en.cppreference.com/w/cpp/filesystem/exists
    inline bool FSO_Exists(const std::filesystem::path& p, std::filesystem::file_status s = std::filesystem::file_status{})
    {
        return std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p);
    }
    inline double RandVal(){
        return static_cast<double>(std::rand() % 100);
    }
}
