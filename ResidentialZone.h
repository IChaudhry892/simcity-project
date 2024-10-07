#include "Zone.h"

class ResidentialZone : public Zone{
public:
    ResidentialZone();
    ResidentialZone(int pop);

    char getType() const override;
    int getPopulation() const override;
    void setPopulation(int pop) override;

    void growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city) override;
};