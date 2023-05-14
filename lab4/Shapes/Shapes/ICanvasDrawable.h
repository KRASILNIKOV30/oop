#pragma once
#include "CCanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) = 0;
	virtual ~ICanvasDrawable() = default;
};
