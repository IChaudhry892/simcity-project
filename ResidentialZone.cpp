#include "ResidentialZone.h"
#include <vector>

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

void ResidentialZone::growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y){
    int adjPop1 = CountAdjacent(x, y, region, 1); //Counts how many adjacent cells have a pop >= 1
    int adjPop2 = CountAdjacent(x, y, region, 2);
    int adjPop3 = CountAdjacent(x, y, region, 3);
    int adjPop4 = CountAdjacent(x, y, region, 4);
    bool PowerlineAdjacent = false;

    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if (i == 0 && j == 0) continue;
            int adjX = x + i;
            int adjY = y + j;
            if (adjX >= 0 && adjX < region.size() && adjY >= 0 && adjY < region[0].size()){
                MapObject* adjacent = region[adjX][adjY];
                if (adjacent->getType() == 'T' || adjacent->getType() == '#'){
                    PowerlineAdjacent = true;
                }
            }
        }
    }

    if (population == 0 && (PowerlineAdjacent || adjPop1 >= 1)){
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
}