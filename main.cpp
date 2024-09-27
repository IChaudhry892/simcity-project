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

    // cout << "Region Layout:" << endl;
    // for (int i = 0; i < region.size(); i++){
    //     for (int j = 0; j < region[i].size(); j++){
    //         cout << region[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    vector<vector<MapObject*>> intialRegion = city.initializeRegion();
    city.displayRegion();


    return 0;
}