#pragma once
#include "Grouping.h"
#include "SceneObject.h"
#include "RenderedObject.h"
#include "Transformer.h"
#include "Hud.h"
#include "Level.h"
#include <vector>



class Scene
{
public:
	Scene();
	Scene(Level* startLevel);
	~Scene();

	Hud* getHud();
	Level* getLevel();
	void setLevel(Level* newVal);
	SceneObject* getCamera();
	void draw();
	void onMousePressed(int x, int y);
	void onMouseReleased(int x, int y);
	void onMouseDragged(int x, int y, glm::vec2 start);
private:
	Level* currentLevel;
	Hud* sceneHud;
	SceneObject* camera;
};

