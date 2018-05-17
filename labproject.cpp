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
    int j;
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

    vector <genome*> temp_initialPopulation;
    vector <genome> initialPopulation;
    for(i=0;i<10;i++)
    {
    	temp_initialPopulation.push_back(new genome);
    	initialPopulation.push_back(*(temp_initialPopulation[i]));
    }
    temp_initialPopulation.clear();

	for(j=0;j<initialPopulation.size();j++)
	{
		for(i=0;i<(coef + 1);i++)
		{
			initialPopulation[j].setCoeficient(dist(rng));
			cout << initialPopulation[j].getCoeficient(i) << " ";
		}
		puts("");
	}
	return 0;
}