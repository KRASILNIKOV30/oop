#include "CRectangle.h"
#include <format>
#include "Common.h"

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
	return std::format("rectangle {} {} {} {} {} {}", 
		m_leftTop.x,
		m_leftTop.y,
		m_width,
		m_height,
		GetHexStrFromUint32(m_fillColor, COLOR_LEN),
		GetHexStrFromUint32(m_outlineColor, COLOR_LEN)
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
