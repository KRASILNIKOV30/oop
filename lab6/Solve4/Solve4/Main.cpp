#include <iostream>
#include "./Solve4.h"

int main()
{
    EquationRoot4 solution{};
    double a, b, c, d, e;
    if (std::cin >> a &&
        std::cin >> b && 
        std::cin >> c && 
        std::cin >> d &&
        std::cin >> e)
    {
        try
        {
            solution = Solve4(a, b, c, d, e);
        }
        catch (std::invalid_argument e)
        {
            std::cout << e.what();
            return 0;
        }
        catch (std::domain_error e)
        {
            std::cout << e.what();
            return 0;
        }
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
        return 0;
    }

    std::cout << "Roots:";
    for (int i = 0; i < solution.numRoots; i++)
    {
        std::cout << " " << solution.roots[i];
    }
    std::cout << std::endl;

    return 0;
}
