#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

class genome
{
	public:
		void setCoeficient(double b)
		{
			coeficients.push_back(b);		
		}

		int getCoeficient(int c)
		{
			return this->coeficients[c];
		}
		void setMateSelector(int n)
		{
			mt19937 rng;
		    rng.seed(random_device()());
		    uniform_int_distribution<mt19937::result_type> distn(0,n);
		    this->mateSelector = distn(rng);
		}
		int getMateSelector()
		{
			return this->mateSelector;
		}
	private:
		vector <double> coeficients;
		double fitness;
		int mateSelector;

};

class tableEntry
{
public:
	tableEntry()
	{
		cout << "Digite o valor de x: ";
		cin >> this->x;
		puts("");
		cout << "Digite o valor de y: ";
		cin >> this->y;
		puts("");
	}

	int getX()
	{
		return this->x;
	}
	int getY()
	{
		return this->y;
	}
private:
	int x;
	int y;
};

class population
{
public:
	void setOrganisms(vector<genome> a, int e)
	{
		for(e=0;e<a.size();e++)
		{
			this->organisms.push_back(a[e]);
		}
	}
	vector<genome> getOrganisms(int i)
	{
		return this->organisms;
	}
	vector<genome> getFittest(int i)
	{
		return this->fittest;
	}
private:
	vector <genome> organisms;
	vector <genome> fittest;
};

class populationOffspring: public genome
{
	public:
		void setOffspring()
		{
			
		}
		vector<genome> getOffspring()
		{
			return this->offspring;
		}
	private:
		genome mate1;
		genome mate2;
		vector<genome> offspring;
};