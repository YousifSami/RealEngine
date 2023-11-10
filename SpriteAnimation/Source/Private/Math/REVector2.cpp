#include "CoreMinimal.h"
#include "Math/REVector2.h"

REVector2::REVector2()
{
	x = y = 0.0f;
}

REVector2::REVector2(float z)
{
	x = y = z;
}

REVector2::REVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool REVector2::operator==(REVector2 Other)
{
	//this x = 1 and other x = 1 while also y = 1 and other y = 1
	return x == Other.x && y == Other.y; 
}

bool REVector2::operator!=(REVector2 Other)
{
	//this x not equal other x or this y  not equal other y
	return x != Other.x || y != Other.y;
}

REVector2 REVector2::operator+(REVector2 Other)
{
	return REVector2(x + Other.x, y + Other.y);
}

REVector2& REVector2::operator+=(REVector2 Other)
{
	x += Other.x;
	y += Other.y;

	return *this;
}

REVector2 REVector2::operator-(REVector2 Other)
{
	return REVector2(x - Other.x, y - Other.y);
}

REVector2& REVector2::operator-=(REVector2 Other)
{
	x -= Other.x;
	y -= Other.y;

	return *this;
}

REVector2 REVector2::operator*(REVector2 Other)
{
	return REVector2(x * Other.x, y *  Other.y);
}

REVector2& REVector2::operator*=(REVector2 Other)
{
	x *= Other.x;
	y *= Other.y;

	return *this;
}

REVector2 REVector2::operator/(REVector2 Other)
{
	REVector2 Result;

	if (Other.x == 0.0f) {
		RELog("Attempting to divide by 0.");
	}
	else {
		Result.x = x / Other.x;
	}

	if (Other.y == 0.0f) {
		RELog("Attempting to divide by 0.");
	}
	else {
		Result.y = y / Other.y;
	}

	return Result;
}

REVector2& REVector2::operator/=(REVector2 Other)
{
	if (Other.x == 0.0f) {
		RELog("Attempting to divide by 0.");
	}
	else {
		x /= Other.x;
	}

	if (Other.y == 0.0f) {
		RELog("Attempting to divide by 0.");
	}
	else {
		y /= Other.y;
	}

	return *this;
}

REVector2 REVector2::operator*(float Scalar)
{
	return REVector2(x * Scalar, y * Scalar);
}

REVector2& REVector2::operator*=(float Scalar)
{
	x *= Scalar;
	y *= Scalar;

	return *this;
}

REVector2 REVector2::operator/(float Scalar)
{
	REVector2 Result;

	if (Scalar == 0.0f) {
		RELog("Attemping to divide by 0");
		return Result; 
	}

	Result.x = x / Scalar;
	Result.y = y / Scalar;

	return Result;
}

REVector2& REVector2::operator/=(float Scalar)
{
	if (Scalar == 0.0f) {
		RELog("Attemping to divide by 0");
		return *this;;
	}

	x /= Scalar;
	y /= Scalar;

	return *this;
}

void REVector2::Log()
{
	RELog("x: " + std::to_string(x) + " , y: " + std::to_string(y));
}

void REVector2::LogLength()
{
	RELog(std::to_string(Length()));
}

float REVector2::Length()
{
	return sqrtf((x * x) + (y * y));
}

REVector2& REVector2::Normalise()
{
	if (Length() != 0.0f) {
		*this /= Length();
	}

	return *this;
}

REVector2 REVector2::Normal()
{
	REVector2 Result = *this;

	if (Length() != 0.0f) {
		Result /=  Length();
	}

	return Result;
}

float REVector2::Distance(REVector2& v1, REVector2& v2)
{
	return (v1 - v2).Length();
}

REVector2 REVector2::Zero()
{
	return REVector2();
}
