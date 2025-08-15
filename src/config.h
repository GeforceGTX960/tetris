#pragma once
#include "INIReader.h"
#include <string>

class Config{
    public:
        Config(const std::string &file);

        double gravity;
        double ARR;
        double DAS;
        int SDF;
};