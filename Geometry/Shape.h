#pragma once

#include "PixelMatrix.h"

namespace MyGame
{
	class Shape
	{
	public:
		virtual void FillPixels(PixelMatrix & output) const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
	};
}