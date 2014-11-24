#include "SceneGraph.h"


SceneGraph::SceneGraph()
	:root(new SceneNode())
{

}

SceneGraph::SceneGraph(SceneNode* _root)
	: root(_root)
{

}

SceneGraph::~SceneGraph()
{
	if (root)
	{
		delete root;
		root = NULL;
	}
}

void SceneGraph::RenderSceneGraph(const Renderer* renderer, const Camera* camera) const
{
	root->RenderSceneNode(renderer, camera);
}

void SceneGraph::UpdateSceneGraph(float dt)
{
	root->UpdateSceneNode(dt);
}
