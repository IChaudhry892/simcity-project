#include "Zone.h"

class ResidentialZone : public Zone{
public:
    ResidentialZone();
    ResidentialZone(int pop, int pol);

    char getType() const override;
    int getPopulation() const override;
    int getPollution() const override;
};