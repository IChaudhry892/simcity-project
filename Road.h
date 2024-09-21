#include "MapObject.h"

class Road : public MapObject{
public:
    Road();
    Road(char t);

    char getType() const override;
};