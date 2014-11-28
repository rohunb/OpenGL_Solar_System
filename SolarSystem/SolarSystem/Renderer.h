#pragma once
#include "vgl.h"
#include "Model.h"

typedef unsigned int uint;

class Renderer
{
public:
	Renderer(int height, int width, int posX, int posY, char* windowName, uint displayMode);
	~Renderer();

	void PreRender() const;
	void RenderModel(const Model* model) const;


};

