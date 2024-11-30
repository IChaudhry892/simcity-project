#include "ResidentialZone.h"
#include "SimCity.h"
#include <vector>
#include <iostream>
using namespace std;

ResidentialZone::ResidentialZone() : Zone('R', 0) {}

ResidentialZone::ResidentialZone(int pop) : Zone('R', pop) {}

char ResidentialZone::getType() const{
    return type;
}

int ResidentialZone::getPopulation() const{
    return population;
}

void ResidentialZone::setPopulation(int pop){
    population = pop;
}

int ResidentialZone::evaluateGrowth(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city){
    //If zone is non-functional, the population will not grow
    if (isNonFunctional()){
        return population;
    }

    int adjPop1 = CountAdjacent(x, y, region, 1); //Counts how many adjacent cells have a pop >= 1
    int adjPop2 = CountAdjacent(x, y, region, 2);
    int adjPop3 = CountAdjacent(x, y, region, 3);
    int adjPop4 = CountAdjacent(x, y, region, 4);

    bool PowerlineAdjacent = PowerlineAdjacentCheck(x, y, region); //check if adjacent to powerline

    //for debugging
    // cout << "**** FOR DEBUGGING ****" << endl;
    // cout << "Zone at (" << x << ", " << y << ") - Population: " << population
    //      << ", adjPop1: " << adjPop1
    //      << ", PowerlineAdjacent: " << PowerlineAdjacent << endl;
    // cout << "**** FOR DEBUGGING ****" << endl;

    int newPopulation = population;

    if (population == 0 && (PowerlineAdjacent || adjPop1 >= 1)){
        newPopulation = 1;
    } else if (population == 1 && adjPop1 >= 2){
        newPopulation = 2;
    } else if (population == 2 && adjPop2 >= 4){
        newPopulation = 3;
    } else if (population == 3 && adjPop3 >= 6){
        newPopulation = 4;
    } else if (population == 4 && adjPop4 >= 8){
        newPopulation = 5;
    }

    return newPopulation; //this is how much this zone's population should be at the end of the current time step
}