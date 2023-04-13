#include "../../../external/catch2/catch.hpp"
#include "../Task1/Car.h"

namespace
{
	Car car;
}

struct Fixture
{
	Car car;
	Fixture()
	{
		car.TurnOnEngine();
	}
};

TEST_CASE_METHOD(Fixture, "Some method")
{
	CHECK(car.IsTurnedOn());
}


SCENARIO("Car behavior on reverse gear")
{
	GIVEN("Car moving on reverse gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(20);

		WHEN("switching on neutral gear")
		{
			car.SetGear(0);

			THEN("car is moving on the same speed")
			{
				CHECK(car.GetSpeed() == 20);

				AND_WHEN("fail to set forward gear")
				{
					CHECK(!car.SetGear(1));

					THEN("continues moving on neutral")
					{
						CHECK(car.GetSpeed() == 20);
						CHECK(car.GetGear() == 0);
						CHECK(car.GetDirection() == Direction::Backward);
					}
				}

				AND_WHEN("fail to select reverse gear")
				{
					CHECK(!car.SetGear(-1));

					THEN("continues moving on neutral")
					{
						CHECK(car.GetSpeed() == 20);
						CHECK(car.GetGear() == 0);
						CHECK(car.GetDirection() == Direction::Backward);
					}
				}
				
			}

		}
	}

}

TEST_CASE("Изначально машина не заведена и на нейтральной скорости")
{
	REQUIRE(!car.IsTurnedOn());
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetDirection() == Direction::StandingStill);
}

TEST_CASE("Нельзя поменять скорость или переключить передачу, если двигатель не заведен")
{
	REQUIRE(!car.SetSpeed(1));
	REQUIRE(!car.SetGear(1));
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
}

TEST_CASE("Можно завести двигатель")
{
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.IsTurnedOn());
}

TEST_CASE("Нельзя разогнаться на нейтральной передаче")
{
	REQUIRE(!car.SetSpeed(1));
	REQUIRE(!car.SetSpeed(151));
	REQUIRE(car.GetSpeed() == 0);
}

TEST_CASE("На первой передаче можно разогнаться, но только до определенной скорости")
{
	REQUIRE(car.SetGear(1));
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.SetSpeed(30));
	REQUIRE(!car.SetSpeed(31));
	REQUIRE(car.GetSpeed() == 30);
	REQUIRE(car.GetDirection() == Direction::Forward);
}

TEST_CASE("С первой 1 нельзя переключиться на 4 и 5")
{
	REQUIRE(!car.SetGear(4));
	REQUIRE(!car.SetGear(5));
	REQUIRE(car.GetGear() == 1);
}

TEST_CASE("Машина может разогнаться до своей максимальной скорости")
{
	REQUIRE(car.SetGear(2));
	REQUIRE(car.GetGear() == 2);
	REQUIRE(car.SetSpeed(50));

	REQUIRE(car.SetGear(3));
	REQUIRE(car.GetGear() == 3);
	REQUIRE(car.SetSpeed(60));

	REQUIRE(car.SetGear(4));
	REQUIRE(car.GetGear() == 4);
	REQUIRE(car.SetSpeed(90));

	REQUIRE(car.SetGear(5));
	REQUIRE(car.GetGear() == 5);
	REQUIRE(car.SetSpeed(150));
	REQUIRE(car.GetSpeed() == 150);
}

TEST_CASE("На скорости можно переключится на нейтральную передачу и сбросить скорость")
{
	REQUIRE(car.SetGear(0));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 150);
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
}

TEST_CASE("Во время движения вперед нельзя включить задний ход")
{
	REQUIRE(car.GetDirection() == Direction::Forward);
	REQUIRE(!car.SetGear(-1));
	REQUIRE(car.GetGear() == 0);
}

TEST_CASE("Задний ход можно включить на нулевой скорости")
{
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.GetDirection() == Direction::StandingStill);
}

TEST_CASE("Машина может ехать назад")
{
	REQUIRE(car.SetSpeed(20));
	REQUIRE(!car.SetSpeed(21));
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetDirection() == Direction::Backward);
}

TEST_CASE("С задней передачи можно переключиться только на нейтральную")
{
	REQUIRE(!car.SetGear(1));
	REQUIRE(!car.SetGear(2));
	//Проверять, дествительно ли не изменилась передача
	REQUIRE(car.SetGear(0));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetDirection() == Direction::Backward);
}

TEST_CASE("Если замедлиться на нейтральной передаче, то машина продолжает ехать назад")
{
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetDirection() == Direction::Backward);
}

TEST_CASE("В движении нельзя снова переключиться на заднюю передачу")
{
	REQUIRE(!car.SetGear(-1));
}

TEST_CASE("Двигатель можно выключить только при нулевой скорости на нейтральной передаче")
{
	REQUIRE(!car.TurnOffEngine());
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.SetGear(1));
	REQUIRE(!car.TurnOffEngine());
	REQUIRE(car.SetGear(0));
	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsTurnedOn());
}

TEST_CASE("При выключенном двигателе можно переключиться только на нейтральную передачу")
{
	REQUIRE(!car.SetGear(1));
	REQUIRE(car.SetGear(0));
	REQUIRE(car.GetDirection() == Direction::StandingStill);
}
