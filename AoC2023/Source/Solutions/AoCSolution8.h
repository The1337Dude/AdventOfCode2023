
#pragma once

#include "Helpers/AoCHelpers.h"
#include <unordered_map>

struct Node
{
    string Left;
    string Right;
};

class AoCSolution8 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
    
private:
    void ParseInstructions();
    void ParseNodeData();
    vector<string> GetNodeNamesEndingWith(const char& EndingChar);
    long long GetNumberOfSteps(const string Start, const int Part = 1) const;
    
private:
    vector<string> InputData;
    unordered_map<string, Node> Nodes;
    string Instructions;
    unordered_map<int, int> PeriodMap;
};
