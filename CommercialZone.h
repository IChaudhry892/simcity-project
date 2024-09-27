#include "Zone.h"

class CommercialZone : public Zone{
public:
    CommercialZone();
    CommercialZone(int pop);

    char getType() const override;
    int getPopulation() const override;
};