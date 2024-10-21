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
    // int adjPop1 = CountAdjacent(x, y, region, 1);

    // int availableWorkers = city.getAvailableWorkers();
    // int availableGoods = city.getAvailableGoods();
    // int oldPopulation = getPopulation();
    // bool PowerlineAdjacent = PowerlineAdjacentCheck(x, y, region);

    // if (population == 0 && (PowerlineAdjacent || adjPop1 >= 1) && availableWorkers >= 1 && availableGoods >= 1){
    //     setPopulation(1);
    // } else if (population == 1 && adjPop1 >= 2 && availableWorkers >= 1 && availableGoods >= 1){
    //     setPopulation(2);
    // }

    // int newPopulation = getPopulation();
    // if (newPopulation > oldPopulation){
    //     city.updateAvailableWorkers(-1);
    //     city.updateAvailableGoods(-1);
    // }
}

int CommercialZone::evaluateGrowth(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city){
    
}