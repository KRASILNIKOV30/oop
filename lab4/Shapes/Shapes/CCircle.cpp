#include "CCircle.h"
#include "Common.h"
#include <format>

CCircle::CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor)
    : ISolidShape(fillColor, outlineColor)
    , m_center(center)
    , m_radius(radius)
    , m_outlineColor(outlineColor)
{
}

double CCircle::GetArea() const
{
    return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * PI * m_radius;
}

std::string CCircle::ToString() const
{
    return std::format("circle {} {} {} {} {}",
        m_center.x,
        m_center.y,
        m_radius,
        GetHexStrFromUint32(GetFillColor(), COLOR_LEN),
        GetHexStrFromUint32(m_outlineColor, COLOR_LEN)
    );
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}
