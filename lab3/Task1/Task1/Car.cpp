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


class Car
{
public:
	bool IsTurnedOn();
	Direction GetDirection();
	int GetSpeed();
	int GetGear();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool isTurnedOn = false;
	Direction direction = Direction::StandingStill;
	int speed = 0;
	int gear = 0;
	bool IsSpeedInRange(Range range);
};

bool Car::IsSpeedInRange(Range range)
{
	return speed >= range.min && speed <= range.max;
}

bool Car::IsTurnedOn()
{
	return isTurnedOn;
}

Direction Car::GetDirection()
{
	return direction;
}

int Car::GetSpeed()
{
	return speed;
}

int Car::GetGear()
{
	return gear;
}

bool Car::TurnOnEngine()
{
	isTurnedOn = true;
	return isTurnedOn;
}

bool Car::TurnOffEngine()
{
	if (speed == 0 && gear == 0)
	{
		isTurnedOn = false;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{
	if (!isTurnedOn)
	{
		return false;
	}
	switch (gear)
	{
	case -1:
		if (speed == 0)
		{
			gear = -1;
			return true;
		}
		return false;
	case 0:
		gear = 0;
	case 1:
		if (direction == Direction::Backward)
		{
			if (speed == 0)
			{
				gear = 1;
				return true;
			}
		}
		else
		{
			if (IsSpeedInRange(FIFTH_GEAR_SPEED_RANGE))
			{
				gear = 1;
				return true;
			}
		}
		return false;
	case 2:
		if (direction == Direction::Forward && IsSpeedInRange(SECOND_GEAR_SPEED_RANGE))
		{
			gear = 2;
			return true;
		}
		return false;
	case 3:
		if (direction == Direction::Forward && IsSpeedInRange(THIRD_GEAR_SPEED_RANGE))
		{
			gear = 2;
			return true;
		}
		return false;
	case 4:
		if (direction == Direction::Forward && IsSpeedInRange(FOURTH_GEAR_SPEED_RANGE))
		{
			gear = 2;
			return true;
		}
		return false;
	case 5:
		if (direction == Direction::Forward && IsSpeedInRange(FIFTH_GEAR_SPEED_RANGE))
		{
			gear = 2;
			return true;
		}
		return false;
	}
}

