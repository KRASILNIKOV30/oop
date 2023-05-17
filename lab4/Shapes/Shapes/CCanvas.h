#pragma once
#include "ICanvas.h"
#include <SDL2/SDL.h>

class CCanvas final : public ICanvas
{
public:
	CCanvas();
	~CCanvas();
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) final;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) final;
	void Render() final;

private:
	void ParseColor(uint32_t color, uint32_t& red, uint32_t& green, uint32_t& blue);
	void SetColor(uint32_t color);

private:
	const int SCREEN_WIDTH = 1040;
	const int SCREEN_HEIGHT = 800;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};

