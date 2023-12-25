#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

namespace AoCHelpers
{
    vector<string> ProcessInput(const int ProblemNumber);
    vector<string> ProcessInput(const string& Path);
    vector<string> Tokenize(const string& InputString, const char& Token);
    float distance(int x1, int y1, int x2, int y2);
    float distance(int x1, int y1, int x2, int y2);

    template<typename T>
    void LogList(const vector<T>& List)
    {
        for(const auto& ListElement : List)
        {
            cout << ListElement << " ";
        }
        
        cout << endl;
    }
}

class IAocSolution
{
public:
    virtual void Initialize(const vector<string>& Input) = 0;
    virtual string GetResult(const int Part) = 0;
};
