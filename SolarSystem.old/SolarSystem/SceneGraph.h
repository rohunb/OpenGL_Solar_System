#pragma once
#include "SceneNode.h"
#include "Camera.h"

class SceneGraph
{
	
public:
	SceneNode* root;

	SceneGraph();
	SceneGraph(SceneNode* root);
	~SceneGraph();

	void RenderSceneGraph(const Renderer* renderer, const Camera* camera) const;
	void UpdateSceneGraph(float dt);
};

