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

int CommercialZone::evaluateGrowth(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city){
    int adjPop1 = CountAdjacent(x, y, region, 1);

    int availableWorkers = city.getAvailableWorkers();
    int availableGoods = city.getAvailableGoods();
    bool PowerlineAdjacent = PowerlineAdjacentCheck(x, y, region);

    int newPopulation = population;

    if (population == 0 && (PowerlineAdjacent || adjPop1 >= 1) && availableWorkers >= 1 && availableGoods >= 1){
        newPopulation = 1;
        city.updateAvailableWorkers(-1);
        city.updateAvailableGoods(-1);
    } else if (population == 1 && adjPop1 >= 2 && availableWorkers >= 1 && availableGoods >= 1){
        newPopulation = 2;
        city.updateAvailableWorkers(-1);
        city.updateAvailableGoods(-1);
    }

    return newPopulation;
}