#include "CommercialZone.h"

CommercialZone::CommercialZone() : Zone('C', 0) {}

CommercialZone::CommercialZone(int pop) : Zone('C', pop) {}

char CommercialZone::getType() const{
    return type;
}

int CommercialZone::getPopulation() const{
    return population;
}