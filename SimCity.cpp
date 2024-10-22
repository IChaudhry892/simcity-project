#include "SimCity.h"
#include "MapObject.h"
#include "Zone.h"
#include "Road.h"
#include "PowerPlant.h"
#include "Powerline.h"
#include "RoadPowerline.h"
#include "ResidentialZone.h"
#include "IndustrialZone.h"
#include "CommercialZone.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

SimCity::SimCity() : availableWorkers(0), availableGoods(0) {}

bool SimCity::readConfigFile(){
    string configFileName;
    cout << "Enter config file name: ";
    cin >> configFileName;

    ifstream configFile(configFileName);
    if (!configFile.is_open()){
        cout << "Could not open config file: " << configFileName << "." << endl;
        return false;
    }
    if (configFile.is_open()){
        string line;
        while(getline(configFile, line)){
            if (line.find("Region Layout:") != string::npos){
                regionFile = line.substr(line.find(":") + 2);
            }
            if (line.find("Time Limit:") != string::npos){
                timeLimit = stoi(line.substr(line.find(":") + 2));
            }
            if (line.find("Refresh Rate:") != string::npos){
                refreshRate = stoi(line.substr(line.find(":") + 2));
            }
        }
        configFile.close();
    }
    return true;
}

bool SimCity::readRegionInitial(){
    ifstream regionFileStream(regionFile);
    if (!regionFileStream.is_open()){
        cout << "Could not open region file: " << regionFile << endl;
        return false;
    }
    if (regionFileStream.is_open()){
        string line;
        while(getline(regionFileStream, line)){
            vector<char> row;
            for(char cell : line){
                if (cell != ' ' && cell != ','){
                    row.push_back(cell);
                }
            }
            regionLayout.push_back(row);

        }
        regionFileStream.close();
    }
    return true;
}

int SimCity::getTimeLimit(){
    return timeLimit;
}
int SimCity::getRefreshRate(){
    return refreshRate;
}
std::vector<std::vector<char>> SimCity::getRegionLayout(){
    return regionLayout;
}

std::vector<std::vector<MapObject*>> SimCity::initializeRegion(){
    for (int i = 0; i < regionLayout.size(); i++){
        vector<MapObject*> regionRow;
        for (int j = 0; j < regionLayout[i].size(); j++){
            char cell = regionLayout[i][j];
            if (cell == '-'){
                regionRow.push_back(new Road());
            } else if (cell == 'P'){
                regionRow.push_back(new PowerPlant());
            } else if (cell == 'T'){
                regionRow.push_back(new Powerline());
            } else if (cell == '#'){
                regionRow.push_back(new RoadPowerline());
            } else if (cell == 'R'){
                regionRow.push_back(new ResidentialZone());
            } else if (cell == 'I'){
                regionRow.push_back(new IndustrialZone());
            } else if (cell == 'C'){
                regionRow.push_back(new CommercialZone());
            } else{
                regionRow.push_back(nullptr);
            }
        }
        region.push_back(regionRow);
    }
    return region;
}

void SimCity::displayRegion(){
    cout << "Region Map:" << endl;
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            MapObject* cell = region[i][j];
            Zone* zone = dynamic_cast<Zone*>(cell);
            if (zone != nullptr){
                if (zone->getPopulation() > 0){
                    cout << zone->getPopulation() << "\t";
                } else{
                    cout << zone->getType() << "\t";
                }
            } else if (cell != nullptr){
                cout << cell->getType() << "\t";
            } else{
                cout << " \t";
            }
        }
        cout << endl;
    }
}

void SimCity::intializeSimulation(){
    if (!readConfigFile()){
        cout << "Failed to read the config file. Exiting simulation." << endl;
        return;
    }

    if (!readRegionInitial()){
        cout << "Failed to read the region layout. Exiting simulation." << endl;
        return;
    }

    initializeRegion();

    cout << "Simulation initialized successfully." << endl;
    displayRegion();

    //for debugging
    displayRegionPopulation();
    displayRegionPollution();
}

void SimCity::runSimulation(){
    for(int step = 0; step < timeLimit; step++){
        cout << "Time step: " << step + 1 << endl;
        cout << "Avaialble workers: " << availableWorkers << endl;
        cout << "Avaialble goods: " << availableGoods << endl;

        //count availableWorkers at start of time step
        int oldAvailableWorkers = 0;
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                ResidentialZone* zone = dynamic_cast<ResidentialZone*>(region[i][j]);
                if (zone != nullptr){
                    oldAvailableWorkers += zone->getPopulation();
                }
            }
        }

        //count availableGoods at start of time step
        int oldAvailableGoods = 0;
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                IndustrialZone* zone = dynamic_cast<IndustrialZone*>(region[i][j]);
                if (zone != nullptr){
                    oldAvailableGoods += zone->getPopulation();
                }
            }
        }

        //create a temporary grid to store new population values
        vector<vector<int>> newPopulations(region.size(), vector<int>(region[0].size(), -1));

        // //evaluate growth and store results in newPopulations
        // for (int i = 0; i < region.size(); i++){
        //     for (int j = 0; j < region[i].size(); j++){
        //         ResidentialZone* zone = dynamic_cast<ResidentialZone*>(region[i][j]);
        //         if (zone != nullptr){
        //             int currentPopulation = zone->getPopulation();
        //             int newPopulation = zone->evaluateGrowth(region, i, j, *this);
        //             newPopulations[i][j] = newPopulation;
        //         }
        //     }
        // }

        //evaluate residential growth and store results in newPopulations
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                ResidentialZone* residentialZone = dynamic_cast<ResidentialZone*>(region[i][j]);
                if (residentialZone != nullptr){
                    int newPopulation = residentialZone->evaluateGrowth(region, i, j, *this);
                    newPopulations[i][j] = newPopulation;
                }
            }
        }

        //evaluate industrial growth and store results in newPopulations
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(region[i][j]);
                if (industrialZone != nullptr){
                    int newPopulation = industrialZone->evaluateGrowth(region, i, j, *this);
                    newPopulations[i][j] = newPopulation;
                }
            }
        }

        // //apply growth from newPopulations to actual region
        // for (int i = 0; i < region.size(); i++){
        //     for (int j = 0; j < region[i].size(); j++){
        //         ResidentialZone* zone = dynamic_cast<ResidentialZone*>(region[i][j]);
        //         if (zone != nullptr){
        //             zone->setPopulation(newPopulations[i][j]);
        //         }
        //     }
        // }

        //apply residential & industrial growth from newPopulations to actual region
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                ResidentialZone* residentialZone = dynamic_cast<ResidentialZone*>(region[i][j]);
                if (residentialZone != nullptr && newPopulations[i][j] != -1){
                    residentialZone->setPopulation(newPopulations[i][j]);
                }

                IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(region[i][j]);
                if (industrialZone != nullptr && newPopulations[i][j] != -1){
                    industrialZone->setPopulation(newPopulations[i][j]);
                }
            }
        }

        // bool growthOcurred = false; //track if growth happens in this time step
        // for (int i = 0; i < region.size(); i++){
        //     for (int j = 0; j < region[i].size(); j++){
        //         Zone* zone = dynamic_cast<Zone*>(region[i][j]);
        //         if (zone != nullptr){
        //             zone->growFunction(region, i, j, *this);
        //         }
        //     }
        // }

        // while (true){
        //     // growthOcurred = false;
        //     struct GrowthCandidate{
        //         int x, y, population, adjPop;
        //         ResidentialZone* zone;
        //     };

        //     GrowthCandidate bestCandidate = {-1, -1, -1, -1, nullptr};

        //     //search region to find best growth candidate
        //     for (int i = 0; i < region.size(); i++){
        //         for (int j = 0; j < region[i].size(); j++){
        //             ResidentialZone* zone = dynamic_cast<ResidentialZone*>(region[i][j]);
        //             if (zone != nullptr){
        //                 int population = zone->getPopulation();
        //                 // int adjacentPop = zone->CountAdjacent(i, j, region, 1);
        //                 int adjPop1 = zone->CountAdjacent(i, j, region, 1);
        //                 int adjPop2 = zone->CountAdjacent(i, j, region, 2);
        //                 int adjPop3 = zone->CountAdjacent(i, j, region, 3);
        //                 int adjPop4 = zone->CountAdjacent(i, j, region, 4);
        //                 int totalAdjPop = (1 * adjPop1) + (2 * adjPop2) + (3 * adjPop3) + (4 * adjPop4);

        //                 //check if zone is growable
        //                 bool powerlineAdjacent = zone->PowerlineAdjacentCheck(i, j, region);
        //                 bool canGrow = (population == 0 && (powerlineAdjacent || adjPop1 >= 1)) ||
        //                                (population == 1 && adjPop1 >= 2) ||
        //                                (population == 2 && adjPop2 >= 4) ||
        //                                (population == 3 && adjPop3 >= 6) ||
        //                                (population == 4 && adjPop4 >= 8);

        //                 if (!canGrow){
        //                     continue;
        //                 }

        //                 //compare to find best growth candidate
        //                 if (population > bestCandidate.population ||
        //                     (population == bestCandidate.population && totalAdjPop > bestCandidate.adjPop) ||
        //                     (population == bestCandidate.population && totalAdjPop == bestCandidate.adjPop && i < bestCandidate.x) ||
        //                     (population == bestCandidate.population && totalAdjPop == bestCandidate.adjPop && i == bestCandidate.x && j < bestCandidate.y)){

        //                     bestCandidate = {i, j, population, totalAdjPop, zone};
        //                 }
        //             }
        //         }
        //     }

        //     //break loop if no valid candidate is found
        //     if (bestCandidate.zone == nullptr){
        //         break;
        //     }

        //     cout << "Best candidate: (" << bestCandidate.x << ", " << bestCandidate.y 
        //         << ") - Population: " << bestCandidate.population 
        //         << ", adjPop: " << bestCandidate.adjPop << endl;

        //     // if (bestCandidate.zone != nullptr){
        //         int oldPopulation = bestCandidate.zone->getPopulation();
        //         bestCandidate.zone->growFunction(region, bestCandidate.x, bestCandidate.y, *this);
        //         int newPopulation = bestCandidate.zone->getPopulation();

        //         //for debugging
        //         cout << "**** For Debugging ****" << endl;
        //         displayRegionPopulation();

        //         if (newPopulation > oldPopulation){
        //             growthOcurred = true; //growth happened if population increased
        //         } else{
        //             break; //no growth, stop further checks
        //         }
        //     // }
        // }

        displayRegionPopulation();
        
        if (step % refreshRate == 0){
            displayRegion();
        }

        //count availableWorkers after growth
        int newAvailableWorkers = 0;
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                ResidentialZone* residentialZone = dynamic_cast<ResidentialZone*>(region[i][j]);
                if (residentialZone != nullptr){
                    newAvailableWorkers += residentialZone->getPopulation();
                }
            }
        }
        //update availableWorkers if the residential zones' population increased
        if (newAvailableWorkers > oldAvailableWorkers){ //this if statement might be unnecessary
            updateAvailableWorkers(newAvailableWorkers - oldAvailableWorkers);
        }

        //count availableGoods after growth
        int newAvailableGoods = 0;
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(region[i][j]);
                if (industrialZone != nullptr){
                    newAvailableGoods += industrialZone->getPopulation();
                }
            }
        }
        //update availableGoods if the industrial zones' population increased
        updateAvailableGoods(newAvailableGoods - oldAvailableGoods);

        cout << "Avaialble workers after growth: " << availableWorkers << endl;
        cout << "Avaialble goods after growth: " << availableGoods << endl;
        
        // if (!growthOcurred){
        //     cout << "Further growth isn't possible. Ending simulation early at time step " << step + 1 << endl;
        //     break;
        // }
    }
}

void SimCity::displayRegionPopulation(){
    cout << "Region Population Map:" << endl;
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            MapObject* cell = region[i][j];
            Zone* zone = dynamic_cast<Zone*>(cell);
            if (zone != nullptr){
                cout << zone->getType() << "(" << zone->getPopulation() << ")\t";
            } else if (cell != nullptr){
                if (cell->getType() == 'T'){
                    cout << "T\t";
                } else if (cell->getType() == '#'){
                    cout << "#\t";
                } else{
                    cout << "-\t";
                }
            } else{
                cout << " \t";
            }
        }
        cout << endl;
    }
}

void SimCity::displayRegionPollution(){
    cout << "Region Pollution Map:" << endl;
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            MapObject* cell = region[i][j];
            if (cell != nullptr){
                cout << cell->getType() << "(" << cell->getPollution() << ")\t";
            } else{
                cout << " \t";
            }
        }
        cout << endl;
    }
}

int SimCity::getAvailableWorkers() const{
    return availableWorkers;
}

int SimCity::getAvailableGoods() const{
    return availableGoods;
}

void SimCity::updateAvailableWorkers(int amount){
    availableWorkers += amount;
}

void SimCity::updateAvailableGoods(int amount){
    availableGoods += amount;
}