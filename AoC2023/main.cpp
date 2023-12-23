#include <iostream>
using namespace std;

#include "Solutions/AoCSolution1.h"
#include "Solutions/AoCSolution2.h"
#include "Solutions/AoCSolution3.h"
#include "Solutions/AoCSolution4.h"

int main()
{
    shared_ptr<IAocSolution> Solution = make_shared<AoCSolution4>();

    Solution->Initialize(AoCHelpers::ProcessInput(4));
    
    cout << Solution->GetResult(2) << endl;

    return 0;
}
