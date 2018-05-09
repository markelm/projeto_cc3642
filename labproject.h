#include <cstdlib>
#include <iostream>
#include <vector>
#import <random>

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