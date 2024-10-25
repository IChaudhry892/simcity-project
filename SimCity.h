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
    int availableWorkers;
    int availableGoods;

    std::vector<std::vector<char>> regionLayout;
    std::vector<std::vector<MapObject*>> region;

public:
    SimCity();

    bool readConfigFile();
    bool readRegionInitial();
    int getTimeLimit();
    int getRefreshRate();
    std::vector<std::vector<char>> getRegionLayout();
    std::vector<std::vector<MapObject*>> initializeRegion();
    void displayRegion();
    void intializeSimulation();
    void runSimulation();

    //for debugging
    void displayRegionPopulation();
    void displayRegionPollution();

    void spreadPollution();
    int getTotalResidentialPopulation() const;
    int getTotalIndustrialPopulation() const;
    int getTotalCommercialPopulation() const;

    int getAvailableWorkers() const;
    int getAvailableGoods() const;
    void updateAvailableWorkers(int amount);
    void updateAvailableGoods(int amount);
};

#endif