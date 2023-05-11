#pragma once
#include "ISolidShape.h"
#include <format>
#include "Common.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape(uint32_t fillColor, uint32_t outlineColor)
		: m_fillColor(fillColor)
		, m_outlineColor(outlineColor)
	{}
	uint32_t GetFillColor() const override { return m_fillColor; }
	uint32_t GetOutlineColor() const override { return m_outlineColor; }
	std::string ToString() const override
	{
		return std::format("{} {} {}",
			GetShapeInfo(),
			GetHexStrFromUint32(GetFillColor(), COLOR_LEN),
			GetHexStrFromUint32(GetOutlineColor(), COLOR_LEN)
		);
	}

private:
	uint32_t m_fillColor, m_outlineColor;
};

