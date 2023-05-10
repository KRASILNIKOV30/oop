#include "CTriangle.h"
#include <format>
#include "Common.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor)
    : m_vertex1(vertex1)
    , m_vertex2(vertex2)
    , m_vertex3(vertex3)
    , m_fillColor(fillColor)
    , m_outlineColor(outlineColor)
{
}

double CTriangle::GetArea() const
{
    double a = GetLineLength(m_vertex1, m_vertex2);
    double b = GetLineLength(m_vertex2, m_vertex3);
    double c = GetLineLength(m_vertex3, m_vertex1);
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
    double edge1 = GetLineLength(m_vertex1, m_vertex2);
    double edge2 = GetLineLength(m_vertex2, m_vertex3);
    double edge3 = GetLineLength(m_vertex3, m_vertex1);
    return edge1 + edge2 + edge3;
}

std::string CTriangle::ToString() const
{
    return std::format("triangle {} {} {} {} {} {} {} {}",
        m_vertex1.x,
        m_vertex1.y,
        m_vertex2.x,
        m_vertex2.y,
        m_vertex3.x,
        m_vertex3.y,
        GetHexStrFromUint32(m_fillColor, COLOR_LEN),
        GetHexStrFromUint32(m_outlineColor, COLOR_LEN)
    );
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
    return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
    return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
    return m_vertex3;
}
