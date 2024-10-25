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
#include <iomanip>
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
    cout << "+==========================================+" << endl;
    cout << "|" << setw(42) << left << "           SIMCITY SIMULATION" << "|" << endl;
    cout << "|==========================================|" << endl;
    cout << "|" << setw(42) << left << " Initial State:" << "|" << endl;
    cout << "|" << " Available Workers: " << setw(22) << left << availableWorkers << "|" << endl;
    cout << "|" << " Available Goods: " << setw(24) << left << availableGoods << "|" << endl;
    cout << "+==========================================+" << endl;
    cout << endl;
    displayRegion();

    //for debugging
    displayRegionPopulation();
    displayRegionPollution();
}

void SimCity::runSimulation(){
    for(int step = 0; step < timeLimit; step++){
        cout << "\n+==========================================+" << endl;
        cout << "|" << setw(42) << left << "           SIMCITY SIMULATION" << "|" << endl;
        cout << "|==========================================|" << endl;
        cout << "|" << " Time Step: " << setw(30) << left << step + 1 << "|" << endl;
        cout << "|" << " Available Workers: " << setw(22) << left << availableWorkers << "|" << endl;
        cout << "|" << " Available Goods: " << setw(24) << left << availableGoods << "|" << endl;
        cout << "+==========================================+" << endl;

        //need to stop time steps when citys tops growing
        bool growthOccurred = false; //set true if population of zones changed

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

        //evaluate residential growth and store results in newPopulations
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                ResidentialZone* residentialZone = dynamic_cast<ResidentialZone*>(region[i][j]);
                if (residentialZone != nullptr){
                    int newPopulation = residentialZone->evaluateGrowth(region, i, j, *this);
                    if (newPopulation != residentialZone->getPopulation()){
                        growthOccurred = true;
                    }
                    newPopulations[i][j] = newPopulation;
                }
            }
        }

        //evaluate commercial growth and store results in newPopulations
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                CommercialZone* commercialZone = dynamic_cast<CommercialZone*>(region[i][j]);
                if (commercialZone != nullptr){
                    int newPopulation = commercialZone->evaluateGrowth(region, i, j, *this);
                    if (newPopulation != commercialZone->getPopulation()){
                        growthOccurred = true;
                    }
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
                    if (newPopulation != industrialZone->getPopulation()){
                        growthOccurred = true;
                    }
                    newPopulations[i][j] = newPopulation;
                }
            }
        }

        //apply residential, commercial, & industrial growth from newPopulations to actual region
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[i].size(); j++){
                ResidentialZone* residentialZone = dynamic_cast<ResidentialZone*>(region[i][j]);
                if (residentialZone != nullptr && newPopulations[i][j] != -1){
                    residentialZone->setPopulation(newPopulations[i][j]);
                }

                CommercialZone* commercialZone = dynamic_cast<CommercialZone*>(region[i][j]);
                if (commercialZone != nullptr && newPopulations[i][j] != -1){
                    commercialZone->setPopulation(newPopulations[i][j]);
                }

                IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(region[i][j]);
                if (industrialZone != nullptr && newPopulations[i][j] != -1){
                    industrialZone->setPopulation(newPopulations[i][j]);
                }
            }
        }

        cout << "**** FOR DEBUGGING ****" << endl;
        displayRegionPopulation();
        displayRegionPollution();
        cout << "**** FOR DEBUGGING ****" << endl;

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
        // if (newAvailableWorkers > oldAvailableWorkers){ //this if statement might be unnecessary, workers could decrease as well
            updateAvailableWorkers(newAvailableWorkers - oldAvailableWorkers);
        // }

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

        cout << "+==========================================+" << endl;
        cout << "|" << setw(42) << left << " GROWTH RESULTS" << "|" << endl;
        cout << "|" << " Available workers after growth: " << setw(9) << left << availableWorkers << "|" << endl;
        cout << "|" << " Available goods after growth: " << setw(11) << left << availableGoods << "|" << endl;
        cout << "+==========================================+" << endl;
        
        if (!growthOccurred){
            cout << "\n+==========================================+" << endl;
            cout << "|" << setw(42) << left << " No further growth is possible." << "|" << endl;
            cout << "|" << " Ending simulation at time step " << setw(10) << left << step + 1 << "|" << endl;
            cout << "+==========================================+" << endl;
            break;
        }

        //ask user to continue to next time step or quit program
        while (true){
            cout << "\n+==========================================+" << endl;
            cout << "|" << setw(42) << left << " Enter 'c' to continue to next time step" << "|" << endl;
            cout << "|" << setw(42) << left << " Enter 'q' to quit simulation" << "|" << endl;
            cout << "+==========================================+" << endl;

            char choice;
            cin >> choice;
            cin.ignore();

            if (choice == 'q' || choice == 'Q'){
                cout << "\n+==========================================+" << endl;
                cout << "|" << setw(42) << left << " Simulation terminated by user" << "|" << endl;
                cout << "|" << " At time step: " << setw(27) << left << step + 1 << "|" << endl;
                cout << "+==========================================+" << endl;
                return;
            } else if (choice == 'c' || choice == 'C'){
                break; //should break while loop and continue to next time step
            } else{
                cout << "\n+==========================================+" << endl;
                cout << "|" << setw(42) << left << " Invalid choice, try again." << "|" << endl;
                cout << "+==========================================+" << endl;
            }
        }
    }

    cout << "\n+==========================================+" << endl;
    cout << "|" << setw(42) << left << "            FINAL REGION STATE" << "|" << endl;
    cout << "+==========================================+" << endl;
    displayRegion();
    cout << "+==========================================+" << endl;
    cout << "|" << setw(42) << left << " FINAL POPULATION TOTALS" << "|" << endl;
    cout << "|" << " Residential Population: " << setw(17) << left << getTotalResidentialPopulation() << "|" << endl;
    cout << "|" << " Industrial Population: " << setw(18) << left << getTotalIndustrialPopulation() << "|" << endl;
    cout << "|" << " Commercial Population: " << setw(18) << left << getTotalCommercialPopulation() << "|" << endl;
    cout << "+==========================================+" << endl;

    spreadPollution();
    cout << "\n+==========================================+" << endl;
    cout << "|" << setw(42) << left << "            FINAL POLLUTION STATE" << "|" << endl;
    cout << "+==========================================+" << endl;
    displayRegionPollution();
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

void SimCity::spreadPollution(){
    //create a grid to store industrial zone pollution values
    // vector<vector<int>> pollutionMap(region.size(), vector<int>(region[0].size(), 0));

    // //add industrial zone population to pollutionMap
    // for (int i = 0; i < region.size(); i++){
    //     for (int j = 0; j < region[i].size(); j++){
    //         IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(region[i][j]);
    //         if (industrialZone != nullptr){
    //             pollutionMap[i][j] = industrialZone->getPopulation();
    //         }
    //     }
    // }
    //new approach, modify actual regions pollution values instead of making a separate grid
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            MapObject* cell = region[i][j];
            if (cell != nullptr){
                IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(cell);
                if (industrialZone != nullptr){
                    cell->setPollution(industrialZone->getPopulation());
                }
            }
        }
    }

    //for debugging
    // cout << "**** FOR DEBUGGING ****" << endl;
    // cout << "INITIAL POLLUTION MAP:" << endl;
    // for (int i = 0; i < region.size(); i++){
    //     for (int j = 0; j < region[i].size(); j++){
    //         int cell = pollutionMap[i][j];
    //         cout << cell << "\t";
    //     }
    //     cout << endl;
    // }
    // cout << "**** FOR DEBUGGING ****" << endl;
    cout << "**** FOR DEBUGGING ****" << endl;
    cout << "INITIAL POLLUTION MAP:" << endl;
    displayRegionPollution();
    cout << "**** FOR DEBUGGING ****" << endl;

    //spread pollution
    // for (int i = 0; i < region.size(); i++){
    //     for (int j = 0; j < region[i].size(); j++){
    //         if (pollutionMap[i][j] > 0){ //if this cell is polluted
    //             int pollutionSource = pollutionMap[i][j];

    //             //check all adjacent cells
    //             for (int i2 = -1; i2 <= 1; i2++){
    //                 for (int j2 = -1; j2 <= 1; j2++){
    //                     if (i2 == 0 && j2 == 0) continue;
    //                     int adjX = i + i2;
    //                     int adjY = j + j2;
    //                     //check if adjacent cell is within bounds
    //                     if (adjX >= 0 && adjX < region.size() && adjY >= 0 && adjY < region[0].size()){
    //                         MapObject* adjacentCell = region[adjX][adjY];
    //                         if (adjacentCell != nullptr){
    //                             int spreadPollution = pollutionSource - 1; //pollution around source is 1 less than pollution at source
    //                             if (spreadPollution > adjacentCell->getPollution()){
    //                                 adjacentCell->setPollution(spreadPollution);
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            MapObject* cell = region[i][j];
            if (cell != nullptr){
                IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(cell);
                if (industrialZone != nullptr && industrialZone->getPopulation() > 0){ //if this cell is polluted
                    int sourcePollution = industrialZone->getPopulation();

                    //check all adjacent cells
                    for (int i2 = -1; i2 <= 1; i2++){
                        for (int j2 = -1; j2 <= 1; j2++){
                            if (i2 == 0 && j2 == 0) continue;
                            int adjX = i + i2;
                            int adjY = j + j2;
                            //check if adjacent cell is within bounds
                            if (adjX >= 0 && adjX < region.size() && adjY >= 0 && adjY < region[0].size()){
                                MapObject* adjacentCell = region[adjX][adjY];
                                if (adjacentCell != nullptr){
                                    int spreadPollution = sourcePollution - 1; //pollution around source is 1 less than pollution at source
                                    if (spreadPollution > adjacentCell->getPollution()){
                                        adjacentCell->setPollution(spreadPollution);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int SimCity::getTotalResidentialPopulation() const{
    int totalPop = 0;
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            ResidentialZone* residentialZone = dynamic_cast<ResidentialZone*>(region[i][j]);
            if (residentialZone != nullptr){
                totalPop += residentialZone->getPopulation();
            }
        }
    }
    return totalPop;
}

int SimCity::getTotalIndustrialPopulation() const{
    int totalPop = 0;
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(region[i][j]);
            if (industrialZone != nullptr){
                totalPop += industrialZone->getPopulation();
            }
        }
    }
    return totalPop;
}

int SimCity::getTotalCommercialPopulation() const{
    int totalPop = 0;
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            CommercialZone* commercialZone = dynamic_cast<CommercialZone*>(region[i][j]);
            if (commercialZone != nullptr){
                totalPop += commercialZone->getPopulation();
            }
        }
    }
    return totalPop;
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