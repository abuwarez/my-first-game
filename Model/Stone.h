#pragma once

#include "Geometry/SpatialShape.h"
#include "Geometry/Rectangle.h"

namespace MyGame
{
	class Stone : public SpatialShape
	{
		Rectangle mShape;
		int mX, mY;

	public:
		Stone() : mShape(0, 0), mX(0), mY(0) {}
		Stone(int x, int y, int width, int height) : mShape(width, height), mX(x), mY(y) {}

		virtual Shape & GetShape() override { return mShape; }
		virtual const Shape & GetShape() const override { return mShape; };
		virtual int GetX() const override { return mX; }
		virtual int GetY() const override { return mY; }
	};
}