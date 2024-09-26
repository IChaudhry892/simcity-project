#include "IndustrialZone.h"

IndustrialZone::IndustrialZone() : Zone('I', 0, 0) {}

IndustrialZone::IndustrialZone(int pop, int pol) : Zone('I', pop, pol) {}

char IndustrialZone::getType() const{
    return type;
}

int IndustrialZone::getPopulation() const{
    return population;
}

int IndustrialZone::getPollution() const{
    return pollution;
}