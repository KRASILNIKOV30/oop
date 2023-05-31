#include "Solve4.h"
#include <stdexcept>
#include<iostream>
#include<math.h>
#include<conio.h>
#include<stdlib.h>
#include <vector> 
#include "./Common.h"

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	const int IMAX = 1000;

	if (a == 0)
	{
		throw std::invalid_argument("Higher coefficient cannot be zero");
	}

	double y1, z1, y, q, r, z;

	b = b / a; 
	c = c / a;
	d = d / a; 
	e = e / a;
	y = d / c; 
	z = e / c;

	for (int i = 1; i <= IMAX; i++)
	{
		y1 = (d - z * (b - y)) / ((c - z) - y * (b - y));
		z1 = e / ((c - z) - y * (b - y));
		y = y1;
		z = z1;
		q = b - y;
		r = (c - z) - y * (b - y);
	}

	std::vector<double> roots = {};
	double delta1, delta2;
	delta1 = q * q - 4 * r;
	delta2 = y * y - 4 * z;

	if (AreDoublesEqual(delta1, 0)) 
	{
		delta1 = 0;
	}
	if (AreDoublesEqual(delta2, 0))
	{
		delta2 = 0;
	}

	if (delta1 >= 0)
	{
		roots.push_back((-q + sqrt(delta1)) / 2);
		roots.push_back((-q - sqrt(delta1)) / 2);
	}
	if (delta2 >= 0)
	{
		roots.push_back((-y + sqrt(delta2)) / 2);
		roots.push_back((-y - sqrt(delta2)) / 2);
	}
	
	if (roots.size() == 0)
	{
		throw std::domain_error("The equation has no real roots");
	}

	EquationRoot4 solution = {};
	solution.numRoots = (double)roots.size();
	std::copy(roots.begin(), roots.end(), solution.roots);
	return solution;
}