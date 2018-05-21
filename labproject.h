#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

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

class tableEntry
{
public:
	void setTableEntries(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	double getX()
	{
		return this->x;
	}
	double getY()
	{
		return this->y;
	}
	void setX(double x)
	{
		this->x = x;
	}
	void setY(double y)
	{
		this->y = y;
	}
	virtual ~tableEntry(){}
protected:
	double x;
	double y;
};

class table: public tableEntry
{
public:
	table()
	{
		cout << "Quantas entradas serao incluidas na tabela x-y? ";
		cin >> this->numberOfEntries;
		int i;
		for(i=0;i<this->numberOfEntries;i++)
		{
			cout << "Digite o valor de x " << "da " << i+1 << " entrada na tabela: ";
			cin >> this->x;
			puts("");
			cout << "Digite o valor de y " << "da " << i+1 << " entrada na tabela: ";
			cin >> this->y;
			puts("");
			tableEntry t;
			t.setTableEntries(this->x, this->y);
			this->xyTable.push_back(t);
		}
	}
	void addToTable(tableEntry tEntry)
	{
		xyTable.push_back(tEntry);
	}
	int getTableSize()
	{
		return numberOfEntries;
	}
	tableEntry getTableEntry(int e)
	{
		return xyTable[e];
	}
private:
	int numberOfEntries;
	vector <tableEntry> xyTable;
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
		void addResult(double r)
		{
			resY.push_back(r);
		}
		void setFitness(table t)
		{
			int r;
			this->fitness = 0;
			for(r=0;r<this->resY.size();r++)
			{
				double temp_res = this->resY[r] - t.getTableEntry(r).getY();
				if(temp_res<0)
				{
					temp_res *= (-1);
				}
				this->fitness += temp_res;
			}
		}
	private:
		vector <double> coeficients;
		double fitness;
		vector <double> resY;
		int mateSelector;

};

class population//Get the organisms and pick the fittest ones, then return them back to Offspring
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

	/*vector<genome> getOffspring(int i, int j)
	{

		return this->offspring;
	}*/

private:
	vector <genome> organisms;
	vector <genome> fittest;
};

class Offspring//Get the offspring and give it to population, then receive back the fittest ones
{
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
	virtual /*vector<genome>*/ void makeOffspring(int num) = 0;
};

class onePointCross: public Offspring
{
private:
	randNum numGen;

	public:
		//populationOffspring(vector<genome> fit) : Offspring(fit){}

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

class polynomy: public table, public genome
{
public:
	void makePolynomy(genome g, table t)
	{
		int e;
		int c;
		for(e=0; e<t.getTableSize(); e++)
		{
			int s = 1;
			double result = 0;
			for(c=0;c<g.size();c++)
			{
				result += g.getCoeficient(c)*pow(t.getTableEntry(e).getX(), g.size() - s);
				s += 1;
			}
			g.addResult(result);
		}
	}
};

class GA
{
	private:
		population pop;
		int deg;
		int n_gen;
		int c_gen;
		
	public:
		GA(int deg, int n_gen, table tab): deg(deg), n_gen(n_gen), c_gen(0){

		}

		void generateRandomPopulation(){

		}

};



//to do list:
//determine fittness (run the genome through the table comparing the results then sum the results)
//(the ones closest to zero are the fittest)
//introduce the mutation function in Offpring->fittest