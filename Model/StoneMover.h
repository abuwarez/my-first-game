#pragma once

#include "Animation/Animation.h"

namespace MyGame
{
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
}