#pragma once

namespace MyGame
{
	class InputListener
	{
	public:
		virtual void MoveUp() = 0;
		virtual void MoveDown() = 0;
		virtual void MoveLeft() = 0;
		virtual void MoveRight() = 0;

		virtual ~InputListener() {}
	};
}