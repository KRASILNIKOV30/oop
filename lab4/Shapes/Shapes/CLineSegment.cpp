#include "CLineSegment.h"
#include <cmath>
#include <format>
#include "Common.h"

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t color)
    : Shape(color)
    , m_startPoint(startPoint)
    , m_endPoint(endPoint)
{
}

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

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

double CLineSegment::GetArea() const
{
    return 0;
}

double CLineSegment::GetPerimeter() const
{
    return GetLineLength(m_startPoint, m_endPoint);
}
