#include "Game.h"
#include <iostream>
#include <string>

State Game::simState = stopped;
Scene* Game::currentScene = new Scene();
HudNode* Game::nodeToExecute = NULL;
int Game::ticksThisNode = 0;

Game::Game(){
	
}


Game::~Game(){
	delete currentScene;
}

Scene* Game::getScene() {
	return currentScene;
}

void Game::setScene(Scene* newVal) {
	currentScene = newVal;
}

State Game::getState() {
	return simState;
}

void Game::init() {
	makeLevelOne();
	nodeToExecute = Game::getScene()->getHud()->getStartNode();
}

void Game::makeLevelOne() {
	int cols = 10;
	int rows = 10;
	int map[10][10]{	{ 0,0,0,0,0,0,0,0,0,0 },
						{ 0,1,1,1,1,1,1,0,0,0 },
						{ 0,1,0,0,0,0,1,0,0,0 },
						{ 0,1,2,2,2,2,1,1,1,0 },
						{ 0,1,1,1,1,2,1,2,1,0 },
						{ 0,1,1,1,1,2,1,2,1,0 },
						{ 0,2,2,2,1,1,1,2,0,0 },
						{ 0,0,0,0,0,1,1,1,1,0 },
						{ 0,0,0,0,0,2,2,2,3,0 },
						{ 0,0,0,0,0,0,0,0,0,0 } };
	std::vector<std::vector<int>> grid;
	grid.resize(rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i].push_back(map[i][j]);
		}
	}
	const char* meshPath = "C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/obj/terrainCube.obj";
	const char* texPath = "C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/textures/terrainTex.png";
	ObjectMesh* m = new ObjectMesh(meshPath);
	Texture* t = new Texture(texPath);
	RenderedObject* terrainObj = new RenderedObject("tile", m, t);
	Level* l = new Level(grid, terrainObj);

	meshPath = "C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/obj/robot.obj";
	texPath = "C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/textures/robotTex.png";
	m = new ObjectMesh(meshPath);
	t = new Texture(texPath);
	l->setPlayerPawn(new Character("player", m, t));
	l->setPlayerStartPos(glm::vec2(1, 1));
	currentScene->setLevel(l);
}

void Game::makeLevelTwo() {
	int cols = 10;
	int rows = 10;
	int map[10][10]{ { 0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,2,1,1,1,0 },
	{ 0,1,1,1,1,2,2,2,0,0 },
	{ 0,1,1,1,1,2,1,1,1,0 },
	{ 0,2,1,2,2,2,1,1,1,0 },
	{ 0,1,1,0,0,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,3,0 },
	{ 0,0,0,0,0,0,0,0,0,0 } };
	std::vector<std::vector<int>> grid;
	grid.resize(rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i].push_back(map[i][j]);
		}
	}
	const char* meshPath = "C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/obj/terrainCube.obj";
	const char* texPath = "C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/textures/terrainTex.png";
	ObjectMesh* m = new ObjectMesh(meshPath);
	Texture* t = new Texture(texPath);
	RenderedObject* terrainObj = new RenderedObject("tile", m, t);
	Level* l = new Level(grid, terrainObj);

	meshPath = "C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/obj/robot.obj";
	texPath = "C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/textures/robotTex.png";
	m = new ObjectMesh(meshPath);
	t = new Texture(texPath);
	l->setPlayerPawn(new Character("player", m, t));
	l->setPlayerStartPos(glm::vec2(1, 1));
	currentScene->setLevel(l);
}

void Game::draw() {
	currentScene->draw();
}

void Game::startSimulation() {
	nodeToExecute = currentScene->getHud()->getStartNode();
	ticksThisNode = 0;
	if (nodeToExecute->getNext() == NULL) {
		endSimulation(error);
	}
	else {
		nodeToExecute = nodeToExecute->getNext();
		simState = playing;
	}
}

void Game::runSimulation() {
	if (nodeToExecute == NULL) {
		//we reached the end of the logic string
		endSimulation(none);
		return;
	}
	//std::cout << "simulating "<< nodeToExecute->getName() << std::endl;
	nodeToExecute->onRun();

	bool playerIsDead = currentScene->getLevel()->getPlayerPawn()->getIsDead();
	if (playerIsDead) {
		endSimulation(died);
		return;
	}
	else if (currentScene->getLevel()->getIsWon()) {
		endSimulation(won);
		return;
	}

	ticksThisNode++;
	if (ticksThisNode >= nodeToExecute->getNumTicks()) {
		ticksThisNode = 0;
		nodeToExecute = nodeToExecute->getNext();
	}
}

void Game::endSimulation(Result r) {
	switch (r) {
	case error:
		std::cout << "error";
		currentScene->getHud()->setMessage("No logic was attached to the start node! Resetting.");
		break;
	case none:
		std::cout << "we reached the end of logic\n";
		currentScene->getHud()->setMessage("You did not reach the goal! Resetting.");
		break;
	case died:
		std::cout << "we died\n";
		currentScene->getHud()->setMessage("You fell off a ledge and died. Resetting.");
		break;
	case won:
		std::cout << "we won!!\n";
		currentScene->getHud()->setMessage("You won the game! Hail to the King!");
		makeLevelTwo();
		break;
	}
	currentScene->getHud()->setIsMessageShowing(true);
	simState = stopped;
	//display message based on result of stopping play
	currentScene->getLevel()->reset();
}
