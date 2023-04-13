#include "../../../external/catch2/catch.hpp"
#include "../Task1/Car.h"

namespace
{
	Car car;
}

TEST_CASE("")
{
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
	REQUIRE(!car.SetSpeed(CAR_SPEED_RANGE.max + 1));
	REQUIRE(car.GetSpeed() == 0);
}

TEST_CASE("На первой передаче можно разогнаться, но только до определенной скорости")
{
	REQUIRE(car.SetGear(1));
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.SetSpeed(FIRST_GEAR_SPEED_RANGE.max));
	REQUIRE(!car.SetSpeed(FIRST_GEAR_SPEED_RANGE.max + 1));
	REQUIRE(car.GetSpeed() == FIRST_GEAR_SPEED_RANGE.max);
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
	REQUIRE(car.SetSpeed(SECOND_GEAR_SPEED_RANGE.max));

	REQUIRE(car.SetGear(3));
	REQUIRE(car.GetGear() == 3);
	REQUIRE(car.SetSpeed(THIRD_GEAR_SPEED_RANGE.max));

	REQUIRE(car.SetGear(4));
	REQUIRE(car.GetGear() == 4);
	REQUIRE(car.SetSpeed(FOURTH_GEAR_SPEED_RANGE.max));

	REQUIRE(car.SetGear(5));
	REQUIRE(car.GetGear() == 5);
	REQUIRE(car.SetSpeed(FIFTH_GEAR_SPEED_RANGE.max));
	REQUIRE(car.GetSpeed() == CAR_SPEED_RANGE.max);
}

TEST_CASE("На скорости можно переключится на нейтральную передачу и сбросить скорость")
{
	REQUIRE(car.SetGear(0));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == CAR_SPEED_RANGE.max);
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
	REQUIRE(car.SetGear(0));
	REQUIRE(car.GetGear() == 0);
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
