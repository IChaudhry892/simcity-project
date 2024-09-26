#include "Zone.h"

class IndustrialZone : public Zone{
public:
    IndustrialZone();
    IndustrialZone(int pop, int pol);

    char getType() const override;
    int getPopulation() const override;
    int getPollution() const override;
};