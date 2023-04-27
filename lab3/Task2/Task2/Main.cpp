#include "CommandHandler.h"
#include <iostream>

int main()
{
	Calculator tv;
	CommandHandler commandHandler(tv, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!commandHandler.HandleCommand())
		{
			std::cout << "Error!" << std::endl;
		}
	}

	return 0;
}
