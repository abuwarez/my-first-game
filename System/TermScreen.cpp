#include "TermScreen.h"
#include "Geometry/PixelMatrix.h"
#include "Geometry/Shape.h"

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
#include <wincon.h>
#include <ConsoleApi.h>
#endif

#include <iostream>

namespace MyGame
{
	TerminalScreen::TerminalScreen()
	{
#if defined(_WIN32) || defined(_WIN64)
		HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode;

		GetConsoleMode(hOutput, &dwMode);

		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOutput, dwMode);
#endif
	}

	TerminalScreen::~TerminalScreen()
	{
		Clear();
		//show cursor
		std::cout << "\033[?25h";
	}


	void TerminalScreen::MoveCursor(int line, int col)
	{
		// CSI sequence for positioning cursor - https://en.wikipedia.org/wiki/ANSI_escape_code
		std::cout << "\033[" << line << ";" << col << "H";
	}

	void TerminalScreen::Clear()
	{
		// CSI sequence for clear screen - https://en.wikipedia.org/wiki/ANSI_escape_code
		std::cout << "\033[2J\033[1;1H";
		// hide cursor
		std::cout << "\033[?25l";
	}

	void TerminalScreen::Draw(const Shape& s, int x, int y)
	{
		PixelMatrix pixels;

		s.FillPixels(pixels);

		MoveCursor(y + 1, x + 1); // +1 pentru ca randurile si coloanele terminalului incep de la 1

		for (int i = 0; i < pixels.GetHeight(); ++i) //get height -> numarul de linii
		{
			MoveCursor(y + 1 + i, x + 1);

			for (int j = 0; j < pixels.GetWidth(); ++j) //numarul de caractere pe linie
			{
				// scriem o linie din matricea de pixeli
				std::cout << pixels.GetPixelAt(j, i);
			}
		}
	}
}
