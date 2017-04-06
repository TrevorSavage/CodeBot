#pragma once
#include "SceneObject.h"
#include "ObjectMesh.h"
#include "Texture.h"

class RenderedObject :
	public SceneObject
{
public:
	RenderedObject(std::string name, ObjectMesh* m);
	RenderedObject(std::string name, ObjectMesh* m, Texture* t);
	~RenderedObject();

	ObjectMesh* getMesh();
	void setMesh(ObjectMesh* m);
	void draw(glm::mat4 parentTransform);

private:
	ObjectMesh* mesh;
	Texture* tex;
};

