#include <iostream>
#include "CommandHandler.h"
#include <windows.h>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <GLFW/glfw3.h>

int main()
{
	CommandHandler commandHandler(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!commandHandler.HandleCommand())
		{
			std::cout << "Error!" << std::endl;
		}
	}
	if (std::cin.eof())
	{
		commandHandler.PrintResult();
	}

	return 0;
}



