
#pragma once

#include "Helpers/AoCHelpers.h"

class AoCSolution9 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
    
private:
    void ParseReadings();
    long long GetNextReading(const vector<long long>& Readings);
    
private:
    vector<string> InputData;
    vector<vector<long long>> ReadingData;
};
