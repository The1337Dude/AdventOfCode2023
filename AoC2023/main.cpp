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

int main()
{
    shared_ptr<IAocSolution> Solution = make_shared<AoCSolution8>();

    Solution->Initialize(AoCHelpers::ProcessInput(8));
    
    cout << Solution->GetResult(2) << endl;

    return 0;
}
