#ifndef SIMCITY_H
#define SIMCITY_H

#include <vector>
#include <string>
class SimCity{
    std::string regionFile;
    int timeLimit;
    int refreshRate;
    std::vector<std::vector<char>> regionLayout;

public:
    bool readConfigFile();
    bool readRegionInitial();

};

#endif