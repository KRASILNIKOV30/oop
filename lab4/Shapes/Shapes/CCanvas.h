#pragma once
#include "ICanvas.h"
#include <SDL2/SDL.h>

class CCanvas final : public ICanvas
{
public:
	//Добавить конструктор перемещения, конструктор удаленный копирования (старый объект нельзя будет использовать) 
	CCanvas(SDL_Window* window);
	~CCanvas();
	CCanvas(CCanvas&& canvas);
	//Дописать оператор перемещающего присваивания (cg-course) (Сделано)
	CCanvas& operator=(CCanvas&& rhs);
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) final;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) final;
	void FillRect(CPoint topLeft, double width, double height, uint32_t fillColor) final;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) final;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) final;
	void Render();

private:
	void ParseColor(uint32_t color, uint32_t& red, uint32_t& green, uint32_t& blue);
	void SetColor(uint32_t color);

private:
	SDL_Renderer* m_renderer;
};

