#include "Car.h"
#include <iostream>	
#include <sstream>

namespace
{//Именование в PascalCase (Исправлено) %%% 
	//Метод ToString (Исправлено) %%%
	std::string ToString(Direction direction)
	{
		switch (direction)
		{
		case Direction::Forward:
			return "forward";
		case Direction::Backward:
			return "backward";
		case Direction::StandingStill:
			return "standing still";
		default:
			return "";
		}
	}

	void WriteCarInfo(Car& car)
	{
		std::cout << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << std::endl;
		std::cout << "Direction: " << ToString(car.GetDirection()) << std::endl;
		std::cout << "Speed: " << car.GetSpeed() << std::endl;
		std::cout << "Gear: " << car.GetGear() << std::endl;
	}

	//Убрать const из параметров методов (Исправлено)
	void TurnOnEngineErrorHandling(bool wasTurnedOnSuccessfully)
	{
		if (wasTurnedOnSuccessfully)
		{
			std::cout << "Engine turned on" << std::endl;
		}
		else
		{
			std::cout << "Unable to turn on engine" << std::endl;
		}
	}

	void TurnOffEngineErrorHandling(bool wasTurnedOffSuccessfully)
	{
		if (wasTurnedOffSuccessfully)
		{
			std::cout << "Engine turned off" << std::endl;
		}
		else
		{
			std::cout << "Unable to turn off engine" << std::endl;
		}
	}

	void SetGearErrorHandling(bool wasSettedSuccessfully)
	{
		if (wasSettedSuccessfully)
		{
			std::cout << "Gear set" << std::endl;
		}
		else
		{
			std::cout << "Unable to set gear" << std::endl;
		}
	}

	void SetSpeedErrorHandling(bool wasSettedSuccessfully)
	{
		if (wasSettedSuccessfully)
		{
			std::cout << "Speed set" << std::endl;
		}
		else
		{
			std::cout << "Unable to set speed" << std::endl;
		}
	}
}

int main()
{
	Car car;
	std::string command;

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		std::cin >> command;
		if (command == "Info")
		{
			WriteCarInfo(car);
		}
		else if (command == "EngineOn")
		{
			TurnOnEngineErrorHandling(car.TurnOnEngine());
		}
		else if (command == "EngineOff")
		{
			TurnOffEngineErrorHandling(car.TurnOffEngine());
		}
		else if (command == "SetGear")
		{
			int gear;
			std::cin >> gear;
			SetGearErrorHandling(car.SetGear(gear));
		}
		else if (command == "SetSpeed")
		{
			int speed;
			std::cin >> speed;
			SetSpeedErrorHandling(car.SetSpeed(speed));
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
		}
	}
	return 0;
}


