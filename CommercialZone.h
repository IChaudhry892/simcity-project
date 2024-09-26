#include "Zone.h"

class CommercialZone : public Zone{
public:
    CommercialZone();
    CommercialZone(int pop, int pol);

    char getType() const override;
    int getPopulation() const override;
    int getPollution() const override;
};