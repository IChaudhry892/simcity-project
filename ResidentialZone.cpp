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

void ResidentialZone::growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city){
    int adjPop1 = CountAdjacent(x, y, region, 1); //Counts how many adjacent cells have a pop >= 1
    int adjPop2 = CountAdjacent(x, y, region, 2);
    int adjPop3 = CountAdjacent(x, y, region, 3);
    int adjPop4 = CountAdjacent(x, y, region, 4);
    // bool PowerlineAdjacent = false;
    bool PowerlineAdjacent = PowerlineAdjacentCheck(x, y, region);

    cout << "Zone at (" << x << ", " << y << ") - Population: " << population
         << ", adjPop1: " << adjPop1
         << ", PowerlineAdjacent: " << PowerlineAdjacent << endl;

    // int oldPopulation = getPopulation();

    // if (population == 0 && (PowerlineAdjacent || adjPop1 >= 1)){
    //     setPopulation(1);
    if (population == 0 && PowerlineAdjacent){
        setPopulation(1);
    } else if (population == 0 && adjPop1 >= 1){
        setPopulation(1);
    } else if (population == 1 && adjPop1 >= 2){
        setPopulation(2);
    } else if (population == 2 && adjPop2 >= 4){
        setPopulation(3);
    } else if (population == 3 && adjPop3 >= 6){
        setPopulation(4);
    } else if (population == 4 && adjPop4 >= 8){
        setPopulation(5);
    }

    // int newPopulation = getPopulation();
    // if (newPopulation > oldPopulation){
    //     city.updateAvailableWorkers(newPopulation - oldPopulation);
    // }
}

int ResidentialZone::evaluateGrowth(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city){
    int adjPop1 = CountAdjacent(x, y, region, 1); //Counts how many adjacent cells have a pop >= 1
    int adjPop2 = CountAdjacent(x, y, region, 2);
    int adjPop3 = CountAdjacent(x, y, region, 3);
    int adjPop4 = CountAdjacent(x, y, region, 4);

    bool PowerlineAdjacent = PowerlineAdjacentCheck(x, y, region); //check if adjacent to powerline

    //for debugging
    cout << "Zone at (" << x << ", " << y << ") - Population: " << population
         << ", adjPop1: " << adjPop1
         << ", PowerlineAdjacent: " << PowerlineAdjacent << endl;

    int newPopulation = population;

    // if (population == 0 && (PowerlineAdjacent || adjPop1 >= 1)){
    //     setPopulation(1);
    if (population == 0 && PowerlineAdjacent){
        newPopulation = 1;
    } else if (population == 0 && adjPop1 >= 1){
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

    return newPopulation;
}