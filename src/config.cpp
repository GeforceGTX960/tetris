#include "config.h"
#include <iostream>

Config::Config(const std::string &file){
    INIReader reader(file);

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'config.ini'\n";

        gravity = 0.02;
        ARR = 0.05;
        DAS = 0.15;
        SDF = 9;

        return;
    }

    gravity = reader.GetReal("Game", "gravity", 0.02);
    ARR = reader.GetReal("Game", "ARR", 0.05);
    DAS = reader.GetReal("Game", "DAS", 0.15);
    SDF = reader.GetInteger("Game", "SDF", 9);
}