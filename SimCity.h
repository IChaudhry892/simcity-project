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
    void displayFinalRegion();
    void displaySpecifiedRegion(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX);
    void displaySpecifiedPollution(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX);
    void intializeSimulation();
    void runSimulation();

    //for debugging
    void displayRegionPopulation();
    void displayRegionPollution();

    void spreadPollution();
    int getTotalPollution() const;
    int getTotalResidentialPopulation() const;
    int getTotalIndustrialPopulation() const;
    int getTotalCommercialPopulation() const;

    int getSpecifiedPollution(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const;
    int getSpecifiedResidentialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const;
    int getSpecifiedIndustrialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const;
    int getSpecifiedCommercialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const;

    int getAvailableWorkers() const;
    int getAvailableGoods() const;
    void updateAvailableWorkers(int amount);
    void updateAvailableGoods(int amount);
};

#endif