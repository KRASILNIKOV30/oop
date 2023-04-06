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

//вынести класс в .h
//методы класса, не изменяющие состояние должны быть константными
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
	// m_
	bool isTurnedOn = false;
	Direction direction = Direction::StandingStill;
	int speed = 0;
	//избавиться от direction, хранить скорость со знаком
	int gear = 0;
	bool IsSpeedInRange(Range range);
	bool TryToSetGear(int gear, Range speedRange, Direction availableDirection);
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

bool Car::TryToSetGear(int newGear, Range speedRange, Direction availableDirection)
{
	if (direction == availableDirection && IsSpeedInRange(speedRange))
	{
		gear = newGear;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{//упростить код
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
			return false;
		}
		else
		{
			return TryToSetGear(1, FIRST_GEAR_SPEED_RANGE, Direction::Forward);
		}
	case 2:
		return TryToSetGear(2, SECOND_GEAR_SPEED_RANGE, Direction::Forward);
	case 3:
		return TryToSetGear(3, THIRD_GEAR_SPEED_RANGE, Direction::Forward);
	case 4:
		return TryToSetGear(4, FOURTH_GEAR_SPEED_RANGE, Direction::Forward);
	case 5:
		return TryToSetGear(5, FIFTH_GEAR_SPEED_RANGE, Direction::Forward);
	}
}

