
#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

typedef pair<int, int> PositionType;

struct CompareByPositionType {
    bool operator()(const PositionType& a, const PositionType& b) const {
        return a.first == b.first && a.second == b.second;
    }
};

struct Number
{
    int Value;
    
    vector<PositionType> Positions;
};

struct Symbol
{
    char Value;
    PositionType Position;
    
    vector<PositionType> GetRelativePositions(const int MaxColumn, const int MaxRow, const vector<PositionType>& PositionModifiers) const;
};

class AoCSolution3 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
    
private:
    vector<string> InputData;
};
