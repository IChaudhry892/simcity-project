#include "PowerPlant.h"
#include <iostream>
using namespace std;

PowerPlant::PowerPlant() : MapObject('P') {}

PowerPlant::PowerPlant(char t) : MapObject(t) {}

char PowerPlant::getType() const{
    return type;
}