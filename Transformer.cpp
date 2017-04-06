#include "Transformer.h"
#include "libraries\glm\glm\gtc\matrix_transform.hpp"
#include <iostream>

const float Transformer::FOV = 45.0f;
const float Transformer::NEAR_PLANE = 0.01f;
const float Transformer::FAR_PLANE = 10000.0f;
int Transformer::windowWidth = 800;
int Transformer::windowHeight = 600;
glm::mat4 Transformer::identity = glm::mat4(1.0);
glm::mat4 Transformer::projMatrix = Transformer::createProjectionMatrix();

Transformer::Transformer(){
}
Transformer::~Transformer() {}

glm::mat4 Transformer::createProjectionMatrix() {
	float aspectRatio = (float)windowWidth / (float)windowHeight;
	float y_scale = (1.0f / tan(degreesToRadians(FOV)/ 2.0f));
	float x_scale = (1.0f / tan(degreesToRadians(FOV) / 2.0f)) / aspectRatio;
	float frustum_length = FAR_PLANE - NEAR_PLANE;

	glm::fmat4 returnMatrix = identity;
	returnMatrix[0][0] = x_scale;
	returnMatrix[1][1] = y_scale;
	returnMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	returnMatrix[2][3] = -1;
	returnMatrix[3][2] = -((2 * NEAR_PLANE *FAR_PLANE) / frustum_length);
	returnMatrix[3][3] = 0;

	return returnMatrix;
}

//only call after a glBegin()
void Transformer::createNewProjectionMatrix() {
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;
	float aspectRatio = (float)windowWidth / (float)windowHeight;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(FOV / 360 * pi) * NEAR_PLANE;
	fW = fH * aspectRatio;

	glFrustum(-fW, fW, -fH, fH, NEAR_PLANE, FAR_PLANE);
}

void Transformer::setWindowSize(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	projMatrix = createProjectionMatrix();
}

glm::mat4 Transformer::getTranslationMatrix(glm::fvec3 transVal) {
	glm::mat4 matrix = identity;
	matrix[3][0] = transVal[0];
	matrix[3][1] = transVal[1];
	matrix[3][2] = transVal[2];

	return matrix;
}

glm::mat4 Transformer::getRotationMatrix(glm::fvec3 rotAxes) {
	return (rotateX(rotAxes[0])*rotateY(rotAxes[1])*rotateZ(rotAxes[2]));
}

glm::mat4 Transformer::getScaleMatrix(glm::fvec3 scaleVal) {
	glm::mat4 matrix = identity;
	matrix[0][0] = scaleVal[0];
	matrix[1][1] = scaleVal[1];
	matrix[2][2] = scaleVal[2];

	return matrix;
}

glm::mat4 Transformer::getMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale) {
	return getTranslationMatrix(translation)*getRotationMatrix(rotation)*getScaleMatrix(scale);
}

glm::mat4 Transformer::getPerspectiveMatrix() {
	return projMatrix;
}

glm::mat4 Transformer::getCameraMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale) {
	return getRotationMatrix(rotation)*getTranslationMatrix(translation)*getScaleMatrix(scale);
}

glm::mat4 Transformer::rotateX(float angle) {
	angle = degreesToRadians(angle);
	glm::mat4 matrix = identity;
	matrix[1][1] = cos(angle);
	matrix[1][2] = sin(angle);
	matrix[2][1] = -sin(angle);
	matrix[2][2] = cos(angle);

	return matrix;
}

glm::mat4 Transformer::rotateY(float angle) {
	angle = degreesToRadians(angle);
	glm::mat4 matrix = identity;
	matrix[0][0] = cos(angle);
	matrix[0][2] = -sin(angle);
	matrix[2][0] = sin(angle);
	matrix[2][2] = cos(angle);

	return matrix;
}

glm::mat4 Transformer::rotateZ(float angle) {
	angle = degreesToRadians(angle);
	glm::mat4 matrix = identity;
	matrix[0][0] = cos(angle);
	matrix[0][1] = sin(angle);
	matrix[1][0] = -sin(angle);
	matrix[1][1] = cos(angle);

	return matrix;
}

float Transformer::degreesToRadians(float degAngle) {
	float pi = 3.141592;
	return degAngle*pi / 180;
}

