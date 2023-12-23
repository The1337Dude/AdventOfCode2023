#include "AoCSolution3.h"

#include <stdlib.h>
#include <map>
#include <set>

using namespace std;

void AoCSolution3::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution3::GetResult(const int Part)
{
    int Result = 0;
    
    vector<Symbol> SymbolData;
    map<PositionType, int> NumberPositionMap;
    
    int MaxRow = 0;
    int MaxColumn = (int)InputData.size() - 1;
    
    for(auto RowIndex = 0; RowIndex < InputData.size(); RowIndex++)
    {
        const auto RowWidth = (int)InputData[RowIndex].size();
        MaxRow = RowWidth;
        for(auto ColumnIndex = 0; ColumnIndex < RowWidth; ColumnIndex++)
        {
            const auto& Token = InputData[RowIndex][ColumnIndex];
            if(!isnumber(Token))
            {
                if(Token == '.')
                {
                    continue;
                }
                
                Symbol SymbolInstance;
                SymbolInstance.Value = Token;
                SymbolInstance.Position = {RowIndex, ColumnIndex};
                cout << SymbolInstance.Position.first << " " << SymbolInstance.Position.second << " " << SymbolInstance.Value << endl;
                SymbolData.push_back(move(SymbolInstance));
                continue;
            }
            
            for(auto Position = ColumnIndex; Position < RowWidth; Position++)
            {
                if(!isnumber(InputData[RowIndex][Position]))
                {
                    ColumnIndex = Position - 1;
                    break; 
                }
                
                const PositionType NumberPosition = {RowIndex, Position};
                NumberPositionMap.insert({NumberPosition, atoi(&Token)});
                cout << NumberPosition.first << " " << NumberPosition.second << " " << NumberPositionMap[NumberPosition] << endl;
            }
        }
    }
    
    long long int Part2Result = 0;
    for(const auto& SymbolInstance : SymbolData)
    {
        vector<int> GearRatioList;
        cout << "---------" << endl;
        
        cout << SymbolInstance.Value << endl;
        
        set<int> Values;
        
        
        const vector<PositionType> TopRowPositionModifiers = { {-1, -1}, {-1,0}, {-1,1} };
        for(const auto& Position : SymbolInstance.GetRelativePositions(MaxColumn, MaxRow, TopRowPositionModifiers))
        {
            if(NumberPositionMap.contains(Position))
            {
                Values.insert(NumberPositionMap[Position]);
            }
        }
        
        for(const auto& Value : Values)
        {
            cout << Value << endl;
            Result += Value;
            GearRatioList.push_back(Value);
        }
        
        const vector<PositionType> SameRowPositionModifiers = {{0,1}, {0,-1}};
        for(const auto& Position : SymbolInstance.GetRelativePositions(MaxColumn, MaxRow, SameRowPositionModifiers))
        {
            if(NumberPositionMap.contains(Position))
            {
                cout << NumberPositionMap[Position] << endl;
                Result += NumberPositionMap[Position];
                GearRatioList.push_back(NumberPositionMap[Position]);
            }
        }
        
        Values.clear();
        
        const vector<PositionType> BottomRowPositionModifiers = { {1,1}, {1,0}, {1,-1} };
        for(const auto& Position : SymbolInstance.GetRelativePositions(MaxColumn, MaxRow, BottomRowPositionModifiers))
        {
            if(NumberPositionMap.contains(Position))
            {
                Values.insert(NumberPositionMap[Position]);
            }
        }
        
        for(const auto& Value : Values)
        {
            cout << Value << endl;
            Result += Value;
            GearRatioList.push_back(Value);
        }
        
        if(GearRatioList.size() == 2)
        {
            Part2Result += GearRatioList[1] * GearRatioList[0];
        }
    }

    return Part == 1 ? to_string(Result) : to_string(Part2Result);
}

vector<PositionType> Symbol::GetRelativePositions(const int MaxColumn, const int MaxRow, const vector<PositionType> &PositionModifiers) const
{
    vector<PositionType> RelativePositions;
    
    for(const auto& PositionModifier : PositionModifiers)
    {
        const PositionType AdjacentPosition = { Position.first + PositionModifier.first, Position.second + PositionModifier.second };
        if(AdjacentPosition.first >= 0 && AdjacentPosition.second >= 0 &&
           AdjacentPosition.second <= MaxColumn && AdjacentPosition.first <= MaxRow)
        {
            RelativePositions.push_back(AdjacentPosition);
        }
    }
    
    return RelativePositions;
}
