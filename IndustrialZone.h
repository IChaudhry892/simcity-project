#include "Zone.h"

class IndustrialZone : public Zone{
public:
    IndustrialZone();
    IndustrialZone(int pop);

    char getType() const override;
    int getPopulation() const override;
};