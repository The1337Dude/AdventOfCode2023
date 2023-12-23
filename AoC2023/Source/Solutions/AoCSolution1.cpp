#include "AoCSolution1.h"

#include <stdlib.h>
#include <map>

using namespace std;

void AoCSolution1::Initialize(const vector<string>& FileLines)
{
    InputData = FileLines;
}

string AoCSolution1::GetResult(const int Part)
{
    if(Part == 2)
    {
        bTranslateAndCheck = true;
    }
    
    int Result = 0;
    
    for(const auto& InputLine : InputData)
    {
        const int FirstDigit = GetFirstDigit(InputLine);
        const int LastDigit = GetLastDigit(InputLine);
        
        cout << InputLine << " " << FirstDigit << LastDigit << endl;
        
        Result += FirstDigit * 10 + LastDigit;
    }
    
    return to_string(Result);
}

int AoCSolution1::GetLastDigit(const string& InputLine) const
{
    for(auto Index = InputLine.size() - 1 ; Index >= 0; Index--)
    {
        const char Char = InputLine[Index];
        
        if(isnumber(Char))
        {
            return atoi(&Char);
        }
        
        if(bTranslateAndCheck)
        {
            const auto StringSoFar = InputLine.substr(Index);
            const auto TranslatedValue = TranslateLine(StringSoFar);
            if(TranslatedValue != 0)
            {
                return TranslatedValue;
            }
        }
    }
    
    return 0;
}

int AoCSolution1::GetFirstDigit(const string& InputLine) const
{
    for(auto Index = 0 ; Index < InputLine.size(); Index++)
    {
        const char Char = InputLine[Index];
        if(isnumber(Char))
        {
            return atoi(&Char);
        }
        
        if(bTranslateAndCheck)
        {
            const auto StringSoFar = InputLine.substr(0, Index + 1);
            const auto TranslatedValue = TranslateLine(StringSoFar);
            if(TranslatedValue != 0)
            {
                return TranslatedValue;
            }
        }
    }
    
    return 0;
}

int AoCSolution1::TranslateLine(const string& Input) const
{
    map<string, int> Dictionary = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    
    for(const auto& DictionaryEntry : Dictionary)
    {
        if(Input.find(DictionaryEntry.first) != string::npos)
        {
            return DictionaryEntry.second;
        }
    }
    
    return 0;
}
