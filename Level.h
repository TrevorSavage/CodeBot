#pragma once
#include "Character.h"
#include <vector>

class Level
{
public:
	Level(std::vector<std::vector<int>> grid, RenderedObject* tile);
	~Level();

	void setGridArray(std::vector<std::vector<int>> newVal);
	Character* getPlayerPawn() {
		return playerPawn;
	}
	void setPlayerPawn(Character* newVal) {
		playerPawn = newVal;
	}
	bool getIsWon();
	void setIsWon(bool newVal);
	void setPlayerStartPos(glm::vec2 newVal);
	void movePlayerForward();
	void draw(glm::mat4 camTransform);
	void reset();

private:
	RenderedObject* terrainTile;
	//array defining the level layout. 0 is a hole, 1 is walkable terrain, 2 is wall
	std::vector<std::vector<int>> gridArray;
	Character* playerPawn;
	bool isWon;
	glm::vec2 playerStartPos;
	RenderedObject* finishTile;
	RenderedObject* wallTile;
};

