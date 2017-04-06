#include "ObjectMesh.h"
#include "ObjLoader.h"

ObjectMesh::ObjectMesh(const char * path) {
	ObjLoader objLoader;
	objLoader.loadOBJ(path, vertices, uvs, normals);
}
ObjectMesh::~ObjectMesh() {}

std::vector< glm::vec3 > ObjectMesh::getVertices() {
	return vertices;
}

std::vector< glm::vec2 > ObjectMesh::getUvs() {
	return uvs;
}

std::vector< glm::vec3 > ObjectMesh::getNormals() {
	return normals;
}