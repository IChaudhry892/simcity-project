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

        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                Zone* zone = dynamic_cast<Zone*>(region[i][j]);
                if (zone != nullptr){
                    zone->growFunction(region, i, j, *this);
                }
            }
        }

        displayRegionPopulation();
        
        if (step % refreshRate == 0){
            displayRegion();
        }
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