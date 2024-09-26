#include "Zone.h"

Zone::Zone() : MapObject('Z'), population(0), pollution(0) {}

Zone::Zone(char t, int pop, int pol) : MapObject(t), population(pop), pollution(pol) {}