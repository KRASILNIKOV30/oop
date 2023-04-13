#pragma once
#include <optional>

enum class Direction
{
	Forward,
	Backward,
	StandingStill
};

struct Range
{
	int min, max;
};

const Range REVERSE_GEAR_SPEED_RANGE = { 0, 20 };
const Range FIRST_GEAR_SPEED_RANGE = { 0, 30 };
const Range SECOND_GEAR_SPEED_RANGE = { 20, 50 };
const Range THIRD_GEAR_SPEED_RANGE = { 30, 60 };
const Range FOURTH_GEAR_SPEED_RANGE = { 40, 90 };
const Range FIFTH_GEAR_SPEED_RANGE = { 50, 150 };
const Range CAR_SPEED_RANGE = { -REVERSE_GEAR_SPEED_RANGE.max, FIFTH_GEAR_SPEED_RANGE.max };

//вынести класс в .h (»справлено)
//методы класса, не измен€ющие состо€ние должны быть константными (»справлено)
class Car
{
public:
	const bool IsTurnedOn();
	const int GetSpeed();
	const int GetGear();
	const Direction GetDirection();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	// m_ (»справлено)
	bool m_isTurnedOn = false;
	int m_speed, m_gear;
	//избавитьс€ от direction, хранить скорость со знаком (»справлено)
	const bool IsInRange(int speed, std::optional<Range> range);
	const bool IsCarMovementAllowsSetGear(int gear);
	const std::optional<Range> GetGearSpeedRange(int gear);
};
