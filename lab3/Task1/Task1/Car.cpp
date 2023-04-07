#include <math.h>
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

const Range REVERSE_GEAR_SPEED_RANGE = { -20, 0 };
const Range FIRST_GEAR_SPEED_RANGE = { 0, 30 };
const Range SECOND_GEAR_SPEED_RANGE = { 20, 50 };
const Range THIRD_GEAR_SPEED_RANGE = { 30, 60 };
const Range FOURTH_GEAR_SPEED_RANGE = { 40, 90 };
const Range FIFTH_GEAR_SPEED_RANGE = { 50, 150 };
const Range CAR_SPEED_RANGE = { REVERSE_GEAR_SPEED_RANGE.min, FIFTH_GEAR_SPEED_RANGE.max };

//вынести класс в .h
//методы класса, не измен€ющие состо€ние должны быть константными (»справлено)
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
	// m_ (»справлено)
	bool m_isTurnedOn = false;
	int m_speed = 0;
	//избавитьс€ от direction, хранить скорость со знаком (»справлено)
	int m_gear = 0;
	bool m_IsInRange(int speed, Range range);
	bool m_TryToSetGear(int gear, Range speedRange);
	const Range m_GetGearSpeedRange(int gear);
};

bool Car::m_IsInRange(int speed, Range range)
{
	return speed >= range.min && speed <= range.max;
}

const bool Car::IsTurnedOn()
{
	return m_isTurnedOn;
}

const Direction Car::GetDirection()
{
	if (m_speed > 0)
	{
		return Direction::Forward;
	}
	if (m_speed < 0)
	{
		return Direction::Backward;
	}
	return Direction::StandingStill;
}

const int Car::GetSpeed()
{
	return abs(m_speed);
}

const int Car::GetGear()
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	m_isTurnedOn = true;
	return m_isTurnedOn;
}

bool Car::TurnOffEngine()
{
	if (m_speed == 0 && m_gear == 0)
	{
		m_isTurnedOn = false;
		return true;
	}
	return false;
}

const Range Car::m_GetGearSpeedRange(int gear)
{
	switch (gear)
	{
	case -1:
		return REVERSE_GEAR_SPEED_RANGE;
	case 0:
		return CAR_SPEED_RANGE;
	case 1:
		return FIRST_GEAR_SPEED_RANGE;
	case 2:
		return SECOND_GEAR_SPEED_RANGE;
	case 3:
		return THIRD_GEAR_SPEED_RANGE;
	case 4:
		return FOURTH_GEAR_SPEED_RANGE;
	case 5:
		return FIFTH_GEAR_SPEED_RANGE;
	}
}

bool Car::m_TryToSetGear(int gear, Range speedRange)
{
	if (m_IsInRange(m_speed, speedRange))
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{//упростить код (»справлено)
	if (m_isTurnedOn && m_IsInRange(m_speed, m_GetGearSpeedRange(gear)))
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isTurnedOn or !m_IsInRange(speed, m_GetGearSpeedRange(m_gear)))
	{
		return false;
	}
	if (m_gear == 0 && speed <= abs(m_speed))
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == -1)
	{
		m_speed = -speed;
		return true;
	}
	return false;
}