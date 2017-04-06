#pragma once
#include "Scene.h"

enum State{stopped = 0, playing = 1};
enum Result{error = 0, none = 1, died = 2, won = 3};

class Game
{
public:
	Game();
	~Game();

	static Scene* getScene();
	static void setScene(Scene* newVal);
	static State Game::getState();
	static void init();
	static void makeLevelOne();
	static void makeLevelTwo();
	static void draw();
	static void startSimulation();
	static void runSimulation();
	static void endSimulation(Result r);
private:
	static Scene* currentScene;
	static HudNode* nodeToExecute;
	static State simState;
	static int ticksThisNode;
};

