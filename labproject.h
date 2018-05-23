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
		double getFitness()
		{
			return this->fitness;
		}
		void clearCoeficients()
		{
			this->coeficients.clear();
		}
		void getSumOfResults(table t)
	{
		int e;
		int c;
		for(e=0; e<t.getTableSize(); e++)
		{
			int s = 1;
			double result = 0;
			for(c=0;c<this->size();c++)
			{
				result += this->getCoeficient(c)*pow(t.getTableEntry(e).getX(), this->size() - s);
				s += 1;
			}
			this->addResult(result);
		}
	}
	private:
		vector <double> coeficients;
		double fitness;
		vector <double> resY;
		int mateSelector;

};

class population//Recebe de Offspring organisms e seleliciona os melhores (fittest), depois os devolve para Offspring
{
public:
	void setOrganisms(genome a)
	{
			this->organisms.push_back(a);
	}
	genome getOrganisms(int i)
	{
		return this->organisms[i];
	}
	vector<genome> getFittest()
	{
		return this->fittest;
	}
	int getPopulationSize()
	{
		return this->organisms.size();
	}
	void setPopulationFitness(table t)
	{
		int i;
		for(i=0;i<this->organisms.size();i++)
		{
			this->organisms[i].setFitness(t);
		}
	}
	void getAllSums(table t)
	{
		int i;
		for(i=0;i<this->organisms.size();i++)
		{
			this->organisms[i].getSumOfResults(t);
		}
	}
	void setFittest()
	{
		vector<double> orderedFitness;
		vector<double> f;
		int i;
		for(i=0;i<this->getPopulationSize();i++)
		{
			f.push_back(getOrganisms(i).getFitness());
		}
		int temp = 0;
		for(i=0;i<f.size();i++)
		{
			if(f[i]>temp)
			{
				temp = int(f[i]);
			}
		}
		temp++;
		int m[temp];
		for(i=0;i<temp;i++)
		{
			m[i] = 0;
		}
		int k;
		for(i=0;i<temp;i++)
		{
			for(k=0;k<f.size();k++)
			{
				if(f[k]==i)
				{
					m[i] == 1;
				}
			}
		}
		for(i=0;i<temp;i++)
		{
			if(m[i]==1)
			{
				for(k=0;k<f.size();k++)
				{
					if(int(f[k])==i)
					{
						orderedFitness.push_back(f[k]);
					}
				}
			}
		}
		this->benchMark = orderedFitness[int(0.05*orderedFitness.size())];
		for(i=0;i<this->organisms.size();i++)
		{
			if(organisms[i].getFitness() <= this->benchMark)
			{
				this->fittest.push_back(organisms[i]);
			}
		}
	}

	/*vector<genome> getOffspring(int i, int j)
	{

		return this->offspring;
	}*/

private:
	double benchMark;
	vector <genome> organisms;
	vector <genome> fittest;
};

class Offspring//Manda a offspring para population e recebe de volta os melhores fittest
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
	virtual void makeOffspring(int num) = 0;
	/*void makeOffspring(int num)
	{
		randNum numGen;
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

	}*/
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

/*class polynomy: public table, public genome
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
};*/

class GA
{
	private:
		population pop;
		int deg;
		int n_gen;
		int c_gen;
		table tab;
		
	public:
		GA(int deg, int n_gen): deg(deg), n_gen(n_gen), c_gen(0){
			table t;//inicializa uma tabela que solicita ao usuario o numero de entradas e valores de x e y para cada entrada
			this->tab = t;
		}

		void generateRandomPopulation(){
			int i;
			int k;
			randNum numGen;
			for(i=0;i<1000;i++)
			{
				genome g;
				for(k=0;k<this->deg;k++)
				{
					g.addCoeficient(numGen.nextFloat(0, 1000));
				}
				this->pop.setOrganisms(g);
				g.clearCoeficients();
			}
			for(i=0;i<this->pop.getPopulationSize();i++)
			pop.getAllSums(this->tab);
			pop.setPopulationFitness(tab);
		}

		void run()
		{

		}

};



//to do list:
//introduce the mutation function in Offpring->fittest