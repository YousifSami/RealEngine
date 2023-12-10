#pragma once


struct REBoxBounds {
	REBoxBounds() : x(0.0f), y(0.0f), w(1.0f), h(1.0f) {}
	REBoxBounds(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

	REBoxBounds operator+(REBoxBounds Other) {
		REBoxBounds Result;

		//this bound +other bounds
		Result.x = x + Other.x;
		Result.y = y + Other.y;
		Result.w = w + Other.w;
		Result.h = h + Other.h;

		return Result;
	}

	bool IsOverlapping(const REBoxBounds& Other) {
		return MaxX() > Other.x && x <Other.MaxX()
			&& MaxY() > Other.y;
	}

	//gives the x value + the width
	float MaxX() const { return x + w;}
	//gives the y value + the height
	float MaxY() const { return y + h; }

	float x, y;
	float w, h;
};
