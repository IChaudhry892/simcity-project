#include "ResidentialZone.h"

ResidentialZone::ResidentialZone() : Zone('R', 0, 0) {}

ResidentialZone::ResidentialZone(int pop, int pol) : Zone('R', pop, pol) {}

char ResidentialZone::getType() const{
    return type;
}

int ResidentialZone::getPopulation() const{
    return population;
}

int ResidentialZone::getPollution() const{
    return pollution;
}