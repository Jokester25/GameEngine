#pragma once
namespace nu
{ 
	struct Vector2
	{
		float x, y;

		Vector2() = default;
		Vector2(float x, float y) : x(x), y(y) {};
		Vector2(float v) : x(v), y(v) {};
	};
}