#pragma once

struct REVector2{
	REVector2();
	REVector2(float z);
	REVector2(float x, float y);

	//allow the negation of vectors
	REVector2 operator-() {
		return REVector2(-x, -y);
	}

	//assigns boolean operators
	bool operator==(REVector2 Other);
	bool operator!=(REVector2 Other);

	//arithmetic operator "+,-,*,/,+=,-=,*=,/="
	REVector2 operator+(REVector2 Other);
	REVector2& operator+=(REVector2 Other);

	REVector2 operator-(REVector2 Other);
	REVector2& operator-=(REVector2 Other);

	REVector2 operator*(REVector2 Other);
	REVector2& operator*=(REVector2 Other);

	REVector2 operator/(REVector2 Other);
	REVector2& operator/=(REVector2 Other);

	//scalar arithmetic operator
	REVector2 operator*(float Scalar);
	REVector2& operator*=(float Scalar);

	REVector2 operator/(float Scalar);
	REVector2& operator/=(float Scalar); 
	
	//debug log
	void Log();

	//quick debug for length logging
	void LogLength();

	//length is power of vector
	float Length();

	//normalise vector2
	REVector2& Normalise();

	//return the normal of a vector
	REVector2 Normal();

	//get distance between 2 vectors
	static float Distance(REVector2& v1, REVector2& v2);

	//returns 0 vector2
	static REVector2 Zero();

	float x, y;
};