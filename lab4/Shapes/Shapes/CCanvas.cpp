#include "CCanvas.h"
#include <string>
#include "Common.h"
#include "../../../external/SDL2_gfx/SDL2_gfxPrimitives.h"

CCanvas::CCanvas()
    : m_window(SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN))
    , m_renderer(SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED))
{
    SDL_RenderClear(m_renderer);
}

CCanvas::~CCanvas()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
    SetColor(lineColor);
    SDL_RenderDrawLineF(m_renderer, from.x, from.y, to.x, to.y);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
    const int pointsNumber = points.size();
    Sint16* xCoords{ new Sint16[pointsNumber] };
    Sint16* yCoords{ new Sint16[pointsNumber] };
    for (int i = 0; i < pointsNumber; i++)
    {
        xCoords[i] = points[i].x;
        yCoords[i] = points[i].y;
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
        topLeft.x,
        topLeft.y,
        width,
        height
    };
    SDL_RenderFillRect(m_renderer, &rect);
}

void CCanvas::Render()
{
    SDL_RenderPresent(m_renderer);
    SDL_Event e;
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
        }
    }
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


