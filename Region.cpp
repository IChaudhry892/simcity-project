#include "Region.h"
#include <iostream>
#include <fstream>
using namespace std;

bool Region::readConfigFile(){
    string configFileName;
    cout << "Enter config file name: ";
    cin >> configFileName;

    ifstream configFile(configFileName);
    if (!configFile.is_open()){
        cout << "Could not open config file." << endl;
        return false;
    }
    if (configFile.is_open()){
        string line;
        while(getline(configFile, line)){
            if (line.find("Region Layout: ") != string::npos){
                regionFile = line.substr(line.find(": ") + 1);
            }
            if (line.find("Time Limit: ") != string::npos){
                timeLimit = stoi(line.substr(line.find(": ") + 1));
            }
            if (line.find("Refresh Rate: ") != string::npos){
                refreshRate = stoi(line.substr(line.find(": ") + 1));
            }
        }
        configFile.close();
    }
    return true;
}

bool Region::readRegionInitial(){
    ifstream regionFileStream(regionFile);
    if (!regionFileStream.is_open()){
        cout << "Could not open config file." << endl;
        return false;
    }
    if (regionFileStream.is_open()){
        string line;
        while(getline(regionFileStream, line)){
            vector<char> row;
            for(char cell : row){
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