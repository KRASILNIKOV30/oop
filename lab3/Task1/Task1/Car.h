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
	int min;
	int max;
};

const Range REVERSE_GEAR_SPEED_RANGE = { 0, 20 };
const Range FIRST_GEAR_SPEED_RANGE = { 0, 30 };
const Range SECOND_GEAR_SPEED_RANGE = { 20, 50 };
const Range THIRD_GEAR_SPEED_RANGE = { 30, 60 };
const Range FOURTH_GEAR_SPEED_RANGE = { 40, 90 };
const Range FIFTH_GEAR_SPEED_RANGE = { 50, 150 };
const Range CAR_SPEED_RANGE = { -REVERSE_GEAR_SPEED_RANGE.max, FIFTH_GEAR_SPEED_RANGE.max };

//вынести класс в .h
//методы класса, не изменяющие состояние должны быть константными (Исправлено)
class Car
{
public:
	const bool IsTurnedOn();
	const Direction GetDirection();
	const int GetSpeed();
	const int GetGear();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	// m_ (Исправлено)
	bool m_isTurnedOn = false;
	int m_speed = 0;
	//избавиться от direction, хранить скорость со знаком (Исправлено)
	int m_gear = 0;
	const bool m_IsInRange(int speed, std::optional<Range> range);
	bool m_TryToSetGear(int gear, Range speedRange);
	const std::optional<Range> m_GetGearSpeedRange(int gear);
	const bool m_IsCarMovementAllowsSetGear(int gear);
};
