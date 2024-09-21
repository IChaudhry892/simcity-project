#include "Powerline.h"
#include <iostream>
using namespace std;

Powerline::Powerline() : MapObject('T') {}

Powerline::Powerline(char t) : MapObject(t) {}

char Powerline::getType() const{
    return type;
}