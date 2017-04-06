#include "MoveForwardNode.h"
#include "Game.h"

MoveForwardNode::MoveForwardNode(glm::vec2 p, glm::vec2 s, int id) : HudNode(p, s, id) {
	name = "Move Forward";
}
MoveForwardNode::~MoveForwardNode(){}

void MoveForwardNode::onRun() {
	Level* level = Game::getScene()->getLevel();
	level->movePlayerForward();
}
