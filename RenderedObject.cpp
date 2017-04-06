#include "RenderedObject.h"
#include "Transformer.h"
#include <iostream>



RenderedObject::RenderedObject(std::string name, ObjectMesh* m) : SceneObject(name){
	mesh = m;
	tex = NULL;
}

RenderedObject::RenderedObject(std::string name, ObjectMesh* m, Texture* t) : SceneObject(name){
	mesh = m;
	tex = t;
}

RenderedObject::~RenderedObject(){
	if (mesh) delete(mesh);
	if (tex) delete(tex);
}

ObjectMesh* RenderedObject::getMesh() {
	return mesh;
}

void RenderedObject::setMesh(ObjectMesh* newVal) {
	mesh = newVal;
}

void RenderedObject::draw(glm::mat4 parentTransform){
	//std::cout << "Drawing object: " << name.c_str() << std::endl;
	//get the objects texture id (if it exists) and bind it
	if (tex) {
		GLuint texId = tex->getTextureId();
		glBindTexture(GL_TEXTURE_2D, texId);
	}
	std::vector< glm::vec3 > vertices = mesh->getVertices();
	std::vector< glm::vec2 > uvs = mesh->getUvs();
	std::vector< glm::vec3 > normals = mesh->getNormals();

	//get the resultant transformation matrix after applying world and then parent/clip transforms
	glm::mat4 objToWorld = Transformer::getMatrix(translation, rotation, scale);
	glm::mat4 objToClip = parentTransform*objToWorld;

	//for each vertex in the object, apply the transformation matrix
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertices.size(); i++) {
			if (tex) {
				glTexCoord2f(uvs[i].x, uvs[i].y);
			}
			glNormal3f(normals[i][0], normals[i][1], normals[i][2]);
			//std::cout << normals[i][0] << " " << normals[i][1] << " " << normals[i][2] << std::endl;
			glm::fvec4 nPoint(vertices[i][0], vertices[i][1], vertices[i][2], 1.0f);
			nPoint = objToClip*nPoint;
			glVertex3f(nPoint[0], nPoint[1], nPoint[2]);
		}
	glEnd();
	
}
