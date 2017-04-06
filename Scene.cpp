#include "Scene.h"
#include <iostream>

Scene::Scene(){
	sceneHud = new Hud();
	currentLevel = NULL;
	camera = new SceneObject("camera");
}

Scene::Scene(Level* level){
	sceneHud = new Hud();
	currentLevel = level;
	camera = new SceneObject("camera");
}

Scene::~Scene() {
	delete sceneHud;
	delete currentLevel;
	delete camera;
}

Hud* Scene::getHud() {
	return sceneHud;
}

Level* Scene::getLevel() {
	return currentLevel;
}

void Scene::setLevel(Level* newVal) {
	currentLevel = newVal;
}

SceneObject* Scene::getCamera() {
	return camera;
}

void Scene::draw() {
	if (currentLevel != NULL) {
		glm::mat4 camTransform = Transformer::getCameraMatrix(camera->getTranslation(), camera->getRotation(), camera->getScale());
		currentLevel->draw(camTransform);
	}
	sceneHud->draw();
}

void Scene::onMousePressed(int x, int y) {
	sceneHud->onMousePressed(x, y);
}

void Scene::onMouseReleased(int x, int y) {
	sceneHud->onMouseReleased(x, y);
}

void Scene::onMouseDragged(int x, int y, glm::vec2 start) {
	sceneHud->onMouseDragged(x, y, start);
}
