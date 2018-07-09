// requires Random1.cpp
#include "Random1.h"
#include <iostream>
#include <cmath>
using namespace std;
double DDOMonteCarlo1(double Expiry,
	double UpperStrike,
	double LowerStrike,
	double Spot,
	double Vol,
	double r,
	unsigned long NumberOfPaths)
{
	double variance = Vol * Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double movedSpot = Spot * exp(r*Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot * exp(rootVariance*thisGaussian);
		double thisPayoff;
		double LowerPayoffcheck = thisSpot - LowerStrike;
		double UpperPayoffcheck = thisSpot - UpperStrike;
		thisPayoff = LowerPayoffcheck >0 ? 1 : 0;
		UpperPayoffcheck = LowerPayoffcheck >0 ? UpperPayoffcheck : 1;
		thisPayoff = UpperPayoffcheck <0 ? 1 : 0;
		runningSum += thisPayoff;
	}
	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r * Expiry);
	return mean;
}
int main()
{
	double Expiry;
	double UpperStrike;
	double LowerStrike;
	double Spot;
	double Vol;
	double r;
	unsigned long NumberOfPaths;
	cout << "\nThis is the MC simulator for double digital option.\n";
	cout << "\nEnter expiry\n";
	cin >> Expiry;
	cout << "\nEnter Upperstrike\n";
	cin >> UpperStrike;
	cout << "\nEnter Lowerstrike\n";
	cin >> LowerStrike;
	cout << "\nEnter spot\n";
	cin >> Spot;
	cout << "\nEnter volatility\n";
	cin >> Vol;
	cout << "\nr\n";
	cin >> r;
	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;
	double result = DDOMonteCarlo1(Expiry,
		UpperStrike,
		LowerStrike,
		Spot,
		Vol,
		r,
		NumberOfPaths);
	cout << "the price is " << result << "\n";
	double tmp;
	cin >> tmp;
	return 0;}