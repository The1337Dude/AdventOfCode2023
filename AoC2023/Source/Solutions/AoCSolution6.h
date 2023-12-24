
#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

struct RaceData
{
    long long Time;
    long long DistanceRecord;
    
    long long GetNumberOfWaysToWin() const;
};

class AoCSolution6 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;

private:
    void ParseRaceData();
    
private:
    vector<string> InputData;
    vector<RaceData> RaceDataEntries;
};
