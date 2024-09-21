#include "MapObject.h"

class Powerline : public MapObject{
public:
    Powerline();
    Powerline(char t);

    char getType() const override;
};