#include <vector>
class Region{
    string regionFile;
    int timeLimit;
    int refreshRate;
    vector<vector<char>> regionLayout;
public:
    bool readConfigFile();
    bool readRegionInitial();

};