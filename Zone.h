#ifndef ZONE_H
#define ZONE_H
#include "MapObject.h"

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
    virtual void growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y) = 0;
};

#endif