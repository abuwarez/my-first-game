#pragma once

namespace MyGame
{
	class Shape;

	class SpatialShape
	{
	public:
		virtual Shape & GetShape() = 0;
		virtual const Shape & GetShape() const = 0;
		virtual int GetX() const = 0;
		virtual int GetY() const = 0;

		virtual ~SpatialShape() {}
	};
}