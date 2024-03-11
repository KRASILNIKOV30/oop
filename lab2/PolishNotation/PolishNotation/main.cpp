#include <iostream>
#include "PolishNotation.h"

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			std::cout << CalculatePolish(line) << std::endl;
		}
		catch (std::exception const& e)
		{
			std::cout << "ERROR: " << e.what() << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}