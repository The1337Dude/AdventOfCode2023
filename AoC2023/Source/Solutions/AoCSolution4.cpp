#include "AoCSolution4.h"

#include <cmath>
#include <map>

using namespace std;

namespace AoCSolution4Helpers
{
    int CalculateTotalWinningCards(const int CardId, const map<int, int>& ScratchCardMatchesData)
    {
        int Sum = 1;
        const int NumberOfMatches = ScratchCardMatchesData.at(CardId);
        int NumberOfBelowCards = CardId + 1 + NumberOfMatches;
        for(int CardIndex = CardId + 1; CardIndex < NumberOfBelowCards; CardIndex++)
        {
            if(ScratchCardMatchesData.contains(CardIndex))
            {
                Sum += CalculateTotalWinningCards(CardIndex, ScratchCardMatchesData);
            }
        }
        
        return Sum;
    }
}

int ScratchCard::GetMatches() const
{
    vector<int> Matches;
    set_intersection(WinningNumbers.begin(), WinningNumbers.end(), PlayerNumbers.begin(), PlayerNumbers.end(), inserter(Matches, Matches.begin()));
    
    cout << "Matches: ";
    for(const auto& Number : Matches)
    {
        cout << Number << " ";
    }
    
    return (int)Matches.size();
}

int AoCSolution4::GetWorth(const int NumberOfMatches) const
{
    return NumberOfMatches == 0 ? 0 : pow(2, NumberOfMatches - 1);
}

void AoCSolution4::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution4::GetResult(const int Part)
{
    int Part1Result = 0;
    map<int, int> ScratchCardMatchesData;
    for(const auto& Input : InputData)
    {
        const auto ScratchCard = ParseScratchCardData(Input);
        const auto NumberOfMatches = ScratchCard.GetMatches();
        const auto Worth = GetWorth(NumberOfMatches);
        cout << "Worth: " << Worth << endl;
        Part1Result += Worth;
        
        ScratchCardMatchesData.insert({ScratchCard.Id, NumberOfMatches});
    }
    
    int Part2Result = 0;
    for(const auto& ScratchCardMatchData : ScratchCardMatchesData)
    {
        Part2Result += AoCSolution4Helpers::CalculateTotalWinningCards(ScratchCardMatchData.first, ScratchCardMatchesData);
    }
    cout << "Total Winning Cards: " << Part2Result << endl;
    
    return Part == 1 ? to_string(Part1Result) : to_string(Part2Result);
}

ScratchCard AoCSolution4::ParseScratchCardData(const string& Input)
{
    // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
    auto ScratchCardDataStringList = AoCHelpers::Tokenize(Input, ' ');
    
    ScratchCard ScratchCardData;
    
    bool bAddtoWinningList = true;
    for(const auto& Token : ScratchCardDataStringList)
    {
        if(Token.empty())
        {
            continue;
        }
        
        if(Token[0] == '|')
        {
            bAddtoWinningList = false;
            continue;
        }
        
        if(!isnumber(Token[0]))
        {
            continue;
        }
        
        if(Token[Token.size() - 1] == ':')
        {
            ScratchCardData.Id = atoi(Token.c_str());
            continue;
        }
        
        const auto NumberValue = atoi(Token.c_str());
        if(bAddtoWinningList)
        {
            ScratchCardData.WinningNumbers.insert(NumberValue);
        }
        else
        {
            ScratchCardData.PlayerNumbers.insert(NumberValue);
        }
    }
    
    cout << "---------------" << endl;
    cout << "Id: " << ScratchCardData.Id << endl;
    cout << "Winning Numbers: ";
    for(const auto& Number : ScratchCardData.WinningNumbers)
    {
        cout << Number << " ";
    }
    cout << endl;
    cout << "Player Numbers: ";
    for(const auto& Number : ScratchCardData.PlayerNumbers)
    {
        cout << Number << " ";
    }
    cout << endl;
    
    return ScratchCardData;
}
