#pragma once
#include "HudNode.h"
#include "Game.h"

class TurnLeftNode :
	public HudNode
{
public:
	TurnLeftNode(glm::vec2 p, glm::vec2 s, int id) : HudNode(p, s, id){
		name = "Turn Left";
	}
	virtual ~TurnLeftNode() {};

	void onRun() {
		Game::getScene()->getLevel()->getPlayerPawn()->turnLeft();
	}
};