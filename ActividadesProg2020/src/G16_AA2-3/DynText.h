#pragma once
#include "Renderer.h"
class DynText
{
	Text text;
	Rect position;
public:
	DynText();
	DynText(Rect newPosition);
	~DynText();

	void UpdateText(Text newText, int size);
	void Draw();
};

