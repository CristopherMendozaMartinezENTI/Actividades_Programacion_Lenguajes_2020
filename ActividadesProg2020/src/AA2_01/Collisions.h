#include "Types.h"

namespace collisions {

	inline bool pointCollision(Vec2 vec, Rect rect)
	{
		return vec.x > rect.x && vec.y > rect.y && vec.x < rect.w + rect.x && vec.y < rect.h + rect.y;
	}

	inline bool rectCollision(Rect rect1, Rect rect2)
	{
		return (pointCollision(Vec2{ rect1.x, rect1.y }, rect2)
			|| pointCollision(Vec2{ rect1.x + rect1.w, rect1.y }, rect2)
			|| pointCollision(Vec2{ rect1.x,rect1.y + rect1.h }, rect2)
			|| pointCollision(Vec2{ rect1.x + rect1.w, rect1.y + rect1.h }, rect2));
	}

	inline bool isColliding(Rect r1, Rect r2) {
		if (r1.x + r1.w > r2.x &&
			r1.x < r2.x + r2.w &&
			r1.y + r1.h > r2.y &&
			r1.y < r2.y + r2.h)
		{

			return true;
		}
		else return false;

		//check Y movement bounce

	}
}




