#include "AoCSolution5.h"

using namespace std;

void AoCSolution5::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution5::GetResult(const int Part)
{
    long long Part1Result = LONG_LONG_MAX;
    
    vector<long> SeedIndexes;
    
    for(int InputLineIndex = 0; InputLineIndex < InputData.size(); InputLineIndex++)
    {
        const auto& InputLine = InputData[InputLineIndex];
        if(InputLine.find("seeds:") != string::npos)
        {
            for(const auto& Token : AoCHelpers::Tokenize(InputLine, ' '))
            {
                if(Token.empty())
                {
                    continue;
                }
                
                if(!isnumber(Token[0]))
                {
                    continue;
                }
                
                SeedIndexes.push_back(atol(Token.c_str()));
            }
            continue;
        }
        
        if(InputLine.find("map:") != string::npos)
        {
            auto PossibleMapDataInputLineIndex = InputLineIndex;
            vector<string> MapDataStrings;
            while (PossibleMapDataInputLineIndex < InputData.size())
            {
                const string& PossibleMapDataInputLine = InputData[PossibleMapDataInputLineIndex];
                if(PossibleMapDataInputLine.empty() || PossibleMapDataInputLineIndex == InputData.size() - 1)
                {
                    if(PossibleMapDataInputLineIndex == InputData.size() - 1)
                    {
                        MapDataStrings.push_back(PossibleMapDataInputLine);
                    }
                    
                    ParseMapData(move(MapDataStrings));
                    InputLineIndex = PossibleMapDataInputLineIndex++;
                    break;
                }
                
                MapDataStrings.push_back(PossibleMapDataInputLine);
                PossibleMapDataInputLineIndex++;
            }
        }
    }
    
    if(Part == 1)
    {
        for(const auto& SeedIndex : SeedIndexes)
        {
            cout << "For Seed: " << SeedIndex << endl;
            const auto LocationIndex = GetLocationIndex(SeedIndex);
            cout << "Location Index: " <<  LocationIndex << endl;
            
            Part1Result = min(LocationIndex, Part1Result);
        }
        
        return to_string(Part1Result);
    }
    
    long long Part2Result = LONG_LONG_MAX;
    vector<pair<long long, long long>> SeedRanges;
    for(auto Index = 0; Index < SeedIndexes.size() - 1; Index += 2)
    {
        long long SeedIndex = SeedIndexes[Index];
        const auto Range = SeedIndexes[Index + 1];
        const long long MaxSeedIndex = SeedIndex + Range;
        
        SeedRanges.push_back({SeedIndex, MaxSeedIndex});
    }
    
    sort(SeedRanges.begin(), SeedRanges.end(), [](const pair<long long, long long>& A, const pair<long long, long long>& B){ return A.first < B.first;});
    
    const auto& LocationRanges = Maps.back().DestinationRangeList;
    const auto MaxLocation = GetMaxLocation(LocationRanges);
    for(long long Location = 0; Location < MaxLocation; Location++)
    {
//        cout << Location << endl;
        const auto SeedIndex = GetSeedIndex(Location);
        for(const auto& SeedRange : SeedRanges)
        {
            if(SeedIndex >= SeedRange.first && SeedIndex <= SeedRange.second)
            {
                return to_string(Location);
            }
        }
    }
    
    return to_string(Part2Result);
}

void AoCSolution5::ParseMapData(const vector<string>& MapDataStrings)
{
    if(MapDataStrings.empty())
    {
        return;
    }
    
    MapData Data;
    
    for(const auto& MapDataString : MapDataStrings)
    {
        const auto Tokens = AoCHelpers::Tokenize(MapDataString, ' ');
        
        if(Tokens.size() == 2)
        {
            // water-to-light map: - sample map name input
            const auto NameTokens = AoCHelpers::Tokenize(Tokens[0], '-');
            if(NameTokens.size() == 3)
            {
                Data.SourceName = NameTokens[0];
                Data.DestinationName = NameTokens[2];
            }
            continue;
        }
        
        if(Tokens.size() == 3)
        {
            // 0 15 37 - sample range input
            const auto DestinationRangeStart = atoll(Tokens[0].c_str());
            const auto SourceRangeStart = atoll(Tokens[1].c_str());
            const auto Range = atoll(Tokens[2].c_str());
            const long long SourceRangeEnd = SourceRangeStart + Range;
            const long long DestinationRangeEnd = DestinationRangeStart + Range;
            Data.SourceRangeList.push_back({SourceRangeStart, SourceRangeEnd});
            Data.DestinationRangeList.push_back({DestinationRangeStart, DestinationRangeEnd});
        }
    }
    
    Maps.push_back(move(Data));
}

long long AoCSolution5::GetLocationIndex(const long long SeedIndex)
{
    long long Result = SeedIndex;
    
    for(auto& Map : Maps)
    {
        const auto SourceIndex = Result;
        Result = Map.GetDestinationIndex(Result);
//        cout << "\t" << Map.DestinationName << " Index: " << Result << " for " << Map.SourceName << " Index: " <<  SourceIndex << endl ;
    }
    
    return Result;
}

long long AoCSolution5::GetSeedIndex(const long long LocationIndex)
{
    long long Result = LocationIndex;
    
    reverse(Maps.begin(), Maps.end());
    
    for(auto& Map : Maps)
    {
        const auto SourceIndex = Result;
        Result = Map.GetSourceIndex(Result);
//        cout << "\t" << Map.SourceName << " Index: " << Result << " for " << Map.DestinationName << " Index: " <<  SourceIndex << endl ;
    }
    
    reverse(Maps.begin(), Maps.end());
    
    return Result;
}

long long AoCSolution5::GetMaxLocation(const vector<pair<long long, long long>>& LocationRanges) const
{
    long long MaxLocation = LONG_LONG_MIN;
    
    for(const auto& LocationRange : LocationRanges)
    {
        MaxLocation = max(LocationRange.second, MaxLocation);
    }
    
    return MaxLocation;
}
