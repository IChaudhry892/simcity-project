#include "Zone.h"

Zone::Zone() : MapObject('Z'), population(0) {}

Zone::Zone(char t, int pop) : MapObject(t), population(pop) {}