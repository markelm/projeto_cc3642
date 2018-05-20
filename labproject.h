#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

class randNum{
private:
	mt19937 rng;
	
public:
	randNum(){
		rng.seed(random_device()());
	}

	int nextInt(int min, int max){
		uniform_int_distribution<mt19937::result_type> dist(min, max);
		return dist(rng);
	}

	float nextFloat(float  min, float max){
		uniform_int_distribution<mt19937::result_type> dist(min, max);
		return dist(rng);
	}

};

class genome
{
	public:
		void setCoeficient(double b, int pos)
		{
			coeficients[pos] = b;		
		}

		void addCoeficient(double b)
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

		int size(){
			return coeficients.size();
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

class GA{
	private:
		population pop;
		int deg;
		int n_gen;
		int c_gen;
		
	public:
		GA(int deg, int n_gen): deg(deg), n_gen(n_gen), c_gen(0){

		}

		void generateRandomPopulation(){

		}

};

class population
{
public:
	void setOrganisms(vector<genome> a)
	{
		int e;
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

	vector<genome> getOffspring(int i, int j)
	{

		return this->offspring;
	}

private:
	vector <genome> organisms;
	vector <genome> fittest;
};

class Offspring{
protected:
	vector<genome> fittest;
	vector<genome> offspring;

public:
	Offspring(vector<genome> fittest) : fittest(fittest){
		//rng.seed(random_device()());
	}
	
	vector<genome> getOffspring()
	{
			return this->offspring;
	}
	virtual vector<genome> makeOffspring(int num) = 0;
};

class onePointCross: public Offspring
{
private:
	randNum numGen;

	public:
		populationOffspring(vector<genome> fit) : Offspring(fit){}

	void makeOffspring(int num)
	{
		for(int k=0;k<num;k++){
			int pa = numGen.nextInt(0, fittest.size());
			int pb = numGen.nextInt(0, fittest.size());

			int p = numGen.nextInt(0, fittest[0].size());

			genome res;
			for(int i = 0 ; i< fittest[pa].size(); i++){
				if(i < p){
					res.addCoeficient(fittest[pa].getCoeficient(i));
				}else{
					res.addCoeficient(fittest[pb].getCoeficient(i));
				}
			}

			offspring.push_back(res);
		}

	}
		
};