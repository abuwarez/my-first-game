#pragma once

#if defined(_WIN32) || defined(_WIN64)

#include <conio.h>

bool _getch_non_blocking(char & out)
{
	if (_kbhit())
	{
		out = _getch();
		return true;
	}

	return false;
}

#else

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

bool _getch_non_blocking(char & out)
{
	char buf = 0;
	struct termios old = { 0 };
	fflush(stdout);
	if (tcgetattr(0, &old) < 0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 0;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");
	int readVal = read(0, &buf, 1);
	if (readVal < 0)
		perror("read()");
	else if (readVal > 0)
	{
		out = buf;
	}

	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror("tcsetattr ~ICANON");
	//printf("%c\n",buf);
	return readVal > 0;
}

#endif
