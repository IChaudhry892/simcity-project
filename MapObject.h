#ifndef MAPOBJECT_H
#define MAPOBJECT_H

class MapObject{
protected:
    char type;
    int pollution;

public:
    MapObject();
    MapObject(char t);
    
    virtual char getType() const = 0;

    int getPollution() const;
    void setPollution(int p);
};

#endif