#include "MapObject.h"

class RoadPowerline : public MapObject{
public:
    RoadPowerline();
    RoadPowerline(char t);

    char getType() const override;
};