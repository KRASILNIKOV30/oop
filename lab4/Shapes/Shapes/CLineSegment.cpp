#include "CLineSegment.h"
#include <cmath>
#include <format>
#include "Common.h"

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
    canvas.DrawLine(m_startPoint, m_endPoint, GetOutlineColor());
}

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t color)
    : CShape(color)
    , m_startPoint(startPoint)
    , m_endPoint(endPoint)
{
}

double CLineSegment::GetArea() const
{
    return 0;
}

double CLineSegment::GetPerimeter() const
{
    return GetLineLength(m_startPoint, m_endPoint);
}

std::string CLineSegment::GetShapeInfo() const
{
    return std::format("line {} {} {} {}",
        m_startPoint.x,
        m_startPoint.y,
        m_endPoint.x,
        m_endPoint.y
    );
}
