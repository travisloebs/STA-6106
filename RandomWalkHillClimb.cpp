// ConsoleApplication9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <iostream>
using namespace std;
void randomWalk(const int n, double & lam1, double & lam2, double & lam3,
	default_random_engine & generator,
	normal_distribution <double> & rnorm);
double objectiveFunc(const double lam1, const double lam2, const double lam3);


int _tmain(int argc, _TCHAR* argv[])
{
	const int n = 1000000;
	random_device rd;
	default_random_engine generator(rd());
	normal_distribution<double> rnorm(0.0, 1.0);

	// Set initial values
	double lam1 = 100.0;
	double lam2 = 100.0;
	double lam3 = 100.0;

	randomWalk(n, lam1, lam2, lam3, generator, rnorm);

	return 0;
}

void randomWalk(const int n, double & lam1, double & lam2, double & lam3,
default_random_engine & generator,
normal_distribution <double> & rnorm)
{
	double temp1;
	double temp2;
	double temp3;

	for (int i = 0; i < n; i++)
	{
		temp1 = lam1 + rnorm(generator);
		if (temp1 < 0)
			temp1 = 0;
		temp2 = lam2 + rnorm(generator);
		if (temp2 < 0)
			temp2 = 0;
		temp3 = lam3 + rnorm(generator);
		if (temp3 < 0)
			temp3 = 0;

		if (objectiveFunc(temp1, temp2, temp3) > objectiveFunc(lam1, lam2, lam3))
		{
			lam1 = temp1;
			lam2 = temp2;
			lam3 = temp3;
		}
	}
	cout << lam1 << "  " << lam2 << "  " << lam3 << endl;
}

double objectiveFunc(const double lam1, const double lam2, const double lam3)
{
	return (15.0*lam1 + lam2 + 2.0*lam3 - 3.0 / 4.0*lam1*lam1 - 1.0 / 2.0*lam1*lam2 - 1.0 / 2.0*lam1*lam3 - 1.0 / 2.0*lam2*lam2 - 1.0 / 8.0*lam3*lam3 - 9.0);
}