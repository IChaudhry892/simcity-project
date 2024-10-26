#include "MapObject.h"
#include <iostream>
using namespace std;

MapObject::MapObject() : type('n'), pollution(0) {}

MapObject::MapObject(char t) : type(t), pollution(0) {}

int MapObject::getPollution() const{
    return pollution;
}

void MapObject::setPollution(int p){
    pollution = p;
}