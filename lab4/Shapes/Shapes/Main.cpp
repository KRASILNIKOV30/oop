#include <iostream>
#include "CommandHandler.h"

int main()
{
	CommandHandler commandHandler(std::cin, std::cout);

	while (!std::cin.fail())
	{
		std::cout << "> ";
		if (!commandHandler.HandleCommand())
		{
			if (std::cin.eof())
			{
				commandHandler.PrintResult();
				break;
			}
			else
			{
				std::cout << "Error!" << std::endl;
			}
		}
	}

	return 0;
}



