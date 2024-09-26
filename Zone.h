#ifndef ZONE_H
#define ZONE_H
#include "MapObject.h"

class Zone : public MapObject{
protected:
    int population;
    int pollution;

public:
    Zone();
    Zone(char t, int pop, int pol);

    virtual char getType() const = 0;
    virtual int getPopulation() const = 0;
    virtual int getPollution() const = 0;
};

#endif