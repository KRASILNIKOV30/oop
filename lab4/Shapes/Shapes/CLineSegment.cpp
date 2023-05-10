#include "CLineSegment.h"
#include <cmath>
#include <format>
#include "Common.h"

std::string CLineSegment::ToString() const
{
    return std::format("line {} {} {} {} {}",
        m_startPoint.x,
        m_startPoint.y,
        m_endPoint.x, 
        m_endPoint.y,
        GetHexStrFromUint32(GetOutlineColor(), COLOR_LEN)
    );
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
    return GetLineLength(m_startPoint, m_endPoint);
}
