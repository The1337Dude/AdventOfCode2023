#include "AoCSolution9.h"
#include <numeric>

void AoCSolution9::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution9::GetResult(const int Part)
{
    ParseReadings();
    
    long long Result = 0;
    for(const auto& InReadings : ReadingData)
    {
        auto Readings = InReadings;
        if(Part == 2)
        {
            reverse(Readings.begin(), Readings.end());
        }
        
        cout << "Readings: ";
        AoCHelpers::LogList(Readings);
        
        const auto NextReading = GetNextReading(Readings);
        cout << NextReading << endl;
        Result += NextReading;
    }
    
    return to_string(Result);
}

void AoCSolution9::ParseReadings()
{
    for(const auto& InputLine : InputData)
    {
        vector<long long> Readings;
        for(const auto& Token : AoCHelpers::Tokenize(InputLine, ' '))
        {
            Readings.push_back(atoll(Token.c_str()));
        }
        ReadingData.push_back(move(Readings));
    }
}

long long AoCSolution9::GetNextReading(const vector<long long>& Readings)
{
    if(Readings.empty())
    {
        return 0;
    }
    
    bool bAllAreTheSame = true;
    for(const auto& Reading : Readings)
    {
        bAllAreTheSame &= Reading == Readings[0];
    }
    
    if(bAllAreTheSame)
    {
        return Readings[0];
    }
    
    vector<long long> DifferenceList;
    for(auto Index = 0; Index < Readings.size() - 1; Index++)
    {
        const auto Difference = Readings[Index + 1] - Readings[Index];
        DifferenceList.push_back(Difference);
    }
    cout << "\t Difference List: " << "Size: " << DifferenceList.size() << " : ";
    AoCHelpers::LogList(DifferenceList);
    
    return Readings.back() + GetNextReading(DifferenceList);
}
