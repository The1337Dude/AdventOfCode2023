#include "AoCSolution6.h"

using namespace std;

long long RaceData::GetNumberOfWaysToWin() const
{
    long long Result = 0;
    for(auto ButtonTime = 0; ButtonTime <= Time; ButtonTime++)
    {
        const auto TimeRemaining = Time - ButtonTime;
        const auto SpeedGained = ButtonTime;
        if( SpeedGained * TimeRemaining > DistanceRecord)
        {
            Result++;
        }
    }
    
    cout << "Time: " << Time << " DistanceRecord: " << DistanceRecord << " NumberOfWaysToWin: " << Result << endl;
    return Result;
}

void AoCSolution6::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
    ParseRaceData();
}

string AoCSolution6::GetResult(const int Part)
{
    long long Result = 1;
    
    for(const auto& RaceDataEntry : RaceDataEntries)
    {
        Result *= RaceDataEntry.GetNumberOfWaysToWin();
    }
    
    return to_string(Result);
}

void AoCSolution6::ParseRaceData()
{
    if(InputData.size() < 2)
    {
        return;
    }
    
    const auto TimeTokens = AoCHelpers::Tokenize(InputData[0], ' ');
    const auto DistanceTokens = AoCHelpers::Tokenize(InputData[1], ' ');
    
    for(auto TokenIndex = 1; TokenIndex < TimeTokens.size(); TokenIndex++)
    {
        RaceData Data;
        Data.Time = atoll(TimeTokens[TokenIndex].c_str());
        Data.DistanceRecord = atoll(DistanceTokens[TokenIndex].c_str());
        
        cout << "Time: " << Data.Time << " DistanceRecord: " << Data.DistanceRecord << endl;
        RaceDataEntries.push_back(move(Data));
    }
}
