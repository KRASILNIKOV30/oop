#include "CRectangle.h"
#include <format>

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

std::string CRectangle::ToString() const
{
	return std::format("rectangle {} {} {} {} {} {}\n", 
		m_leftTop.x,
		m_leftTop.y,
		m_width,
		m_height,
		m_fillColor,
		m_outlineColor
	);
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint({m_leftTop.x + m_width, m_leftTop.y + m_height});
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
