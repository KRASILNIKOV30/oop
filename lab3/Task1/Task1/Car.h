#pragma once
#include <optional>

enum class Direction
{
	Forward,
	Backward,
	StandingStill
};



//вынести класс в .h (Исправлено)
//методы класса, не изменяющие состояние должны быть константными (Исправлено) %%%
class Car
{
public:
	//const не нужен у методов get (Исправлено) %%%
	bool IsTurnedOn() const;
	int GetSpeed() const;
	int GetGear() const;
	Direction GetDirection() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	struct Range //перенести в private (Исправлено) %%%
	{
		int min, max;
	};
	static inline const Range REVERSE_GEAR_SPEED_RANGE = { 0, 20 };
	static inline const Range FIRST_GEAR_SPEED_RANGE = { 0, 30 };
	static inline const Range SECOND_GEAR_SPEED_RANGE = { 20, 50 };
	static inline const Range THIRD_GEAR_SPEED_RANGE = { 30, 60 };
	static inline const Range FOURTH_GEAR_SPEED_RANGE = { 40, 90 };
	static inline const Range FIFTH_GEAR_SPEED_RANGE = { 50, 150 };
	static inline const Range CAR_SPEED_RANGE = { -REVERSE_GEAR_SPEED_RANGE.max, FIFTH_GEAR_SPEED_RANGE.max };

	//избавиться от direction, хранить скорость со знаком (Исправлено)
	bool IsInRange(int value, Range range) const;//Не принимать optional (Исправлено) %%%
	bool IsCarDirectionAllowsSetGear(int gear) const;
	std::optional<Range> GetGearSpeedRange(int gear) const;

	// m_ (Исправлено)
	bool m_isTurnedOn = false;
	int m_speed = 0;
	int m_gear = 0;

};
