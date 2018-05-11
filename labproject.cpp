#include <cstdlib>
#include <iostream>
#include "labproject.h"
#include <random>

using namespace std;

int main()
{

	//____________________Random number generator_______________________

	mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist(0,100);

    //______________End of random number generator______________________


    vector <table*> t;
    t.push_back(new table);

	int j;
	genome g1;
	for(j=0;j<6;j++)
	{
		g1.setCoeficient(dist(rng));
		cout << g1.getCoeficient(j) << " ";
	}
	puts("");
	return 0;
}