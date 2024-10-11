#include "CommercialZone.h"
#include "SimCity.h"
#include <vector>

CommercialZone::CommercialZone() : Zone('C', 0) {}

CommercialZone::CommercialZone(int pop) : Zone('C', pop) {}

char CommercialZone::getType() const{
    return type;
}

int CommercialZone::getPopulation() const{
    return population;
}

void CommercialZone::setPopulation(int pop){
    population = pop;
}

void CommercialZone::growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city){
    int adjPop1 = CountAdjacent(x, y, region, 1);

    int availableWorkers = city.getAvailableWorkers();
    int availableGoods = city.getAvailableGoods();
}