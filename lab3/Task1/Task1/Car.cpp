#include <math.h>
#include "Car.h"

const int REVERSE_GEAR = -1;
const int NEUTRAL_GEAR = 0;
const int FIRST_GEAR = 1;
const int SECOND_GEAR = 2;
const int THIRD_GEAR = 3;
const int FOURTH_GEAR = 4;
const int FIFTH_GEAR = 5;

//спр€тать в cpp (»справлено) %%%


//TODO: speed Speed: 858993460 Gear: -858993460 is not normal (fixed)
bool Car::IsInRange(int value, Range range) const
{
	return value >= range.min && value <= range.max;
}

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

Direction Car::GetDirection() const
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

int Car::GetSpeed() const
{
	return abs(m_speed);
}

int Car::GetGear() const
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
	if (m_speed == 0 && m_gear == NEUTRAL_GEAR)
	{
		m_isTurnedOn = false;
		return true;
	}
	return false;
}

std::optional<Car::Range> Car::GetGearSpeedRange(int gear) const
{
	switch (gear)
	{
	case REVERSE_GEAR://TODO: use const to gear (fixed)
		return REVERSE_GEAR_SPEED_RANGE;
	case NEUTRAL_GEAR:
		return CAR_SPEED_RANGE;
	case FIRST_GEAR:
		return FIRST_GEAR_SPEED_RANGE;
	case SECOND_GEAR:
		return SECOND_GEAR_SPEED_RANGE;
	case THIRD_GEAR:
		return THIRD_GEAR_SPEED_RANGE;
	case FOURTH_GEAR:
		return FOURTH_GEAR_SPEED_RANGE;
	case FIFTH_GEAR:
		return FIFTH_GEAR_SPEED_RANGE;
	default:
		return std::nullopt;
	}
}

bool Car::IsCarDirectionAllowsSetGear(int gear) const
{
	const Direction direction = Car::GetDirection();
	if (gear >= FIRST_GEAR)
	{
		return direction != Direction::Backward;
	} 
	if (gear == REVERSE_GEAR)
	{
		return direction == Direction::StandingStill;
	} 
	//TODO: сосредоточить проверку сущностей в разных методах(fixed)

	return true;
}

bool Car::SetGear(int gear)
{//упростить код (»справлено)
	if (gear == m_gear)
	{
		return true;
	}
	std::optional gearSpeedRange = GetGearSpeedRange(gear);
	if (!gearSpeedRange.has_value())
	{
		return false;
	}
	if (!IsInRange(m_speed, gearSpeedRange.value())) //TODO: сделать преждевременный выход из ф-ии при ошибке (fixed)
	{
		return false;
	}
	if (!IsCarDirectionAllowsSetGear(gear))
	{
		return false;
	}
	if (!m_isTurnedOn)
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	std::optional gearSpeedRange = GetGearSpeedRange(m_gear);
	if (!gearSpeedRange.has_value())
	{
		return false;
	}
	if (!m_isTurnedOn or !IsInRange(speed, gearSpeedRange.value()))
	{
		return false;
	}
	if (m_gear == NEUTRAL_GEAR && speed > abs(m_speed))
	{
		return false;
	}
	//TODO: упростить условие, чтобы speed : -speed выполн€лось один раз (fixed)
	bool isCarWillMoveBackward = m_gear == REVERSE_GEAR || GetDirection() == Direction::Backward;
	m_speed = isCarWillMoveBackward ? -speed : speed;

	return true;
}