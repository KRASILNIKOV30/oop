#include "CLineSegment.h"
#include <cmath>
#include <format>

std::string CLineSegment::ToString() const
{
    return std::format("line {} {} {} {} {}", m_startPoint.x, m_startPoint.y, m_endPoint.x, m_endPoint.y, GetOutlineColor());
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_color;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t color)
    : m_startPoint(startPoint)
    , m_endPoint(endPoint)
    , m_color(color)
{
}

double CLineSegment::GetArea() const
{
    return 0;
}

double CLineSegment::GetPerimeter() const
{
    return std::sqrt(std::pow(m_endPoint.x - m_startPoint.x, 2) + std::pow(m_endPoint.y - m_startPoint.y, 2));
}
