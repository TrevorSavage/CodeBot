#pragma once
#include "HudNode.h"
#include "Game.h"

class TurnRightNode :
	public HudNode
{
public:
	TurnRightNode(glm::vec2 p, glm::vec2 s, int id) : HudNode(p, s, id) {
		name = "Turn Right";
	}
	virtual ~TurnRightNode() {};

	void onRun() {
		Game::getScene()->getLevel()->getPlayerPawn()->turnRight();
	}
};
