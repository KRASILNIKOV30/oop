#include <iostream>
#include "CommandHandler.h"
#undef main

int main()
{
	CommandHandler commandHandler(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!commandHandler.HandleCommand())
		{
			if (std::cin.eof())
			{
				commandHandler.PrintResult();
				commandHandler.DrawShapes();
			}
			else
			{
				std::cout << "Error!" << std::endl;
			}
		}
	}
	
	return 0;
}



