#include "Zone.h"
#include <vector>

Zone::Zone() : MapObject('Z'), population(0) {}

Zone::Zone(char t, int pop) : MapObject(t), population(pop) {}

int Zone::CountAdjacent(int x, int y, std::vector<std::vector<MapObject*>>& region, int minPopulation){
    int adjPopulationCount = 0;
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if (i == 0 && j == 0) continue;
            int adjX = x + i;
            int adjY = y + j;
            if (adjX >= 0 && adjX < region.size() && adjY >= 0 && adjY < region[0].size()){
                Zone* adjacentZone = dynamic_cast<Zone*>(region[adjX][adjY]);
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
            int adjX = x + i;
            int adjY = y + j;
            if (adjX >= 0 && adjX < region.size() && adjY >= 0 && adjY < region[0].size()){
                MapObject* adjacent = region[adjX][adjY];
                if (adjacent != nullptr && (adjacent->getType() == 'T' || adjacent->getType() == '#')){
                    return true;
                }
            }
        }
    }
    return false;
}