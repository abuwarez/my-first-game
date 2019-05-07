#include "System/TermScreen.h"
#include "System/KbInput.h"

#include "Model/Personaj.h"
#include "Model/Stone.h"
#include "Model/Mover.h"

#include <unistd.h>
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


	class Animation
	{
		public:
			virtual void Update(int elapsedMillis) = 0;//elapsed (delta) millis since last update
			virtual void Reset() = 0;
			virtual bool IsFinished() const = 0;
			virtual ~Animation() {}
	};


	class StoneMover : public Animation
	{
		int mVelocityX; // pixels (terminal chars) per second
		int mMaxX;

		Stone & mStone;
		int mElapsedTime;
		int mInitialX;

		public:
			StoneMover(int vX, int maxX, Stone & stone) : mVelocityX(vX), mStone(stone), mElapsedTime(0), mInitialX(mStone.GetX()), mMaxX(maxX) {}

			virtual void Update(int elapsedMillis) 
			{
				mElapsedTime += elapsedMillis;

				mStone.SetX(mInitialX + mVelocityX * mElapsedTime / 1000);

			}

			virtual void Reset()
			{
				mElapsedTime = 0;
				mInitialX = mStone.GetX();
			}

			virtual bool IsFinished() const
			{
				return mStone.GetX() == mMaxX;
			}
	};

	class AnimationChain : public Animation
	{
		std::vector<Animation*> mAnimations;
		int mActiveAnimIndex;

		public:
			AnimationChain() : mActiveAnimIndex(0) {}
			
			void AddAnimation(Animation* a)
			{
				mAnimations.push_back(a);
			}

			virtual void Update(int elapsedMillis)
			{
				Animation * activeAnim = mAnimations[mActiveAnimIndex];
				if (!activeAnim->IsFinished())
					activeAnim->Update(elapsedMillis);
				else
				{
					mActiveAnimIndex = (mActiveAnimIndex + 1) % mAnimations.size();
					Animation * activeAnim = mAnimations[mActiveAnimIndex];
					activeAnim->Reset();
					activeAnim->Update(elapsedMillis);
				}
			}

			virtual bool IsFinished() const
			{
				return false;
			}

			virtual void Reset()
			{
				mActiveAnimIndex = 0;
				Animation * activeAnim = mAnimations[mActiveAnimIndex];
				activeAnim->Reset();
			}
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
		
		_getch(input);

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

