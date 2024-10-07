#include "IndustrialZone.h"
#include <vector>

IndustrialZone::IndustrialZone() : Zone('I', 0) {}

IndustrialZone::IndustrialZone(int pop) : Zone('I', pop) {}

char IndustrialZone::getType() const{
    return type;
}

int IndustrialZone::getPopulation() const{
    return population;
}

void IndustrialZone::setPopulation(int pop){
    population = pop;
}

void IndustrialZone::growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city){
}