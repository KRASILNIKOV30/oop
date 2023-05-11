#pragma once
#include "IShape.h"
#include <format>
#include "Common.h"

class CShape : public IShape
{
public:
	CShape(uint32_t outlineColor)
		:m_outlineColor(outlineColor)
	{}
	uint32_t GetOutlineColor() const override { return m_outlineColor; }
	//Не ставить ; после тела метода, убрать виртуальные деструкторы у наследников (Исправлено)
	std::string ToString() const override
	{
		return std::format("{} {}",
			GetShapeInfo(),
			GetHexStrFromUint32(GetOutlineColor(), COLOR_LEN)
		);
	}

private:
	uint32_t m_outlineColor;
};

