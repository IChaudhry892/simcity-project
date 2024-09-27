#include "IndustrialZone.h"

IndustrialZone::IndustrialZone() : Zone('I', 0) {}

IndustrialZone::IndustrialZone(int pop) : Zone('I', pop) {}

char IndustrialZone::getType() const{
    return type;
}

int IndustrialZone::getPopulation() const{
    return population;
}