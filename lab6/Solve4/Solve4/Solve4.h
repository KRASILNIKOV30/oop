#pragma once

struct EquationRoot4
{
	double numRoots;
	double roots[4];
};

// ¬ычисл€ем корни кубического уравнени€ ax^4 + bx^3 + cx^2 + dx + e = 0
EquationRoot4 Solve4(double a, double b, double c, double d, double e);
