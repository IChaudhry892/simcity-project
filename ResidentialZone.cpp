#include "ResidentialZone.h"

ResidentialZone::ResidentialZone() : Zone('R', 0) {}

ResidentialZone::ResidentialZone(int pop) : Zone('R', pop) {}

char ResidentialZone::getType() const{
    return type;
}

int ResidentialZone::getPopulation() const{
    return population;
}