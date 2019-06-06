#pragma once
#include "maths.h"
#include "Texture.h"

class Gui {
public:
	vector2 position;
	vector2 scale;
	float depth;
	Texture* texture;
private:
};
class GuiSystem
{
public:
	GuiSystem();
	~GuiSystem();
};

