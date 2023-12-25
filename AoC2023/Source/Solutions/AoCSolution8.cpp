#include "AoCSolution8.h"

#include <numeric>

namespace AoCHelpers
{
    long long GCD(long long A, long long B)
    {
        if (B == 0)
            return A;
        return GCD(B, A % B);
    }
     
    long long LCM(std::vector<long long> Numbers)
    {
        long long LCM = Numbers[0];
        for (int Index = 1; Index < Numbers.size(); Index++)
        {
            long long Num1 = LCM;
            long long Num2 = Numbers[Index];
            long long GCDValue = GCD(Num1, Num2);
            LCM = (LCM * Numbers[Index]) / GCDValue;
        }
        
        return LCM;
    }
}

void AoCSolution8::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution8::GetResult(const int Part)
{
    ParseNodeData();
    
    ParseInstructions();
    
    if(Part == 1)
    {
        return to_string(GetNumberOfSteps("AAA", Part));
    }
    
    vector<long long> NumberOfSteps;
    for(const auto& NodeEndingWithA : GetNodeNamesEndingWith('A'))
    {
        const auto NumberOfStepsForNode = GetNumberOfSteps(NodeEndingWithA, Part);
        NumberOfSteps.push_back(NumberOfStepsForNode);
    }
    
    return to_string(AoCHelpers::LCM(move(NumberOfSteps)));
}

void AoCSolution8::ParseInstructions()
{
    Instructions = InputData[0];
}

void AoCSolution8::ParseNodeData()
{
    for(const auto& InputLine : InputData)
    {
        if(InputLine.find('=') == string::npos)
        {
            continue;
        }
        
        string NodeName = InputLine.substr(0, 3);
        Node NodeData;
        NodeData.Left = InputLine.substr(7,3);
        NodeData.Right = InputLine.substr(12,3);
        
        Nodes.insert({move(NodeName), move(NodeData)});
    }
}

vector<string> AoCSolution8::GetNodeNamesEndingWith(const char& EndingChar)
{
    vector<string> Result;
    
    for(const auto& NodeData : Nodes)
    {
        if(NodeData.first[NodeData.first.size() - 1] == 'A')
        {
            Result.push_back(NodeData.first);
        }
    }
    
    return Result;
}

long long AoCSolution8::GetNumberOfSteps(const string Start, const int Part) const
{
    long long Result = 0;
    
    auto NodeToCheck = Start;
    while(true)
    {
        for(const auto& Instruction : Instructions)
        {
            Result++;
            
            const auto NextNodeData = Nodes.find(NodeToCheck);
            if(NextNodeData == Nodes.end())
            {
                return 0;
            }
            
            if(Instruction == 'L')
            {
                NodeToCheck = NextNodeData->second.Left;
            }
            else
            {
                NodeToCheck = NextNodeData->second.Right;
            }

            if(Part == 1)
            {
                if(NodeToCheck == "ZZZ")
                {
                    cout << Start << "," << NodeToCheck << ": " << Result << endl;
                    return Result;
                }
            }
            else
            {
                if(NodeToCheck[NodeToCheck.size() - 1] == 'Z')
                {
                    cout << Start << "," << NodeToCheck << ": " << Result << endl;
                    return Result;
                }
            }
        }
    }
    
    return Result;
}
