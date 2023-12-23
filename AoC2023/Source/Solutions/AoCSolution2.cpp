#include "AoCSolution2.h"

#include <stdlib.h>


using namespace std;

void AoCSolution2::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution2::GetResult(const int Part)
{
    int Result = 0;
    
    const map<ECubeColor, int> BagData = {{ECubeColor::Red, 12}, {ECubeColor::Green, 13}, {ECubeColor::Blue, 15} };
    
    for(const auto& Input : InputData)
    {
        const auto GameData = GetGameData(Input);
        
        if(Part == 1)
        {
            if(GameData.IsValid(BagData))
            {
                cout << GameData.Id << endl;
                Result += GameData.Id;
            }
        }
        
        if(Part == 2)
        {
            const int Power = GameData.GetPower();
            cout << Power << endl;
            Result += Power;
        }
    }
    
    return to_string(Result);
}

Game AoCSolution2::GetGameData(const std::string &Input) const
{
    // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    // Split on : first
    
    const auto& GameDataStringList = AoCHelpers::Tokenize(Input, ':');
    
    if(GameDataStringList.size() != 2)
    {
        return {};
    }
    
    Game GameData;
    
    // Parse Id
    const auto IdString = AoCHelpers::Tokenize(GameDataStringList[0], ' ')[1];
    GameData.Id = atoi(IdString.c_str());
    
    // Parse Rounds
    for(const auto& RoundString : AoCHelpers::Tokenize(GameDataStringList[1], ';'))
    {
        GameRound RoundData;
        
        for(const auto& CubeDataString: AoCHelpers::Tokenize(RoundString, ','))
        {
            const auto& CubeDataStringTokens = AoCHelpers::Tokenize(CubeDataString, ' ');
            
            const auto NumberOfCubes = atoi(CubeDataStringTokens[1].c_str());
            
            const auto CubeColorString = CubeDataStringTokens[2];
            
            if(CubeColorString == "red")
            {
                RoundData.ReveleadCubeData.insert({ECubeColor::Red, NumberOfCubes});
            }
            
            if(CubeColorString == "green")
            {
                RoundData.ReveleadCubeData.insert({ECubeColor::Green, NumberOfCubes});
            }
            
            if(CubeColorString == "blue")
            {
                RoundData.ReveleadCubeData.insert({ECubeColor::Blue, NumberOfCubes});
            }
        }
        
        GameData.RoundData.push_back(move(RoundData));
    }
    
    return GameData;
}

bool GameRound::IsValid(const map<ECubeColor, int>& BagData) const
{
    for(const auto& RevealedCubeDataEntry :  ReveleadCubeData)
    {
        if(!BagData.contains(RevealedCubeDataEntry.first))
        {
            return false;
        }
        
        const auto ExpectedValue = BagData.find(RevealedCubeDataEntry.first);
        if( ExpectedValue->second < RevealedCubeDataEntry.second)
        {
            return false;
        }
    }
    
    return true;
}

bool Game::IsValid(const map<ECubeColor, int>& BagData) const
{
    for(const auto& Round : RoundData)
    {
        if(!Round.IsValid(BagData))
        {
            return false;
        }
    }
    
    return true;
}

int Game::GetPower() const
{
    map<ECubeColor, int> MinCubes {{ECubeColor::Red, 0}, {ECubeColor::Green, 0}, {ECubeColor::Blue, 0}};
    for(const auto& Round : RoundData)
    {
        for(auto& MinCubesEntry : MinCubes)
        {
            const auto NumberOfCubes = Round.ReveleadCubeData.find(MinCubesEntry.first);
            if(NumberOfCubes != Round.ReveleadCubeData.cend())
            {
                MinCubesEntry.second = max(NumberOfCubes->second, MinCubesEntry.second);
            }
        }
    }
    
    return MinCubes[ECubeColor::Red] * MinCubes[ECubeColor::Green] * MinCubes[ECubeColor::Blue];
}
