#ifndef EARTHQUAKE_H
#define EARTHQUAKE_H

class Earthquake{
private:
    bool hasOccurred; //flag that indicates if an earthquake has already occurred in the simulation
    double magnitude; //the magnitude of the earthquake (6.7, 7.0, 7.5, 9.5)
    int centerX; //the earthquake center's X coordinate (col)
    int centerY; //the earthquake center's Y coordinate (row)

    /*Probabilities for each magnitude (percentages)
    Magnitude9.5 = 3.0
    Magnitude7.5 = 6.1
    Magnitude7.0 = 10.2
    Magnitude6.7 = 15.0
    */
    
    //Cumulative probabilities
    //If the random number is <= a magnitude's threshold, the earthquake will be of that magnitude
    //static const b/c the threshold values should stay constant
    static constexpr double MAGNITUDE_95_THRESHOLD = 3.0;
    static constexpr double MAGNITUDE_75_THRESHOLD = 9.1;
    static constexpr double MAGNITUDE_70_THRESHOLD = 19.3;
    static constexpr double MAGNITUDE_67_THRESHOLD = 34.3;

public:
    Earthquake(); //default constructor
    bool checkForEarthquake(int maxY, int maxX); //returns true if earthquake occurs
    bool hasEarthquakeOccurred() const; //returns true if earthquake has occurred in simulation, flase if earthquake has not occured yet

    //Getters
    double getMagnitude() const; //returns the magnitude of the earthquake
    int getCenterX() const;
    int getCenterY() const;
};

#endif