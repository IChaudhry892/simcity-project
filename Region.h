#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>
class Region{
    std::string regionFile;
    int timeLimit;
    int refreshRate;
    std::vector<std::vector<char>> regionLayout;
public:
    bool readConfigFile();
    bool readRegionInitial();

};

#endif