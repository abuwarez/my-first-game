#pragma once

namespace MyGame
{
	class Shape;

	class TerminalScreen
	{
		void MoveCursor(int line, int col);

	public:
		TerminalScreen();
		~TerminalScreen();

		void Clear();
		void Draw(const Shape& s, int x, int y);
	};
}