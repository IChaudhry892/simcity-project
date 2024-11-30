#include "Zone.h"
#include <vector>

Zone::Zone() : MapObject('Z'), population(0) {}

Zone::Zone(char t, int pop) : MapObject(t), population(pop) {}

int Zone::CountAdjacent(int x, int y, std::vector<std::vector<MapObject*>>& region, int minPopulation){
    int adjPopulationCount = 0;
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if (i == 0 && j == 0) continue;
            int adjY = x + i; //checks cells above and below i, i is y-coordinate
            int adjX = y + j; //checks cells to the left and right of j, j is x-coordinate
            if (adjY >= 0 && adjY < region.size() && adjX >= 0 && adjX < region[0].size()){
                Zone* adjacentZone = dynamic_cast<Zone*>(region[adjY][adjX]);
                if (adjacentZone && adjacentZone->getPopulation() >= minPopulation){
                    adjPopulationCount++;
                }
            }
        }
    }
    return adjPopulationCount;
}

bool Zone::PowerlineAdjacentCheck(int x, int y, std::vector<std::vector<MapObject*>>& region){
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if (i == 0 && j == 0) continue;
            int adjY = x + i; //checks cells above and below i, i is y-coordinate
            int adjX = y + j; //checks cells to the left and right of j, j is x-coordinate
            if (adjY >= 0 && adjY < region.size() && adjX >= 0 && adjX < region[0].size()){
                MapObject* adjacent = region[adjY][adjX];
                if (adjacent != nullptr && (adjacent->getType() == 'T' || adjacent->getType() == '#')){
                    return true;
                }
            }
        }
    }
    return false;
}

int Zone::getNonFunctionalTimeSteps() const{
    return nonFunctionalTimeSteps;
}

void Zone::setNonFunctionalTimeSteps(int timeSteps){
    nonFunctionalTimeSteps = timeSteps;
}

//return true if nonFunctinonalTimeSteps > 0
bool Zone::isNonFunctional() const{
    return nonFunctionalTimeSteps > 0;
}

void Zone::decrementNonFunctionalTime(){
    if (nonFunctionalTimeSteps > 0){
        nonFunctionalTimeSteps--;
    }
}