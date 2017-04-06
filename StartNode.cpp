#include "StartNode.h"
#include "glm\glm.hpp"

StartNode::StartNode(glm::vec2 pos, glm::vec2 size, int id)  : HudNode(pos, size, id)
{
	//set the 'in' node to null. the start node should have no 'in' value
	execIn = NULL;
	name = "START";
}


StartNode::~StartNode()
{
}

void StartNode::onRun() {};