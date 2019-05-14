#pragma once

#include <vector>

namespace MyGame
{
	class Animation
	{
	public:
		virtual void Update(int elapsedMillis) = 0;//elapsed (delta) millis since last update
		virtual void Reset() = 0;
		virtual bool IsFinished() const = 0;
		virtual ~Animation() {}
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