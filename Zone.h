#ifndef ZONE_H
#define ZONE_H
#include "MapObject.h"
// #include "SimCity.h"
#include <vector>

class SimCity; //forward declare SimCity

class Zone : public MapObject{
protected:
    int population;

public:
    Zone();
    Zone(char t, int pop);

    virtual char getType() const = 0;
    virtual int getPopulation() const = 0;
    virtual void setPopulation(int pop) = 0;

    int CountAdjacent(int x, int y, std::vector<std::vector<MapObject*>>& region, int minPopulation);
    bool PowerlineAdjacentCheck(int x, int y, std::vector<std::vector<MapObject*>>& region);
    virtual void growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city) = 0; //reference to region b/c the region itself is being modified
    virtual int evaluateGrowth(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city) = 0;
};

#endif