#include "AoCSolution7.h"

#include <map>

using namespace std;

namespace AoCHelpers
{
    void LogCard(const Hand& HandEntry)
    {
        cout << "Hand: " << HandEntry.Cards[0] << HandEntry.Cards[1] << HandEntry.Cards[2] << HandEntry.Cards[3] << HandEntry.Cards[4];
        switch (HandEntry.Type) {
            case EHandType::HighCard:
                cout << " Type: HighCard" << endl;
                break;
            case EHandType::OnePair:
                cout << " Type: OnePair" << endl;
                break;
            case EHandType::TwoPair:
                cout << " Type: TwoPair" << endl;
                break;
            case EHandType::ThreeOfAKind:
                cout << " Type: ThreeOfAKind" << endl;
                break;
            case EHandType::FullHouse:
                cout << " Type: FullHouse" << endl;
                break;
            case EHandType::FourOfAKind:
                cout << " Type: FourOfAKind" << endl;
                break;
            case EHandType::FiveOfAKind:
                cout << " Type: FiveOfAKind" << endl;
                break;
            default:
                break;
        }
    }
}

void AoCSolution7::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution7::GetResult(const int Part)
{
    ParseHandData(Part);
    
    map<char, int> ValueMap = {{'A', 14}, {'K',13}, {'Q',12}, {'J', 11}, {'T', 10}, {'9', 9}, {'8',8}, {'7',7}, {'6',6}, {'5',5}, {'4',4}, {'3',3}, {'2',2}};
    if(Part == 2)
    {
        ValueMap['J'] = 1;
    }
    
    const auto Comparator = [&ValueMap](const Hand& A, const Hand& B)
    {
        if(A.Type == B.Type)
        {
            for(auto Index = 0; Index < A.Cards.size(); Index++)
            {
                const auto ACardValue = ValueMap[A.Cards[Index]];
                const auto BCardValue = ValueMap[B.Cards[Index]];
                if(ACardValue == BCardValue)
                {
                    continue;
                }
                
                return ACardValue < BCardValue;
            }
        }
        
        return A.Type < B.Type;
    };
    
    sort(HandData.begin(), HandData.end(), Comparator);
    
    long long Result = 0;
    for(auto Index = 0; Index < HandData.size(); Index++)
    {
        Result += (Index + 1) * HandData[Index].Bid;
    }
    
    return to_string(Result);
}

void AoCSolution7::ParseHandData(const int Part)
{
    for(const auto& InputLine : InputData)
    {
        const auto Tokens = AoCHelpers::Tokenize(InputLine, ' ');
        
        if(Tokens.size() != 2)
        {
            continue;
        }
        
        Hand HandEntry;
        HandEntry.Cards = {Tokens[0][0], Tokens[0][1], Tokens[0][2], Tokens[0][3], Tokens[0][4]};
        HandEntry.Bid = atoi(Tokens[1].c_str());
        HandEntry.Type = ComputeHandType(HandEntry.Cards, Part);
        
        AoCHelpers::LogCard(HandEntry);
        
        HandData.push_back(move(HandEntry));
    }
}

EHandType AoCSolution7::ComputeHandType(const vector<char>& InCards, const int Part)
{
    map<char, int> CardCountMap;
    for(const auto& Card : InCards)
    {
        CardCountMap[Card]++;
    }
    
    const auto HasJ = [&CardCountMap]()
    {
        return CardCountMap.contains('J');
    };
    
    const auto GetJCount = [&CardCountMap, HasJ]()
    {
        if(!HasJ())
        {
            return 0;
        }
        
        return CardCountMap['J'];
    };
    
    if(CardCountMap.size() == 1)
    {
        return EHandType::FiveOfAKind;
    }
    
    if(CardCountMap.size() == 2)
    {
        if(Part == 2 && HasJ())
        {
            return EHandType::FiveOfAKind;
        }
        
        const auto CardCount = CardCountMap.begin()->second;
        if( CardCount == 1 || CardCount == 4)
        {
            return EHandType::FourOfAKind;
        }
        
        return EHandType::FullHouse;
    }
    
    if(CardCountMap.size() == 3)
    {
        for(const auto& CardCountEntry : CardCountMap)
        {
            if(CardCountEntry.second == 3)
            {
                if(Part == 2 && HasJ())
                {
                    return EHandType::FourOfAKind;
                }
                
                return EHandType::ThreeOfAKind;
            }
        }
        
        if(Part == 2)
        {
            const int JCount = GetJCount();
            if(JCount == 2)
            {
                return EHandType::FourOfAKind;
            }
            
            if(JCount == 1)
            {
                return EHandType::FullHouse;
            }
        }
        return EHandType::TwoPair;
    }
    
    if(CardCountMap.size() == 4)
    {
        if(Part == 2 && HasJ())
        {
            return EHandType::ThreeOfAKind;
        }
        
        return EHandType::OnePair;
    }
    
    if(Part == 2 && HasJ())
    {
        return EHandType::OnePair;
    }
    
    return EHandType::HighCard;
}
