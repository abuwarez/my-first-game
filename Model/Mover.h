#pragma once

#include "System/InputListener.h"
#include "Geometry/Rectangle.h"

#include "Personaj.h"
#include "Stone.h"

#include <vector>

namespace MyGame
{
	class Mover :public InputListener
	{
		Personaj & mPersonaj;
		Rectangle & mArena;
		std::vector<Stone> & mStones;

		bool IsCollitizone(const Shape& s1, int x1, int y1, const Shape& s2, int x2, int y2)
		{
			bool xOverlap = (x1 <= x2) && (x2 - x1 < s1.GetWidth()) || (x2 < x1) && (x1 - x2 < s2.GetWidth());
			bool yOverlap = (y1 <= y2) && (y2 - y1 < s1.GetHeight()) || (y2 < y1) && (y1 - y2 < s2.GetHeight());

			return xOverlap && yOverlap;
		}

		bool IsCollision(int newX, int newY)
		{
			for (const Stone & s : mStones)
				if (IsCollitizone(mPersonaj.GetShape(), newX, newY, s.GetShape(), s.GetX(), s.GetY()))
					return true;

			return false;
		}


	public:
		Mover(Personaj & personaj, Rectangle & arena, std::vector<Stone> & stones) : mPersonaj(personaj), mArena(arena), mStones(stones) {}

		virtual void MoveUp() override
		{
			int y = mPersonaj.GetY();
			if (y > 0 && !IsCollision(mPersonaj.GetX(), mPersonaj.GetY() - 1))
				mPersonaj.SetY(y - 1);
		}

		virtual void MoveDown() override
		{
			int y = mPersonaj.GetY();
			if (y + mPersonaj.GetShape().GetHeight() < mArena.GetHeight() &&
				!IsCollision(mPersonaj.GetX(), mPersonaj.GetY() + 1))
				mPersonaj.SetY(y + 1);
		}

		virtual void MoveLeft() override
		{
			int x = mPersonaj.GetX();
			if (x > 0 && !IsCollision(mPersonaj.GetX() - 1, mPersonaj.GetY()))
				mPersonaj.SetX(x - 1);

			mPersonaj.SetOrientare(Personaj::SPRE_STANGA);
		}

		virtual void MoveRight() override
		{
			int x = mPersonaj.GetX();
			if (x + mPersonaj.GetShape().GetWidth() < mArena.GetWidth() &&
				!IsCollision(mPersonaj.GetX() + 1, mPersonaj.GetY()))
				mPersonaj.SetX(x + 1);

			mPersonaj.SetOrientare(Personaj::SPRE_DREAPTA);
		}
	};

}