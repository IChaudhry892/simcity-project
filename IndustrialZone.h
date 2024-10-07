#include "Zone.h"

class IndustrialZone : public Zone{
public:
    IndustrialZone();
    IndustrialZone(int pop);

    char getType() const override;
    int getPopulation() const override;
    void setPopulation(int pop) override;

    void growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city) override;
};