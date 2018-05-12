#include <cstdlib>
#include <iostream>
#include "labproject.h"
#include <random>
#include <vector>
using namespace std;

int main()
{

	//____________________Random number generator_______________________

	mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist(0,100);

    //______________End of random number generator______________________


    vector <tableEntry*> temp_table;
    vector <tableEntry> table;

    int e;
    int i;
    cout << "Digite o numero de entradas da tabale x->y:";
    cin >> e;

    for(i=0;i<e;i++)
    {
    	temp_table.push_back(new tableEntry);
    }
     for(i=0;i<e;i++)
    {
    	table.push_back(*(temp_table[i]));
    }
    temp_table.clear();

    for(i=0;i<table.size();i++)
    {
    	cout << "x: " << table[i].getX() << " y: " << table[i].getY() << endl;
    }

	genome g1;
	int coef;
	cout << "Digite o grau do polinomio: ";
	cin >> coef;

	for(i=0;i<(coef + 1);i++)
	{
		g1.setCoeficient(dist(rng));
		cout << g1.getCoeficient(i) << " ";
	}
	puts("");
	return 0;
}