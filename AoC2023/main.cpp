#include <iostream>
using namespace std;

#include "Solutions/AoCSolution1.h"
#include "Solutions/AoCSolution2.h"
#include "Solutions/AoCSolution3.h"
#include "Solutions/AoCSolution4.h"
#include "Solutions/AoCSolution5.h"
#include "Solutions/AoCSolution6.h"
#include "Solutions/AoCSolution7.h"
#include "Solutions/AoCSolution8.h"
#include "Solutions/AoCSolution9.h"

int main()
{
    shared_ptr<IAocSolution> Solution = make_shared<AoCSolution9>();

    Solution->Initialize(AoCHelpers::ProcessInput(9));
    
    cout << Solution->GetResult(2) << endl;

    return 0;
}
