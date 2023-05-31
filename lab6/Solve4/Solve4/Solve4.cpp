#include "Solve4.h"
#include <stdexcept>
#include<iostream>
#include<math.h>
#include<conio.h>
#include<stdlib.h>

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (a == 0)
	{
		throw std::invalid_argument("Higher coefficient cannot be zero");
	}

	int i;
	double y1, z1, x, y, p, q, r, z;

	b = b / a; 
	c = c / a;
	d = d / a; 
	e = e / a;
	a = 1;
	y = d / c; 
	z = e / c;
	x = 1;

	for (i = 1; i <= 800; i++)
	{
		y1 = (d - z * (b - y)) / ((c - z) - y * (b - y));
		z1 = e / ((c - z) - y * (b - y));
		y = y1;
		z = z1;

		p = 1;
		q = b - y;
		r = (c - z) - y * (b - y);
	}

	double delta1, delta2;
	delta1 = q * q - 4 * p * r;
	delta2 = y * y - 4 * x * z;

	double r1, r2, r3, r4;

	if (delta1 >= 0)
	{
		r1 = (-q + sqrt(delta1)) / (2 * p);
		r2 = (-q - sqrt(delta1)) / (2 * p);
	}
	if (delta2 >= 0)
	{
		r3 = (-y + sqrt(delta2)) / (2 * x);
		r4 = (-y - sqrt(delta2)) / (2 * x);
	}

	return EquationRoot4({ 4, {r1, r2, r3, r4} });
}