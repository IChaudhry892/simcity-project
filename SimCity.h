#ifndef SIMCITY_H
#define SIMCITY_H

#include "MapObject.h"
#include "Zone.h"
#include "Earthquake.h"
#include <vector>
#include <string>
class SimCity{
    std::string regionFile;
    int timeLimit; //the max time steps the simulation will go through
    int refreshRate;
    int availableWorkers; //keeps track of available workers
    int availableGoods; //keeps track of available goods

    std::vector<std::vector<char>> regionLayout; // Character grid used to create the main region grid
    std::vector<std::vector<MapObject*>> region; // Main region grid

    Earthquake earthquake; //creates an Earthquake object with the default construtor (hasOccured is false, magnitude is 0.0)
    int earthquakeCenterX; //the earthquake center's X coordinate
    int earthquakeCenterY; //the earthquake center's Y coordinate

public:
    SimCity();
    ~SimCity();

    bool readConfigFile();
    bool readRegionInitial();
    int getTimeLimit();
    int getRefreshRate();
    std::vector<std::vector<char>> getRegionLayout();
    std::vector<std::vector<MapObject*>> initializeRegion(); //initalizes the region with MapObject objects
    void displayRegion();
    void displayFinalRegion(); //displays the final region with x and y axes
    void displaySpecifiedRegion(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX); //displays user-specified region
    void displaySpecifiedPollution(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX); //displays pollution map of user-specifified region
    bool intializeSimulation(); //calls initializeRegion() and displays the initial region state
    void runSimulation(); //executes the main game loop and the region analysis component

    void displayRegionPopulation(); //for debugging
    void displayRegionPollution(); //displays the region's pollution map

    void displayCityDestruction(); //displays a simple city destruction animation
    void applyEarthquakeDamage(double magnitude, int centerY, int centerX); //reduces zone populations in earthquake radius

    void spreadPollution(); //creates an initial pollution state then spreads pollution 3 times
    int getTotalPollution() const; //returns the region's total pollution
    int getTotalResidentialPopulation() const; //returns the residential zones' total pollution
    int getTotalIndustrialPopulation() const; //returns the industrial zones' total pollution
    int getTotalCommercialPopulation() const; //returns the commercial zones' total pollution

    int getSpecifiedPollution(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const;
    int getSpecifiedResidentialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const;
    int getSpecifiedIndustrialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const;
    int getSpecifiedCommercialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const;
    int getValidCoordinate(const std::string& prompt); //handles error if user inputs a non-integer coordinate during region analysis

    int getAvailableWorkers() const;
    int getAvailableGoods() const;
    void updateAvailableWorkers(int amount);
    void updateAvailableGoods(int amount);
};

#endif