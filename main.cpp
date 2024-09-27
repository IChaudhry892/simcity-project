#include "SimCity.h"
#include <iostream>
using namespace std;

int main(){
    SimCity city;
    city.readConfigFile();
    city.readRegionInitial();

    int timeLimit = city.getTimeLimit();
    int refreshRate = city.getRefreshRate();
    vector<vector<char>> region = city.getRegionLayout();
    cout << "Time limit: " << timeLimit << endl;
    cout << "Refresh rate: " << refreshRate << endl;

    vector<vector<MapObject*>> intialRegion = city.initializeRegion();
    cout << "Region Map:" << endl;
    city.displayRegion();

    cout << "Region Population Map:" << endl;
    city.displayRegionPopulation();

    cout << "Region Pollution Map:" << endl;
    city.displayRegionPollution();


    return 0;
}