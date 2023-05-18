#include "CRectangle.h"
#include <format>
#include "Common.h"

CRectangle::CRectangle(CPoint leftTop, double width, double height, uint32_t fillColor, uint32_t outlineColor)
	: CSolidShape(fillColor, outlineColor)
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

std::string CRectangle::GetShapeInfo() const
{
	return std::format("rectangle {} {} {} {}", 
		m_leftTop.x,
		m_leftTop.y,
		m_width,
		m_height
		//Паттерн шаблонный метод для утранения дублирования кода (Исправлено)
	);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightTop() const
{
	return CPoint({m_leftTop.x + m_width, m_leftTop.y});
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint({m_leftTop.x + m_width, m_leftTop.y + m_height});
}

CPoint CRectangle::GetLeftBottom() const
{
	return CPoint({ m_leftTop.x, m_leftTop.y + m_height});
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.FillRect(GetLeftTop(), m_width, m_height, GetFillColor());
	canvas.DrawLine(GetLeftTop(), GetRightTop(), GetOutlineColor());
	canvas.DrawLine(GetRightTop(), GetRightBottom(), GetOutlineColor());
	canvas.DrawLine(GetRightBottom(), GetLeftBottom(), GetOutlineColor());
	canvas.DrawLine(GetLeftBottom(), GetLeftTop(), GetOutlineColor());
}
