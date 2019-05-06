#include "System/TermScreen.h"
#include "System/KbInput.h"

#include "Model/Personaj.h"
#include "Model/Stone.h"
#include "Model/Mover.h"

namespace MyGame
{
	class Settings
	{
	public:
		char upKey;
		char downKey;
		char leftKey;
		char rightKey;
		char layBombKey;
	};
}

int main()
{
	const int maxX = 80;
	const int maxY = 30;

	MyGame::TerminalScreen s;

	MyGame::Personaj personaj;
	MyGame::Rectangle arena(maxX, maxY);

	std::vector<MyGame::Stone> mStones(5);

	mStones.push_back(MyGame::Stone(36, 13, 8, 4));
	mStones.push_back(MyGame::Stone(13, 4, 9, 5));
	mStones.push_back(MyGame::Stone(54, 6, 3, 3));
	mStones.push_back(MyGame::Stone(9, 20, 12, 8));
	mStones.push_back(MyGame::Stone(40, 19, 20, 2));

	personaj.SetX(70);
	personaj.SetY(25);

	MyGame::Mover mover(personaj, arena, mStones);

	while (1)
	{
		//rendering
		s.Clear();
		s.Draw(arena, 0, 0);
		for (const MyGame::Stone & stone : mStones)
			s.Draw(stone.GetShape(), stone.GetX(), stone.GetY());

		s.Draw(personaj.GetShape(), personaj.GetX(), personaj.GetY());

		//input handling
		char input = _getch();

		switch (input)
		{
		case 'w':
			mover.MoveUp();
			break;
		case 'a':
			mover.MoveLeft();
			break;
		case 's':
			mover.MoveDown();
			break;
		case 'd':
			mover.MoveRight();
			break;
		case 'q':
			s.Clear();
			return 0;
		default:
			break;
		}
	}
}

