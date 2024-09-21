#include "Road.h"
#include <iostream>
using namespace std;

Road::Road() : MapObject('-') {}

Road::Road(char t) : MapObject(t) {}

char Road::getType() const{
    return type;
}