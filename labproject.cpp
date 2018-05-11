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


    vector <tableEntry*> t;

    int e;
    int i;
    cout << "Digite o numero de entradas da tabale x->y:";
    cin >> e;

    for(i=0;i<e;i++)
    {
    	t.push_back(new tableEntry);
    }

    for(i=0;i<e;i++)
    {
    	cout << "x: " << t[i]->getX() << " y: " << t[i]->getY() << endl;
    }

	int j;
	genome g1;
	for(i=0;i<6;i++)
	{
		g1.setCoeficient(dist(rng));
		cout << g1.getCoeficient(j) << " ";
	}
	puts("");
	return 0;
}