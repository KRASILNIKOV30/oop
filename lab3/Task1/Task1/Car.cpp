#include <math.h>
#include "Car.h"

const bool Car::IsInRange(int speed, std::optional<Range> range)
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

const std::optional<Range> Car::GetGearSpeedRange(int gear)
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

const bool Car::IsCarMovementAllowsSetGear(int gear)
{
	const Direction direction = Car::GetDirection();
	if (gear == 1)
	{
		return direction == Direction::Forward || direction == Direction::StandingStill;
	} 
	if (gear == -1)
	{
		return m_speed == 0;
	} 

	return true;
}

bool Car::SetGear(int gear)
{//упростить код (Исправлено)
	std::optional speedRange = GetGearSpeedRange(gear);
	bool isSpeedInGearRange = IsInRange(m_speed, speedRange);
	bool isCarMovementAllowsSetGear = IsCarMovementAllowsSetGear(gear);
	if ((m_isTurnedOn || gear == 0) && isSpeedInGearRange && isCarMovementAllowsSetGear)
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isTurnedOn or !IsInRange(speed, GetGearSpeedRange(m_gear)))
	{
		return false;
	}
	if (m_gear == 0)
	{
		if (speed <= abs(m_speed))
		{
			m_speed = m_speed > 0 ? speed : -speed;
			return true;
		}
		return false;
	}
	m_speed = m_gear == -1 ? -speed : speed;

	return true;
}