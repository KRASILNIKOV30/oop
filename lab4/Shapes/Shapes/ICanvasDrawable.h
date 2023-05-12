#pragma once
#include "ICanvas.h"

class ICanvasDrawable
{
	virtual void Draw(ICanvas& canvas) = 0;
	virtual ~ICanvasDrawable() = default;
};
