#include "Earthquake.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

//hasOccured should be initialized to false
Earthquake::Earthquake() : hasOccurred(false), magnitude(0.0) {
    srand(time(NULL)); //seed the random number generator
}

//Return true if an earthquake occurs, else return false
bool Earthquake::checkForEarthquake(){
    //***COMMENTED OUT FOR DEBUGGING***
    //Return false immediately if hasOccured is true
    if (hasOccurred){
        return false;
    }

    //If hasOccured was false, generate a random number between 1 and 100 to determine the earthquake's magnitude
    double randomNumber = (static_cast<double>(rand()) / RAND_MAX * 100.0); //generates a random number 0-100 (inclusive)

    //***FOR DEBUGGING***
    cout << "Random number generated " << randomNumber << endl;

    if (randomNumber <= MAGNITUDE_95_THRESHOLD){
        magnitude = 9.5;
        hasOccurred = true;
        cout << "A CATASTROPHIC MAGNITUDE 9.5 EARTHQUAKE HAS OCCURRED!\n";
        this_thread::sleep_for(chrono::seconds(3)); //program sleeps for 3 seconds
        return true;
    } else if (randomNumber <= MAGNITUDE_75_THRESHOLD){
        // magnitude = 7.5;
        magnitude = 9.5;
        hasOccurred = true;
        cout << "A CATASTROPHIC MAGNITUDE 9.5 EARTHQUAKE HAS OCCURRED!\n";
        this_thread::sleep_for(chrono::seconds(3)); //program sleeps for 3 seconds
        return true;
    } else if (randomNumber <= MAGNITUDE_70_THRESHOLD){
        // magnitude = 7.0;
        magnitude = 9.5;
        hasOccurred = true;
        cout << "A CATASTROPHIC MAGNITUDE 9.5 EARTHQUAKE HAS OCCURRED!\n";
        this_thread::sleep_for(chrono::seconds(3)); //program sleeps for 3 seconds
        return true;
    } else if (randomNumber <= MAGNITUDE_67_THRESHOLD){
        // magnitude = 6.7;
        magnitude = 9.5;
        hasOccurred = true;
        cout << "A CATASTROPHIC MAGNITUDE 9.5 EARTHQUAKE HAS OCCURRED!\n";
        this_thread::sleep_for(chrono::seconds(3)); //program sleeps for 3 seconds
        return true;
    }

    //If randomNumber is > 63.7, no earthquake will occur
    cout << "NO EARTHQUAKE OCCURRED!\n";
    return false;
}

bool Earthquake::hasEarthquakeOccurred() const{
    return hasOccurred;
}

double Earthquake::getMagnitude() const{
    return magnitude;
}