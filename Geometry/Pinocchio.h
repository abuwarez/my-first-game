#pragma once

#include "Shape.h"
#include "PixelMatrix.h"

namespace MyGame
{
	class PinocchioLeft : public Shape
	{
	public:
		virtual void FillPixels(PixelMatrix & output) const override
		{
			output.SetPixelAt(0, 0, '-');
			output.SetPixelAt(1, 0, 'O');
			output.SetPixelAt(2, 0, ' ');
			output.SetPixelAt(0, 1, '/');
			output.SetPixelAt(1, 1, '|');
			output.SetPixelAt(2, 1, '/');
			output.SetPixelAt(0, 2, '/');
			output.SetPixelAt(1, 2, ' ');
			output.SetPixelAt(2, 2, '\\');

			output.SetHeight(3);
			output.SetWidth(3);
		}

		virtual int GetWidth() const override
		{
			return 3;
		}

		virtual int GetHeight() const override
		{
			return 3;
		}
	};

	class PinocchioRight : public Shape
	{
	public:
		virtual void FillPixels(PixelMatrix & output) const override
		{
			output.SetPixelAt(0, 0, ' ');
			output.SetPixelAt(1, 0, 'O');
			output.SetPixelAt(2, 0, '-');
			output.SetPixelAt(0, 1, '\\');
			output.SetPixelAt(1, 1, '|');
			output.SetPixelAt(2, 1, '\\');
			output.SetPixelAt(0, 2, '/');
			output.SetPixelAt(1, 2, ' ');
			output.SetPixelAt(2, 2, '\\');

			output.SetHeight(3);
			output.SetWidth(3);
		}

		virtual int GetWidth() const override
		{
			return 3;
		}

		virtual int GetHeight() const override
		{
			return 3;
		}
	};
}