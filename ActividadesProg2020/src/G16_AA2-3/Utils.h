
#include "Types.h"


Rect Vec2ToRect(Vec2 vec, int _width, int _height)
{
	Rect newRect(vec.x, vec.y, _width, _height);
	return newRect;
}



