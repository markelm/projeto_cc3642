#include <cstdlib>
#include <iostream>
#include "labproject.h"
#include <random>
#include <vector>
using namespace std;

int main()
{

    GA gen(2, 10000);
    gen.run();

	return 0;
}
