#include "SimCity.h"
#include <iostream>
using namespace std;

int main(){
    SimCity city;
    
    if (!city.intializeSimulation()){
        cout << "[ERROR] Simulation initialization failed. Exiting program." << endl;
        return -1;
    }

    city.runSimulation();


    return 0;
}