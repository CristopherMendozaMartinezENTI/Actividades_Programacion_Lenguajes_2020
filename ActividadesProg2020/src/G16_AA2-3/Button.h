#pragma once
#include "GameObject.h"


class Button : public GameObject {

protected:
	bool isHovered;
	Text text, textHover;
	Rect textRect;
	std::string textRectID;

public:
	Button();
	Button(Color _normal, Color _hovered, std::string _text, Rect _position, std::string _id);
	~Button();
	void Update(InputManager _input, float _deltaTime);
	void Draw();
	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	std::string GetTexture();
	void SetHover(bool _b);
};


class SpecialButton: public Button {

private:
	bool isPressed;
	Text text2, textHover2;
	Rect textRect2;
	std::string textRect2ID;

public:
	SpecialButton();
	SpecialButton(Color _normal, Color _hovered, Color _normal2, Color _hovered2, std::string _text, std::string _text2, Rect _position, std::string _id);
	~SpecialButton();
	void Update(InputManager _input, float _deltaTime);
	void Draw();
	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	std::string GetTexture();
	void SetHover(bool _b);
	void SetPressed();
};