#include "SimCity.h"
#include <iostream>
using namespace std;

int main(){
    SimCity city;
    city.readConfigFile();
    city.readRegionInitial();


    return 0;
}