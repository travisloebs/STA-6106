// ConsoleApplication9.cpp : Defines the entry point for the console application.
//

#include <random>
#include <iostream>
using namespace std;
void randomWalk(const int n, double & lam1,
	double & lam2, double & lam3,
	default_random_engine & generator,
	normal_distribution <double> & rnorm);
	void randomWalkPrimal(const int n, double & x1, double & x2,
	default_random_engine & generator,
	normal_distribution <double> & rnorm);
double dualProblem(const double lam1,
	const double lam2, const double lam3);
double primalProblem(const double x1, const double x2);


int main()
{
	// Define the number of runs
	const int n = 1000000;

	// Set up random number generator
	random_device rd;
	default_random_engine generator(rd());
	// Use standard normal for steps in each direction
	normal_distribution<double> rnorm(0.0, 1.0);

	// Set initial values
	double lam1 = 100.0;
	double lam2 = 100.0;
	double lam3 = 100.0;

	double x1 = 10.0;
	double x2 = 10.0;

	//
	randomWalk(n, lam1, lam2, lam3, generator, rnorm);
	randomWalkPrimal(n, x1, x2, generator, rnorm);
	return 0;
}

void randomWalk(const int n, double & lam1,
double & lam2, double & lam3,
default_random_engine & generator,
normal_distribution <double> & rnorm)
{
	// create temporary variables to test acceptance
	double temp1;
	double temp2;
	double temp3;

	for (int i = 0; i < n; i++)
	{
		// Take random step in direction 1
		temp1 = lam1 + rnorm(generator);
		if (temp1 < 0)
			temp1 = 0;	// Satisfy the constraint

		// Take random step in direction 2
		temp2 = lam2 + rnorm(generator);
		if (temp2 < 0)
			temp2 = 0;	// Satisfy the constraint

		// Take random step in direction 3
		temp3 = lam3 + rnorm(generator);
		if (temp3 < 0)
			temp3 = 0;	// Satisfy the constraint

		// If the new point is higher than the old one,
		// then accept the new point, otherwise reject
		if (dualProblem(temp1, temp2, temp3) > dualProblem(lam1, lam2, lam3))
		{
			lam1 = temp1;
			lam2 = temp2;
			lam3 = temp3;
		}
	}
	// Print final results to the screen
	cout << "Lambda's: " << lam1 << "  " << lam2 << "  " << lam3 << endl;
}

void randomWalkPrimal(const int n, double & x1, double & x2,
default_random_engine & generator,
normal_distribution <double> & rnorm)
{
	double temp1;
	double temp2;

	for (int i = 0; i < n; i++)
	{
		do
		{
			temp1 = x1 + rnorm(generator);
			if (temp1 < 0)
				temp1 = 0;
			temp2 = x2 + rnorm(generator);
			if (temp2 < 0)
				temp2 = 0;
		} while (-1.*temp1 - 2.*temp2 + 10. > 0.);

		if (primalProblem(temp1, temp2) < primalProblem(x1, x2))
		{
			x1 = temp1;
			x2 = temp2;
		}
	}
	cout << "\nx's: " << x1 << "  " << x2 << endl;
}

double dualProblem(const double lam1,
	const double lam2,
	const double lam3)
{
	// Return the dual problem evaluated at the given points
	return (15.0*lam1 + lam2 + 2.0*lam3 - 3.0 / 4.0*lam1*lam1
		- 1.0 / 2.0*lam1*lam2 - 1.0 / 2.0*lam1*lam3
		- 1.0 / 4.0*lam2*lam2 - 1.0 / 8.0*lam3*lam3 - 9.0);
}

double primalProblem(const double x1, const double x2)
{
	return x1*x1 + 2.*x2*x2 + 2.*x1 + 8.*x2;
}
