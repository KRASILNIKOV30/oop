#include "CCanvas.h"
#include <string>
#include "Common.h"
#include "../../../external/SDL2_gfx/SDL2_gfxPrimitives.h"

CCanvas::CCanvas(SDL_Window* window)
     //принимать window (исправлено)
    : m_renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
{
    SDL_RenderClear(m_renderer);
}

CCanvas::~CCanvas()
{
    if (m_renderer != nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
    }
    
}

CCanvas::CCanvas(CCanvas&& canvas)
    :m_renderer(std::move(canvas.m_renderer))
{
    canvas.m_renderer = nullptr;
}

CCanvas& CCanvas::operator=(CCanvas&& rhs)
{
    m_renderer = std::move(rhs.m_renderer);
    rhs.m_renderer = nullptr;
    return *this;
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
    SetColor(lineColor);
    SDL_RenderDrawLineF(m_renderer, (float)from.x, (float)from.y, (float)to.x, (float)to.y);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
    const int pointsNumber = (int)points.size();
    Sint16* xCoords{ new Sint16[pointsNumber] };
    Sint16* yCoords{ new Sint16[pointsNumber] };
    for (int i = 0; i < pointsNumber; i++)
    {
        xCoords[i] = (Sint16)points[i].x;
        yCoords[i] = (Sint16)points[i].y;
    }
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    ParseColor(fillColor, red, green, blue);
    filledPolygonRGBA(m_renderer, xCoords, yCoords, pointsNumber, red, green, blue, 0xff);
    delete[] xCoords;
    delete[] yCoords;
}

void CCanvas::FillRect(CPoint topLeft, double width, double height, uint32_t fillColor)
{
    SetColor(fillColor);
    SDL_Rect rect
    {
        (int)topLeft.x,
        (int)topLeft.y,
        (int)width,
        (int)height
    };
    SDL_RenderFillRect(m_renderer, &rect);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    ParseColor(fillColor, red, green, blue);
    filledEllipseRGBA(m_renderer, (Sint16)center.x, (Sint16)center.y, (Sint16)radius, (Sint16)radius, red, green, blue, 0xff);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    ParseColor(lineColor, red, green, blue);
    aaellipseRGBA(m_renderer, (Sint16)center.x, (Sint16)center.y, (Sint16)radius, (Sint16)radius, red, green, blue, 0xff);
}

void CCanvas::Render()
{
    SDL_RenderPresent(m_renderer);
}

void CCanvas::ParseColor(uint32_t color, uint32_t& red, uint32_t& green, uint32_t& blue)
{
    std::string colorStr = GetHexStrFromUint32(color, COLOR_LEN);
    std::string redStr = colorStr.substr(0, 2);
    std::string greenStr = colorStr.substr(2, 2);
    std::string blueStr = colorStr.substr(4, 2);
    StringToUint32(redStr, red);
    StringToUint32(greenStr, green);
    StringToUint32(blueStr, blue);
}

void CCanvas::SetColor(uint32_t color)
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    ParseColor(color, red, green, blue);
    SDL_SetRenderDrawColor(m_renderer, red, green, blue, 0xFF);
}


