#ifndef ZONE_H
#define ZONE_H
#include "MapObject.h"
#include <vector>

class SimCity; //forward declare SimCity

class Zone : public MapObject{
protected:
    int population;
    int nonFunctionalTimeSteps; //the number of time steps zones remain non-functional

public:
    Zone();
    Zone(char t, int pop);

    virtual char getType() const = 0;
    virtual int getPopulation() const = 0;
    virtual void setPopulation(int pop) = 0;

    int CountAdjacent(int x, int y, std::vector<std::vector<MapObject*>>& region, int minPopulation);
    bool PowerlineAdjacentCheck(int x, int y, std::vector<std::vector<MapObject*>>& region);
    virtual int evaluateGrowth(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city) = 0; //evaluates zone growth at the start of each time step, but does not execute growth

    //Functions for handling non-functional state
    int getNonFunctionalTimeSteps() const;
    void setNonFunctionalTimeSteps(int timeSteps);
    bool isNonFunctional() const; //bool flag to indicate if a zone is non-functional
    void decrementNonFunctionalTime(); //called at the end of every time step
};

#endif