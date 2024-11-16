#include "Earthquake.h"
#include <cstdlib>
#include <ctime>
using namespace std;

//hasOccured should be initialized to false
Earthquake::Earthquake() : hasOccurred(false), magnitude(0.0) {}

//Return false if hasOccured is true
bool Earthquake::checkForEarthquake(){
    if (hasOccurred){
        return false;
    }

    //If hasOccured was false, generate a random number between 1 and 100 to determine the earthquake's magnitude
    srand(time(NULL)); //seed the random number generator
    double randomNumber = (static_cast<double>(rand()) / RAND_MAX * 100.0); //generates a random number 0-100 (inclusive)

    if (randomNumber <= MAGNITUDE_95_THRESHOLD){
        magnitude = 9.5;
        hasOccurred = true;
        return true;
    } else if (randomNumber <= MAGNITUDE_75_THRESHOLD){
        magnitude = 7.5;
        hasOccurred = true;
        return true;
    } else if (randomNumber <= MAGNITUDE_70_THRESHOLD){
        magnitude = 7.0;
        hasOccurred = true;
        return true;
    } else if (randomNumber <= MAGNITUDE_67_THRESHOLD){
        magnitude = 6.7;
        hasOccurred = true;
        return true;
    }

    //If randomNumber is > 63.7, no earthquake will occur
    return false;
}

bool Earthquake::hasEarthquakeOccurred() const{
    return hasOccurred;
}

double Earthquake::getMagnitude() const{
    return magnitude;
}