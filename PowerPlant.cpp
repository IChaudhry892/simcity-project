#include "PowerPlant.h"
#include <iostream>
using namespace std;

// PowerPlant::PowerPlant(){
//     type = 'P';
// }

PowerPlant::PowerPlant() : MapObject('P') {}

// PowerPlant::PowerPlant(char t){
//     type = t;
// }

PowerPlant::PowerPlant(char t) : MapObject(t) {}

char PowerPlant::getType() const{
    return type;
}