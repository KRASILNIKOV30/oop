#include "CCircle.h"
#include "Common.h"
#include <format>

CCircle::CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor)
    : CSolidShape(fillColor, outlineColor)
    , m_center(center)
    , m_radius(radius)
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

std::string CCircle::GetShapeInfo() const
{
    return std::format("circle {} {} {}",
        m_center.x,
        m_center.y,
        m_radius
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

void CCircle::Draw(ICanvas& canvas)
{
}
