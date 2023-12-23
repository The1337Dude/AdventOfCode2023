
#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>
#include <map>

enum class ECubeColor : int
{
    Red,
    Green,
    Blue,
};

struct GameRound
{
    map<ECubeColor, int> ReveleadCubeData;
    
    bool IsValid(const map<ECubeColor, int>& BagData) const;
};

struct Game
{
    int Id = 0;
    vector<GameRound> RoundData;
    bool IsValid(const map<ECubeColor, int>& BagData) const;
    int GetPower() const;
};

class AoCSolution2 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
    
private:
    vector<string> InputData;

private:
    Game GetGameData(const string& Input) const;
};
