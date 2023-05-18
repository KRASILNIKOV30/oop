#include <iostream>
#include "CommandHandler.h"
#undef main

int main()
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;
	CommandHandler commandHandler(std::cin, std::cout);
	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!commandHandler.HandleCommand())
		{
			if (std::cin.eof())
			{
				commandHandler.PrintResult();
				commandHandler.DrawShapes(window);
			}
			else
			{
				std::cout << "Error!" << std::endl;
			}
		}
	}

	SDL_Event e;
	while (true)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				SDL_DestroyWindow(window);
				SDL_Quit();
			}
		}
	}
	
	return 0;
}



