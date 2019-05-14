#include "System/TermScreen.h"
#include "System/KbInput.h"
#include "System/System.h"

#include "Model/Personaj.h"
#include "Model/Stone.h"
#include "Model/Mover.h"
#include "Model/StoneMover.h"

#include <ostream>
#include <iostream>

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

	std::vector<MyGame::Stone> mStones;
	mStones.reserve(5);

	mStones.push_back(MyGame::Stone(36, 13, 8, 4));
	mStones.push_back(MyGame::Stone(13, 4, 9, 5));
	mStones.push_back(MyGame::Stone(54, 6, 3, 3));
	mStones.push_back(MyGame::Stone(9, 20, 12, 8));
	mStones.push_back(MyGame::Stone(40, 19, 20, 2));

	MyGame::StoneMover stoneMoverRight(7, 72, mStones.front());
	MyGame::StoneMover stoneMoverLeft(-7, 0, mStones.front());

	MyGame::AnimationChain stoneAnimChain;
	stoneAnimChain.AddAnimation(&stoneMoverRight);
	stoneAnimChain.AddAnimation(&stoneMoverLeft);

	personaj.SetX(70);
	personaj.SetY(13);

	MyGame::Mover mover(personaj, arena, mStones);

	int frameDurationMillis = 50;

	std::vector<MyGame::Animation*> animations;
	animations.push_back(&stoneAnimChain);

	while (1)
	{
		//rendering
		s.Clear();
		s.Draw(arena, 0, 0);
		for (const MyGame::Stone & stone : mStones)
			s.Draw(stone.GetShape(), stone.GetX(), stone.GetY());

		s.Draw(personaj.GetShape(), personaj.GetX(), personaj.GetY());

		std::cout << std::flush;

		for (MyGame::Animation * anim : animations)
			anim->Update(frameDurationMillis);

		//input handling
		char input = 0;
		
		if (!_getch_non_blocking(input))
			continue;

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

		usleep(frameDurationMillis * 1000);
	}
}

