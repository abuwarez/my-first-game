#pragma once

#include "Shape.h"
#include "PixelMatrix.h"

namespace MyGame
{
	class Rectangle : public Shape
	{
		int lungime;
		int latime;

	public:
		Rectangle(int _lungime, int _latime) : lungime(_lungime), latime(_latime) {}

		virtual void FillPixels(PixelMatrix & output) const override
		{
			output.SetWidth(lungime);
			output.SetHeight(latime);
			for (int i = 0; i < lungime; ++i)
			{
				for (int j = 0; j < latime; ++j)
				{
					output.SetPixelAt(i, j, ' ');
				}
			}

			//prima si ultima linie
			for (int i = 0; i < lungime; ++i)
			{
				output.SetPixelAt(i, 0, 'x');
				output.SetPixelAt(i, latime - 1, 'x');
			}

			for (int j = 1; j < latime - 1; ++j) // toate liniile mai putin prima si ultima
			{
				output.SetPixelAt(0, j, 'x');
				output.SetPixelAt(lungime - 1, j, 'x');
			}
		}

		virtual int GetWidth() const override { return lungime; }
		virtual int GetHeight() const override { return latime; }

	};

}