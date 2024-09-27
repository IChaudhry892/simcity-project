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
};

#endif