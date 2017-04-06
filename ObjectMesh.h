#pragma once
#include<vector>
#include "libraries\glm\glm\glm.hpp"

class ObjectMesh {
public:
	ObjectMesh(const char * path);
	~ObjectMesh();

	std::vector< glm::vec3 > getVertices();

	std::vector< glm::vec2 > getUvs();

	std::vector< glm::vec3 > getNormals();

private:
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
};
