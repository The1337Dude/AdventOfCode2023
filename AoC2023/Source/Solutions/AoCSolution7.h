
#pragma once

#include "Helpers/AoCHelpers.h"
#include <vector>

enum class EHandType : int8_t
{
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind,
};

struct Hand
{
    vector<char> Cards;
    int Bid = 0;
    EHandType Type = EHandType::HighCard;
};

class AoCSolution7 : public IAocSolution
{
public:
    void Initialize(const vector<string>& Input) override;
    string GetResult(const int Part) override;

private:
    void ParseHandData(const int Part = 1);
    EHandType ComputeHandType(const vector<char>& Cards, const int Part = 1);
    
    void CompareHand(const Hand& A, const Hand& B);
    
private:
    vector<string> InputData;
    vector<Hand> HandData;
};
