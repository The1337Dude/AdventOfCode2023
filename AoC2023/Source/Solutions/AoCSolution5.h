
#pragma once

#include "Helpers/AoCHelpers.h"
#include <set>
#include <vector>
#include <map>

struct MapData
{
    string SourceName;
    string DestinationName;
    vector<pair<long long, long long>> SourceRangeList;
    vector<pair<long long, long long>> DestinationRangeList;
    
    long long GetDestinationIndex(const long long SourceIndex)
    {
        for(auto Index = 0; Index < SourceRangeList.size(); Index++)
        {
            const auto& RangeData = SourceRangeList[Index];
            const long long RangeStart = RangeData.first;
            const long long RangeEnd = RangeData.second;
            
            if(SourceIndex >= RangeStart && SourceIndex <= RangeEnd)
            {
                const long long DestinationRangeStart = DestinationRangeList[Index].first;
                const long long Result = DestinationRangeStart + (SourceIndex - RangeStart);
                return Result;
            }
        }
        
        return SourceIndex;
    }
    
    long long GetSourceIndex(const long long DestinationIndex)
    {
        for(auto Index = 0; Index < DestinationRangeList.size(); Index++)
        {
            const auto& RangeData = DestinationRangeList[Index];
            const long long RangeStart = RangeData.first;
            const long long RangeEnd = RangeData.second;
            
            if(DestinationIndex >= RangeStart && DestinationIndex <= RangeEnd)
            {
                const long long SourceRangeStart = SourceRangeList[Index].first;
                const long long Result = SourceRangeStart + (DestinationIndex - RangeStart);
                return Result;
            }
        }
        
        return DestinationIndex;
    }
};

class AoCSolution5 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;
    
private:
    void ParseMapData(const vector<string>& MapDataStrings);
    
    long long GetLocationIndex(const long long SeedIndex);
    
    long long GetSeedIndex(const long long LocationIndex);
    
    long long GetMaxLocation(const vector<pair<long long, long long>>& LocationRange) const;
    
private:
    vector<string> InputData;
    vector<MapData> Maps;
    map<long long, long long> SourceCache;
    map<long long, long long> DestinationCache;
};
