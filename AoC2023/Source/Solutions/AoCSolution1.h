
#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

class AoCSolution1 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
    
private:
    vector<string> InputData;
    bool bTranslateAndCheck = false;
    
private:
    int GetLastDigit(const string& Input) const;
    int GetFirstDigit(const string& Input) const;
    
    int TranslateLine(const string& Input) const;
};
