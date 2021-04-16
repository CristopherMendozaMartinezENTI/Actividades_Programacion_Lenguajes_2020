
#include "Button.h"


Button::Button()
{

}

Button::Button(Color _normal, Color _hovered, std::string _text, Rect _position, std::string _id)
{
	//La fuente "BomberFont" se carga desde el SceneMenu al Empezar la partida.

	text = Text("text" + _id, _text, _normal);
	textHover = Text("textHover" + _id, _text, _hovered);
	textRectID = "RextTextID" + _id;
	isHovered = false;

	Renderer::Instance()->LoadTextureText("BomberFont", text);
	Renderer::Instance()->LoadTextureText("BomberFont", textHover);

	int tmpPoint = ((_position.x * 2) - Renderer::Instance()->GetTextureSize(text.id).x) / 2;
	textRect = { tmpPoint, _position.y, Renderer::Instance()->GetTextureSize(text.id).x, Renderer::Instance()->GetTextureSize(text.id).y };
	Renderer::Instance()->LoadRect(textRectID, textRect);

}

Button::~Button()
{

}

void Button::Update(InputManager _input, float _deltaTime)
{
}

void Button::Draw()
{
	if (!isHovered)
		Renderer::Instance()->PushImage(text.id, textRectID);
	else
		Renderer::Instance()->PushImage(textHover.id, textRectID);
}

Rect Button::GetRect()
{
	return textRect;
}

Rect Button::GetFrame()
{
	return frame;
}

Rect Button::GetPosition()
{
	return position;
}

std::string Button::GetTexture()
{
	return texture;
}

void Button::SetHover(bool _b)
{
	isHovered = _b;
}

