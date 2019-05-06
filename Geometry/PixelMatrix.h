#pragma once

namespace MyGame
{
	using Pixel = char;

	class PixelMatrix
	{
		int width, height;
		Pixel pixels[100][100];

	public:
		int GetWidth() const { return width; }
		int GetHeight() const { return height; }
		Pixel GetPixelAt(int x, int y) const { return pixels[x][y]; }

		void SetWidth(int w) { width = w; }
		void SetHeight(int h) { height = h; }
		void SetPixelAt(int x, int y, Pixel p) { pixels[x][y] = p; }
	};
}
