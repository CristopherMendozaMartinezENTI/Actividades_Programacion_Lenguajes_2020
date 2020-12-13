#pragma once
#include "GameObject.h""


class Button : public GameObject {

private:
	bool isPressed;
	Color color;
	std::string text;
	
public:
	Button();
	~Button();
	void Update(InputManager _input);
	Rect GetRect();
	Rect GetFrame();
	Vec2 GetPosition();
	bool GetPressed();


};
