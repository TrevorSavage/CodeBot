#pragma once
#include "libraries\glm\glm\glm.hpp"
#include "libraries\glew\glew.h"

class Transformer {
public:
	Transformer();
	~Transformer();

	static const float FOV;
	static const float NEAR_PLANE;
	static const float FAR_PLANE;
	static int windowHeight;
	static int windowWidth;

	static glm::mat4 getMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
	static glm::mat4 getCameraMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
	static glm::mat4 getTranslationMatrix(glm::fvec3 transVal);
	static glm::mat4 getRotationMatrix(glm::fvec3 rotVal);
	static glm::mat4 getScaleMatrix(glm::fvec3 scaleVal);
	static void setWindowSize(int width, int height);
	static glm::mat4 getPerspectiveMatrix();
	static float degreesToRadians(float degAngle);

	static void createNewProjectionMatrix();

	static glm::mat4 projMatrix;
	static glm::mat4 identity;

private:

	static glm::mat4 createProjectionMatrix();
	static glm::mat4 rotateX(float angle);
	static glm::mat4 rotateY(float angle);
	static glm::mat4 rotateZ(float angle);
};