#include "Zone.h"

class CommercialZone : public Zone{
public:
    CommercialZone();
    CommercialZone(int pop);

    char getType() const override;
    int getPopulation() const override;
    void setPopulation(int pop) override;

    void growFunction(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city) override;
    int evaluateGrowth(std::vector<std::vector<MapObject*>>& region, int x, int y, SimCity& city) override;
};