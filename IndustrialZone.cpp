#include "IndustrialZone.h"
#include "SimCity.h"
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
    int adjPop1 = CountAdjacent(x, y, region, 1);
    int adjPop2 = CountAdjacent(x, y, region, 2);

    int availableWorkers = city.getAvailableWorkers();
    int oldPopulation = getPopulation();
    bool PowerlineAdjacent = PowerlineAdjacentCheck(x, y, region);

    if (population == 0 && (PowerlineAdjacent || adjPop1 >= 1) && availableWorkers >= 2){
        setPopulation(1);
        // city.updateAvailableWorkers(-2);
    } else if (population == 1 && adjPop1 >= 2 && availableWorkers >= 2){
        setPopulation(2);
        // city.updateAvailableWorkers(-2);
    } else if (population == 2 && adjPop2 >= 4 && availableWorkers >= 2){
        setPopulation(3);
        // city.updateAvailableWorkers(-2);
    }

    int newPopulation = getPopulation();
    if (newPopulation > oldPopulation){
        city.updateAvailableWorkers(-2);
        city.updateAvailableGoods(1);
    }
}