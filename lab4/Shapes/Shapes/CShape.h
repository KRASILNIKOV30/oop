#pragma once
#include "IShape.h"
class CShape : public IShape
{
public:
	CShape(uint32_t outlineColor)
		:m_outlineColor(outlineColor)
	{}
	uint32_t GetOutlineColor() const override { return m_outlineColor; }
	//Не ставить ; после тела метода, убрать виртуальные деструкторы у наследников (Исправлено)

private:
	uint32_t m_outlineColor;
};

