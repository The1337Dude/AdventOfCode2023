
#pragma once

#include "Helpers/AoCHelpers.h"
#include <set>
#include <vector>

struct ScratchCard
{
    int Id = 0;
    set<int> WinningNumbers;
    set<int> PlayerNumbers;
    int GetMatches() const;
};

class AoCSolution4 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
    
private:
    ScratchCard ParseScratchCardData(const string& Input);
    int GetWorth(const int NumberOfMatches) const;
    
private:
    vector<string> InputData;
};
