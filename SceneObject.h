#pragma once
#include "ObjectMesh.h"
#include "Texture.h"
#include "glm\glm.hpp"
#include <vector>

struct Transform {
	enum TransType { TRANSLATE, ROTATE, SCALE };

	TransType type;
	glm::vec3 value;

	Transform(TransType t, glm::vec3 v) {
		type = t;
		value = v;
	}
};

class SceneObject
{
public:
	SceneObject(std::string name);
	~SceneObject();

	std::string getName();
	glm::vec3 getTranslation();
	void setTranslation(glm::vec3 newVal);
	glm::vec3 getRotation();
	glm::vec3 getScale();

	void clearTransforms();

	void translateBy(glm::fvec3 transVal);
	void rotateBy(glm::fvec3 scaleVal);
	void scaleBy(glm::fvec3 scaleVal);

	virtual void draw(glm::mat4 parentTransform);

protected:
	std::string name;
	glm::fvec3 translation;
	glm::fvec3 rotation;
	glm::fvec3 scale;
};

