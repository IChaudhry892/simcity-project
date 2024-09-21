#ifndef MAPOBJECT_H
#define MAPOBJECT_H

class MapObject{
protected:
    char type;
public:
    MapObject();
    MapObject(char t);
    virtual char getType() const = 0;
};

#endif