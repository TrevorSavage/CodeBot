#pragma once

#include <vector>
#include "libraries\glm\glm\glm.hpp"

class ObjLoader {
public:

	ObjLoader();
	~ObjLoader();

	bool loadOBJ(
		const char * path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals
	);
};