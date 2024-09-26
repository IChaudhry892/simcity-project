#include "CommercialZone.h"

CommercialZone::CommercialZone() : Zone('C', 0, 0) {}

CommercialZone::CommercialZone(int pop, int pol) : Zone('C', pop, pol) {}

char CommercialZone::getType() const{
    return type;
}

int CommercialZone::getPopulation() const{
    return population;
}

int CommercialZone::getPollution() const{
    return pollution;
}