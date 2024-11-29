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
#include <limits>
#include <chrono>
#include <thread>
using namespace std;

SimCity::SimCity() : availableWorkers(0), availableGoods(0) {}

bool SimCity::readConfigFile(){
    string configFileName;
    cout << "Enter config file name: ";
    cin >> configFileName;

    ifstream configFile(configFileName);
    if (!configFile.is_open()){
        cout << "[ERROR] Could not open config file: " << configFileName << "." << endl;
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
        cout << "[ERROR] Could not open region file: " << regionFile << endl;
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

std::vector<std::vector<MapObject*>> SimCity::initializeRegion(){ //uses characters from regionLayout to make the city and store it in region
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

void SimCity::displayFinalRegion(){ //displays region with x and y axes
    cout << "Region Map:" << endl;
    //print x-axis numbers
    cout << "    ";
    for (int j = 0; j < region[0].size(); j++){
        cout << j << "       ";
    }
    cout << endl;
    
    cout << "   ";
    for (int j = 0; j < region[0].size(); j++){
        cout << "--------";
    }
    cout << endl;

    //print region and y-axis numbers
    for (int i = 0; i < region.size(); i++){
        cout << i << " | ";
        for (int j = 0; j < region[i].size(); j++){
            MapObject* cell = region[i][j];
            Zone* zone = dynamic_cast<Zone*>(cell);
            if (zone != nullptr){
                if (zone->getPopulation() > 0){
                    cout << zone->getPopulation() << "       ";
                } else{
                    cout << zone->getType() << "       ";
                }
            } else if (cell != nullptr){
                cout << cell->getType() << "       ";
            } else{
                cout << "        ";
            }
        }
        cout << endl;
    }
}

void SimCity::displaySpecifiedRegion(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX){
    cout << "Specified Region Map:" << endl;

    //print x-axis numbers
    cout << "    ";
    for (int j = topLeftX; j <= bottomRightX; j++){
        cout << j << "       ";
    }
    cout << endl;
    
    cout << "   ";
    for (int j = topLeftX; j <= bottomRightX; j++){
        cout << "--------";
    }
    cout << endl;

    //print region and y-axis numbers
    for (int i = topLeftY; i <= bottomRightY; i++){
        cout << i << " | ";
        for (int j = topLeftX; j <= bottomRightX; j++){
            MapObject* cell = region[i][j];
            Zone* zone = dynamic_cast<Zone*>(cell);
            if (zone != nullptr){
                if (zone->getPopulation() > 0){
                    cout << zone->getPopulation() << "       ";
                } else{
                    cout << zone->getType() << "       ";
                }
            } else if (cell != nullptr){
                cout << cell->getType() << "       ";
            } else{
                cout << "        ";
            }
        }
        cout << endl;
    }
}

void SimCity::displaySpecifiedPollution(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX){
    cout << "Specified Region Pollution Map:" << endl;

    //print x-axis numbers
    cout << "    ";
    for (int j = topLeftX; j <= bottomRightX; j++){
        cout << j << "       ";
    }
    cout << endl;
    
    cout << "   ";
    for (int j = topLeftX; j <= bottomRightX; j++){
        cout << "--------";
    }
    cout << endl;

    //print region and y-axis numbers
    for (int i = topLeftY; i <= bottomRightY; i++){
        cout << i << " | ";
        for (int j = topLeftX; j <= bottomRightX; j++){
            MapObject* cell = region[i][j];
            if (cell != nullptr){
                cout << cell->getType() << "(" << cell ->getPollution() << ")    ";
            } else{
                cout << "        ";
            }
        }
        cout << endl;
    }
}

void SimCity::displayCityDestruction(){
    //Create a bunch of newlines to clear screen
    for (int i = 0; i < 50; i++){
        cout << endl;
    }

    //Show the city right before the earthquake
    displayRegion();
    cout << "\nCITY DESTRUCTION IMMINENT...\n" << endl;
    // this_thread::sleep_for(chrono::seconds(2));
    //Countdown starting at 3
    int countdown = 3;

    while (countdown >= 1){
        cout << countdown << "...\n";
        this_thread::sleep_for(chrono::seconds(1));
        countdown--;
    }

    //Display city destruction
    for (int i = 0; i <= region.size(); i++){
        //Clear the screen before display each level of destruction
        for (int i = 0; i < 50; i++){
            cout << endl;
        }

        //Display the current level of destruction
        for (int m = 0; m < i; m++){
            for (int n = 0; n < region[0].size(); n++){
                cout << "X\t";
            }
            cout << endl;
        }

        //Display the remaning city below the X's
        for (int j = i; j < region.size(); j++){
            for (int k = 0; k < region[j].size(); k++){
                MapObject* cell = region[j][k];
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

        //Add a delay before outputting each destruction level
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    cout << "\nCITY COMPLETELY DESTROYED BY MAGNITUDE 9.5 EARTHQUAKE\n" << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

bool SimCity::intializeSimulation(){
    if (!readConfigFile()){
        cout << "[ERROR] Failed to read the config file. Exiting simulation." << endl;
        return false;
    }

    if (!readRegionInitial()){
        cout << "[ERROR] Failed to read the region layout. Exiting simulation." << endl;
        return false;
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
    // displayRegionPopulation();
    // displayRegionPollution();
    return true; //returns true on successful initialization
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

        //check if earthquake has occurred
        if (earthquake.checkForEarthquake(region.size(), region[0].size())){
            //end simulation if the earthquake's magnitude is 9.5
            if (earthquake.getMagnitude() == 9.5){
                displayCityDestruction();
                return;
            } else{
                cout << "An earthquake of magnitude " << earthquake.getMagnitude() << " has occurred!" << endl;
                //set earthquake center coordinates
                earthquakeCenterY = earthquake.getCenterY();
                earthquakeCenterX = earthquake.getCenterX();
                cout << "Earthquake's center is at coordinates (" << earthquakeCenterY << ", " << earthquakeCenterX << ")" << endl;
            }
        }

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

        // cout << "**** FOR DEBUGGING ****" << endl;
        // displayRegionPopulation();
        // displayRegionPollution();
        // cout << "**** FOR DEBUGGING ****" << endl;

        if (step % refreshRate == 0){ //only displays region every refresh rate
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
        //update availableWorkers
        updateAvailableWorkers(newAvailableWorkers - oldAvailableWorkers);

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
        //update availableGoods
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

    //display final region state and final population totals
    int totalRegionPopulation = getTotalResidentialPopulation() + getTotalIndustrialPopulation() + getTotalCommercialPopulation();
    cout << "\n+==========================================+" << endl;
    cout << "|" << setw(42) << left << "            FINAL REGION STATE" << "|" << endl;
    cout << "+==========================================+" << endl;
    displayFinalRegion();
    cout << "+==========================================+" << endl;
    cout << "|" << setw(42) << left << " FINAL POPULATION TOTALS" << "|" << endl;
    cout << "|" << " Residential Population: " << setw(17) << left << getTotalResidentialPopulation() << "|" << endl;
    cout << "|" << " Industrial Population: " << setw(18) << left << getTotalIndustrialPopulation() << "|" << endl;
    cout << "|" << " Commercial Population: " << setw(18) << left << getTotalCommercialPopulation() << "|" << endl;
    cout << "|" << " Total Region Population: " << setw(16) << left << totalRegionPopulation << "|" << endl;
    cout << "+==========================================+" << endl;

    //start spreading pollution and display final pollution state w/total pollution value
    spreadPollution();
    cout << "\n+==========================================+" << endl;
    cout << "|" << setw(42) << left << "          FINAL POLLUTION STATE" << "|" << endl;
    cout << "+==========================================+" << endl;
    displayRegionPollution();
    cout << "+==========================================+" << endl;
    cout << "|" << " Total Pollution: " << setw(24) << left << getTotalPollution() << "|" << endl;
    cout << "+==========================================+" << endl;

    //prompt user for coordinates of a rectangular region in the city until they enter a valid region
    while (true){
        cout << "\n+==========================================+" << endl;
        cout << "|" << setw(42) << left << " ANALYSIS OF DESIRED AREA" << "|" << endl;
        cout << "+==========================================+" << endl;
        cout << "|" << setw(42) << left << " Enter coordinates of a rectangular area" << "|" << endl;
        cout << "|" << setw(42) << left << " in the region to analyze (y,x)" << "|" << endl;
        cout << "+------------------------------------------+" << endl;
        cout << "|" << setw(42) << left << " Top-Left cell = (0,0)" << "|" << endl;
        cout << "| Bottom-Left cell = (" << region.size() - 1 << setw(20) << left << ",0)" << "|" << endl;
        cout << "| Top-Right cell = (0," << region[0].size() - 1 << setw(20) << ")" << "|" << endl;
        cout << "| Bottom-right cell = (" << region.size() -1 << "," << region[0].size() - 1 << setw(17) << ")" << "|" << endl;
        cout << "+==========================================+" << endl;

        cout << endl;
        int topLeftY = getValidCoordinate("Enter y-coordinate of top-left corner of desired area (y,x): ");
        int topLeftX = getValidCoordinate("Enter x-coordinate of top-left corner of desired area (y,x): ");
        int bottomRightY = getValidCoordinate("Enter y-coordinate of bottom-right corner of desired area (y,x): ");
        int bottomRightX = getValidCoordinate("Enter x-coordinate of bottom-right corner of desired area (y,x): ");

        //check if the coordinates are in the bounds of the region
        if (topLeftY >= 0 && topLeftY < region.size() &&
            topLeftX >= 0 && topLeftX < region[0].size() &&
            bottomRightY >= 0 && bottomRightY < region.size() &&
            bottomRightX >= 0 && bottomRightX < region[0].size() &&
            bottomRightY >= topLeftY && bottomRightX >= topLeftX){
            cout << "\nValid rectanlge. Coordinates are inside bounds of region." << endl;
            //output the map of the specified area
            cout << "+==========================================+" << endl;
            cout << "|" << setw(42) << left << "          SPECIFIED REGION STATE" << "|" << endl;
            cout << "+==========================================+" << endl;
            displaySpecifiedRegion(topLeftY, topLeftX, bottomRightY, bottomRightX);

            int specifiedResidential = getSpecifiedResidentialPopulation(topLeftY, topLeftX, bottomRightY, bottomRightX);
            int specifiedIndustrial = getSpecifiedIndustrialPopulation(topLeftY, topLeftX, bottomRightY, bottomRightX);
            int specifiedCommercial = getSpecifiedCommercialPopulation(topLeftY, topLeftX, bottomRightY, bottomRightX);
            int totalSpecifiedPopulation = specifiedResidential + specifiedIndustrial + specifiedCommercial;

            cout << "+==========================================+" << endl;
            cout << "|" << setw(42) << left << " SPECIFIED REGION POPULATION TOTALS" << "|" << endl;
            cout << "|" << " Residential Population: " << setw(17) << left << specifiedResidential << "|" << endl;
            cout << "|" << " Industrial Population: " << setw(18) << left << specifiedIndustrial << "|" << endl;
            cout << "|" << " Commercial Population: " << setw(18) << left << specifiedCommercial << "|" << endl;
            cout << "|" << " Total Region Population: " << setw(16) << left << totalSpecifiedPopulation << "|" << endl;
            cout << "+==========================================+" << endl;

            cout << "\n+==========================================+" << endl;
            cout << "|" << setw(42) << left << "     SPECIFIED REGION POLLUTION STATE" << "|" << endl;
            cout << "+==========================================+" << endl;
            //display specified region pollution
            displaySpecifiedPollution(topLeftY, topLeftX, bottomRightY, bottomRightX);
            //output specified region's total pollution
            cout << "+==========================================+" << endl;
            cout << "|" << " Total Pollution: " << setw(24) << left << getSpecifiedPollution(topLeftY, topLeftX, bottomRightY, bottomRightX) << "|" << endl;
            cout << "+==========================================+" << endl;
            break;
        } else{
            cout << "\n[ERROR] Invalid rectangle. Coordinates are outside bounds of region or form an invalid rectangle. Please try again." << endl;
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

void SimCity::spreadPollution(){
    //modify actual region's pollution values to create an initial pollution state
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            MapObject* cell = region[i][j];
            if (cell != nullptr){
                IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(cell);
                if (industrialZone != nullptr){
                    cell->setPollution(industrialZone->getPopulation());
                } else{
                    cell->setPollution(0); //non-industrial cells should start with 0 pollution
                }
            }
        }
    }

    // for debugging
    // cout << "**** FOR DEBUGGING ****" << endl;
    // cout << "INITIAL POLLUTION MAP:" << endl;
    // displayRegionPollution();
    // cout << "**** FOR DEBUGGING ****" << endl;

    //create a temporary grid to store new pollution values
    vector<vector<int>> newPollution(region.size(), vector<int>(region[0].size(), 0));

    //pollution needs to spread more than once,
    //a maximum of 3 times b/c an industrial zone's max population is 3
    const int SPREAD_ITERATIONS = 3;

    for (int iteration = 0; iteration < SPREAD_ITERATIONS; iteration++){
        //copy initial pollution state to temporary grid
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[0].size(); j++){
                if (region[i][j] != nullptr){
                    newPollution[i][j] = region[i][j]->getPollution();
                }
            }
        }

        //get new pollution values
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[0].size(); j++){
                MapObject* cell = region[i][j];
                if (cell != nullptr && cell->getPollution() > 0){
                    int sourcePollution = cell->getPollution();

                    //check all adjacent cells
                    for (int i2 = -1; i2 <= 1; i2++){
                        for (int j2 = -1; j2 <= 1; j2++){
                            if (i2 == 0 && j2 == 0) continue;
                            int adjY = i + i2; //checks cells above and below i, i is y-coordinate
                            int adjX = j + j2; //checks cells to the left and right of j, j is x-coordinate
                            //check if adjacent cell is within bounds
                            if (adjY >= 0 && adjY < region.size() && adjX >= 0 && adjX < region[0].size()){
                                MapObject* adjacentCell = region[adjY][adjX];
                                if (adjacentCell != nullptr){
                                    int spreadPollution = sourcePollution - 1; //pollution around source is set to 1 less than pollution at source
                                    if (spreadPollution > newPollution[adjY][adjX]){
                                        newPollution[adjY][adjX] = spreadPollution;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //update actual region with new pollution values
        for (int i = 0; i < region.size(); i++){
            for (int j = 0; j < region[0].size(); j++){
                if (region[i][j] != nullptr){
                    region[i][j]->setPollution(newPollution[i][j]);
                }
            }
        }
    }
}

int SimCity::getTotalPollution() const{
    int totalPollution = 0;
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            MapObject* cell = dynamic_cast<MapObject*>(region[i][j]);
            if (cell != nullptr){
                totalPollution += cell->getPollution();
            }
        }
    }
    return totalPollution;
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

int SimCity::getSpecifiedPollution(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const{
    int totalPollution = 0;
    for (int i = topLeftY; i <= bottomRightY; i++){
        for (int j = topLeftX; j <= bottomRightX; j++){
            MapObject* cell = dynamic_cast<MapObject*>(region[i][j]);
            if (cell != nullptr){
                totalPollution += cell->getPollution();
            }
        }
    }
    return totalPollution;
}

int SimCity::getSpecifiedResidentialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const{
    int totalPop = 0;
    for (int i = topLeftY; i <= bottomRightY; i++){
        for (int j = topLeftX; j <= bottomRightX; j++){
            ResidentialZone* residentialZone = dynamic_cast<ResidentialZone*>(region[i][j]);
            if (residentialZone != nullptr){
                totalPop += residentialZone->getPopulation();
            }
        }
    }
    return totalPop;
}

int SimCity::getSpecifiedIndustrialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const{
    int totalPop = 0;
    for (int i = topLeftY; i <= bottomRightY; i++){
        for (int j = topLeftX; j <= bottomRightX; j++){
            IndustrialZone* industrialZone = dynamic_cast<IndustrialZone*>(region[i][j]);
            if (industrialZone != nullptr){
                totalPop += industrialZone->getPopulation();
            }
        }
    }
    return totalPop;
}

int SimCity::getSpecifiedCommercialPopulation(int topLeftY, int topLeftX, int bottomRightY, int bottomRightX) const{
    int totalPop = 0;
    for (int i = topLeftY; i <= bottomRightY; i++){
        for (int j = topLeftX; j <= bottomRightX; j++){
            CommercialZone* commercialZone = dynamic_cast<CommercialZone*>(region[i][j]);
            if (commercialZone != nullptr){
                totalPop += commercialZone->getPopulation();
            }
        }
    }
    return totalPop;
}

int SimCity::getValidCoordinate(const string& prompt){
    int coordinate;
    while (true){
        cout << prompt;
        if (cin >> coordinate){ //input was an integer
            return coordinate;
        }
        //if input was a non-integer
        cout << "[ERROR] Invalid input. Please enter a number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

SimCity::~SimCity(){
    for (int i = 0; i < region.size(); i++){
        for (int j = 0; j < region[i].size(); j++){
            if(region[i][j] != nullptr){
                delete region[i][j];
                region[i][j] = nullptr;
            }
        }
    }
    region.clear();
}