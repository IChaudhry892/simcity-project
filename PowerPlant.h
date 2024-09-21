#include "MapObject.h"

class PowerPlant : public MapObject{
public:
    PowerPlant();
    PowerPlant(char t);

    char getType() const override;
};