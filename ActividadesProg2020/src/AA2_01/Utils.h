#include <iomanip>
#include <sstream>
#include <string>
#include "Types.h"

std::string FloatToString(float num, int precision)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << num;
	std::string number = stream.str();
	return number;
}

Rect Vec2ToRect(Vec2 vec, int _width, int _height)
{
	Rect newRect(vec.x, vec.y, _width, _height);
	return newRect;
}

