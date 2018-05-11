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
	private:
		vector <double> coeficients;

};

class table
{
public:
	table()
	{
		cout << "Digite o valor de x: ";
		cin >> this->x;
		puts("");
		cout << "Digite o valor de y: ";
		cin >> this->y;
		puts("");
	}
private:
	int x;
	int y;
};