#include "DynText.h"

DynText::DynText()
{
}

DynText::DynText(Rect newPosition)
{
	position = newPosition;
}

DynText::~DynText()
{
}

void DynText::UpdateText(Text newText, int size)
{
	text = newText;
	position.w = text.text.length() * size;
}

void DynText::Draw()
{
	Renderer::Instance()->OverwritteTextureText(text);
	Renderer::Instance()->PushImageToRect(text.id, { position.x, position.y, position.w, position.h });
}
