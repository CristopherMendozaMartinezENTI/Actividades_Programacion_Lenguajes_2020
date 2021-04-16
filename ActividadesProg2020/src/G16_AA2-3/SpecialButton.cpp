
#include "Button.h"


SpecialButton::SpecialButton()
{

}

SpecialButton::SpecialButton(Color _normal, Color _hovered, Color _normal2, Color _hovered2, std::string _text, std::string _text2, Rect _position, std::string _id)
{
	//La fuente "BomberFont" se carga desde el SceneMenu al Empezar la partida.
	text = Text("text" + _id, _text, _normal);
	text2 = Text("text2" + _id, _text2, _normal2);

	textHover = Text("textHover" + _id, _text, _hovered);
	textHover2 = Text("textHover2" + _id, _text2, _hovered2);

	textRectID = "RextTextID" + _id;
	textRect2ID = "RectText2ID" + _id;

	isHovered = false;
	isPressed = false;

	Renderer::Instance()->LoadTextureText("BomberFont", text);
	Renderer::Instance()->LoadTextureText("BomberFont", textHover);
	Renderer::Instance()->LoadTextureText("BomberFont", text2);
	Renderer::Instance()->LoadTextureText("BomberFont", textHover2);

	int tmpPoint = ((_position.x * 2) - Renderer::Instance()->GetTextureSize(text.id).x) / 2;
	textRect = { tmpPoint, _position.y, Renderer::Instance()->GetTextureSize(text.id).x, Renderer::Instance()->GetTextureSize(text.id).y };
	Renderer::Instance()->LoadRect(textRectID, textRect);

	int tmpPoint2 = ((_position.x * 2) - Renderer::Instance()->GetTextureSize(text2.id).x) / 2;
	textRect2 = { tmpPoint2, _position.y, Renderer::Instance()->GetTextureSize(text2.id).x, Renderer::Instance()->GetTextureSize(text2.id).y };
	Renderer::Instance()->LoadRect(textRect2ID, textRect2);
}

SpecialButton::~SpecialButton()
{

}

void SpecialButton::Update(InputManager _input, float _deltaTime)
{
}

void SpecialButton::Draw()
{
	if (isPressed)
	{
		if (!isHovered)
			Renderer::Instance()->PushImage(text2.id, textRect2ID);
		else
		{
			Renderer::Instance()->PushImage(textHover2.id, textRect2ID);
		}
	}
	else {
		if (!isHovered)
			Renderer::Instance()->PushImage(text.id, textRectID);
		else
			Renderer::Instance()->PushImage(textHover.id, textRectID);
	}
}

Rect SpecialButton::GetRect()
{
	return textRect;
}

Rect SpecialButton::GetFrame()
{
	return frame;
}

Rect SpecialButton::GetPosition()
{
	return position;
}

std::string SpecialButton::GetTexture()
{
	return texture;
}

void SpecialButton::SetHover(bool _b)
{
	isHovered = _b;
}
void SpecialButton::SetPressed()
{
	if (isPressed) isPressed = false;
	else isPressed = true;
}
