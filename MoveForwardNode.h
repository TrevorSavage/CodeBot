#pragma once
#include "HudNode.h"
class MoveForwardNode :
	public HudNode
{
public:
	MoveForwardNode(glm::vec2 p, glm::vec2 s, int id);
	virtual ~MoveForwardNode();

	void onRun();
};

