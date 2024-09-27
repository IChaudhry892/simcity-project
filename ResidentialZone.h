#include "Zone.h"

class ResidentialZone : public Zone{
public:
    ResidentialZone();
    ResidentialZone(int pop);

    char getType() const override;
    int getPopulation() const override;
};