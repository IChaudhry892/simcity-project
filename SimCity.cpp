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
        for (int j = 0; j < regionLayout.size(); j++){
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
            }
        }
        region.push_back(regionRow);
    }
    return region;
}

void SimCity::displayRegion(){
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region.size(); j++){
            MapObject* cell = region[i][j];
            cout << cell->getType() << "\t";
        }
        cout << endl;
    }
}