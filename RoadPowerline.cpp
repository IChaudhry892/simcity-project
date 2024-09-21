#include "RoadPowerline.h"

RoadPowerline::RoadPowerline() : MapObject('#') {}

RoadPowerline::RoadPowerline(char t) : MapObject(t) {}

char RoadPowerline::getType() const{
    return type;
}