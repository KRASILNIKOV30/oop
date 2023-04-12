#include <math.h>
#include "Car.h"

const bool Car::m_IsInRange(int speed, std::optional<Range> range)
{
	if (!range.has_value())
	{
		return false;
	}
	return speed >= range.value().min && speed <= range.value().max;
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

const std::optional<Range> Car::m_GetGearSpeedRange(int gear)
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
	default:
		return std::nullopt;
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
{//упростить код (Исправлено)
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
	if (m_gear == 0)
	{
		if (speed <= abs(m_speed))
		{
			m_speed = speed;
			return true;
		}
		return false;
	} 
	if (m_gear == -1)
	{
		m_speed = -speed;
		return true;
	}
	else
	{
		m_speed = speed;
	}
	return true;
}