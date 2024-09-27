#ifndef SIMCITY_H
#define SIMCITY_H

#include "MapObject.h"
#include "Zone.h"
#include <vector>
#include <string>
class SimCity{
    std::string regionFile;
    int timeLimit;
    int refreshRate;
    std::vector<std::vector<char>> regionLayout;
    std::vector<std::vector<MapObject*>> region;

public:
    bool readConfigFile();
    bool readRegionInitial();
    int getTimeLimit();
    int getRefreshRate();
    std::vector<std::vector<char>> getRegionLayout();
    std::vector<std::vector<MapObject*>> initializeRegion();
    void displayRegion();

};

#endif