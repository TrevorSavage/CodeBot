#pragma once
#include "SceneObject.h"
#include "RenderedObject.h"
#include "Transformer.h"
#include <vector>

class Grouping : public SceneObject
{
public:
	Grouping(std::string name);
	Grouping(std::string name, std::vector<SceneObject*> initObjs);
	~Grouping();

	void rotateChildrenBy(glm::vec3 rotAmt);

	std::vector<SceneObject*> getObjects();
	SceneObject* getObject(std::string name);
	void removeObject(std::string name);
	void addObject(SceneObject* obj);
	virtual void draw(glm::mat4 parentTransform);

protected:
	std::vector<SceneObject*> objects;
};

