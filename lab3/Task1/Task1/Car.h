#pragma once
#include <optional>

enum class Direction
{
	Forward,
	Backward,
	StandingStill
};



//������� ����� � .h (����������)
//������ ������, �� ���������� ��������� ������ ���� ������������ (����������) %%%
class Car
{
public:
	//const �� ����� � ������� get (����������) %%%
	bool IsTurnedOn() const;
	int GetSpeed() const;
	int GetGear() const;
	Direction GetDirection() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	struct Range //��������� � private (����������) %%%
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

	//���������� �� direction, ������� �������� �� ������ (����������)
	bool IsInRange(int value, Range range) const;//�� ��������� optional (����������) %%%
	bool IsCarDirectionAllowsSetGear(int gear) const;
	std::optional<Range> GetGearSpeedRange(int gear) const;

	// m_ (����������)
	bool m_isTurnedOn = false;
	int m_speed = 0;
	int m_gear = 0;

};
